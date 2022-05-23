using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using Lab7.Domain;
using Lab7.Repository;
using Lab7.Service;
using Lab7.Validator;
using Lab7.Exceptions;

namespace Lab7.MyConsole
{
    class ConsoleInterface
    {
        private TeamService teamService;
        private PlayerService playerService;
        private GameService gameService;
        private ActivePlayerService activePlayerService;

        public ConsoleInterface()
        {
            string teamsFileName = ConfigurationManager.AppSettings["teams"];
            IRepository<int, Team> teamRepository = new TeamRepository(teamsFileName);
            IValidator<Team> teamValidator = new TeamValidator();
            this.teamService = new TeamService(teamRepository, teamValidator);

            string playersFileName = ConfigurationManager.AppSettings["players"];
            IRepository<int, Player> playerRepository = new PlayerRepository(playersFileName);
            IValidator<Player> playerValidator = new PlayerValidator();
            this.playerService = new PlayerService(playerRepository, playerValidator);

            string gamesFileName = ConfigurationManager.AppSettings["games"];
            IRepository<int, Game> gameRepository = new GameRepository(gamesFileName);
            IValidator<Game> gameValidator = new GameValidator();
            this.gameService = new GameService(gameRepository, gameValidator);

            string activePlayersFileName = ConfigurationManager.AppSettings["activeplayers"];
            IRepository<Tuple<int, int>, ActivePlayer> activePlayerRepository = new ActivePlayerRepository(activePlayersFileName);
            IValidator<ActivePlayer> activePlayerValidator = new ActivePlayerValidator();
            this.activePlayerService = new ActivePlayerService(activePlayerRepository, playerRepository, activePlayerValidator);


        }

        private void DisplayMenu()
        {
            Console.WriteLine("Menu:");
            Console.WriteLine("1. Display players from a team.");
            Console.WriteLine("2. Display active players from team from a game.");
            Console.WriteLine("3. Display all games form certain time period.");
            Console.WriteLine("4. Display the score from a game.");
            Console.WriteLine("0. Exit program.");
        }

        public void Start()
        {
            this.DisplayMenu();
            while(true)
            {
                Console.Write("Command: ");
                string input = Console.ReadLine();

                switch(input)
                {
                    case "0": { return; }
                    case "1": { this.DisplayPlayersFromTeam(); break; }
                    case "2": { this.DisplayActivePlayersFromGame(); break; }
                    case "3": { this.DisplayGamesFromTimePeriod(); break; }
                    case "4": { this.DisplayScoreOfGame(); break; }
                    default: { Console.WriteLine("Invalid command!"); break; }
                }
            }
        }

        private void DisplayPlayersFromTeam()
        {
            Console.Write("Give us a team: ");
            string input = Console.ReadLine();

            try
            {
                Team team = this.teamService.GetTeamByName(input);
                List<Player> players = (List<Player>)this.playerService.GetAllByTeam(team);
                players.ForEach(x => Console.WriteLine("ID = " + x.ID + " | Name = " + x.Name));
            }catch(ServiceException e)
            {
                Console.WriteLine(e.GetMessage());
            }
        }
        private void DisplayActivePlayersFromGame()
        {
            Console.Write("Give us a game: ");
            string inputGame = Console.ReadLine();
            Console.Write("Give us a team: ");
            string inputTeam = Console.ReadLine();

            try
            {
                Team team = this.teamService.GetTeamByName(inputTeam);

                string[] gameNames = inputGame.Split(" vs. ");

                Team firstTeam = this.teamService.GetTeamByName(gameNames[0]);
                Team secondTeam = this.teamService.GetTeamByName(gameNames[1]);

                Game game = this.gameService.GetGameByTeams(firstTeam, secondTeam);
                
                List<ActivePlayer> activePlayers = this.activePlayerService.GetAllFromGameAndTeam(game, team).ToList();
                
                activePlayers.ForEach(x => Console.WriteLine(this.playerService.GetByID(x.PlayerID).Name + " | " + x.ScoredPoints + " scored points | " + x.Type.ToString()));
            }catch(ServiceException e)
            {
                Console.WriteLine(e.GetMessage());
            }catch(InputException e)
            {
                Console.WriteLine(e.GetMessage());
            }
        }
        private void DisplayGamesFromTimePeriod()
        {
            Console.Write("First date: ");
            string firstDateInput = Console.ReadLine();
            Console.Write("Second date: ");
            string secondDateInput = Console.ReadLine();


            bool parse1 = DateTime.TryParse(firstDateInput, out DateTime firstDate);
            bool parse2 = DateTime.TryParse(secondDateInput, out DateTime secondDate);

            if(!parse1 || !parse2)
            {
                Console.WriteLine("Invalid date format! Try dd/mm/yyyy.");
                return;
            }
            if(firstDate.CompareTo(secondDate) > 0)
            {
                Console.WriteLine("First date cannot be after second date!");
                return;
            }

            List<Game> games = this.gameService.GetAllFromPeriod(firstDate, secondDate).ToList();
            games.ForEach(Console.WriteLine);
        }
        private void DisplayScoreOfGame()
        {
            Console.Write("Give us a game: ");
            string inputGame = Console.ReadLine();

            try
            {
                string[] gameNames = inputGame.Split(" vs. ");

                Team firstTeam = this.teamService.GetTeamByName(gameNames[0]);
                Team secondTeam = this.teamService.GetTeamByName(gameNames[1]);

                Game game = this.gameService.GetGameByTeams(firstTeam, secondTeam);

                List<ActivePlayer> activePlayers1 = this.activePlayerService.GetAllFromGameAndTeam(game, firstTeam).ToList();
                List<ActivePlayer> activePlayers2 = this.activePlayerService.GetAllFromGameAndTeam(game, secondTeam).ToList();

                Tuple<int, int> score = this.gameService.ComputeScore(game, activePlayers1, activePlayers2);

                Console.WriteLine("[" + firstTeam.Name + "] " + score.Item1 + " - " + score.Item2 + " [" + secondTeam.Name + "]");
            }catch(ServiceException e)
            {
                Console.WriteLine(e.GetMessage());
            }catch (InputException e)
            {
                Console.WriteLine(e.GetMessage());
            }
        }
        private void validateGameInput(string[] input)
        {
            if (input.Length != 3)
                throw new InputException("Team must be of form Team 1 vs. Team 2");

            if (input[1] != "vs.")
                throw new InputException("Team must be of form Team 1 vs. Team 2");
        }
    }
}
