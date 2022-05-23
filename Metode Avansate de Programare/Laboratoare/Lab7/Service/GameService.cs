using System;
using System.Collections.Generic;
using Lab7.Domain;
using Lab7.Validator;
using Lab7.Repository;
using Lab7.Exceptions;
using System.Linq;

namespace Lab7.Service
{
    class GameService
    {
        private IRepository<int, Game> gameRepository;
        private IValidator<Game> gameValidator;

        public GameService(IRepository<int, Game> gameRepository, IValidator<Game> gameValidator)
        {
            this.gameRepository = gameRepository;
            this.gameValidator = gameValidator;
        }
        public Game GetGameByTeams(Team firstTeam, Team secondTeam)
        {
            List<Game> games = this.GetAll().ToList();
            var result = games.Where(g => g.FirstTeam.Name.Equals(firstTeam.Name) && g.SecondTeam.Name.Equals(secondTeam.Name) || g.FirstTeam.Name.Equals(secondTeam.Name) && g.SecondTeam.Name.Equals(firstTeam.Name));
            Game resultGame = result.FirstOrDefault();
            if (resultGame == null)
                throw new ServiceException("Cannot find game.");
            return resultGame;
        }
        public IEnumerable<Game> GetAllFromPeriod(DateTime firstDate, DateTime secondDate)
        {
            List<Game> games = this.GetAll().ToList();
            var result = games.Where(g => g.Date.CompareTo(firstDate) >= 0 && g.Date.CompareTo(secondDate) <= 0);
            return result.ToList();
        }
        public Tuple<int, int> ComputeScore(Game game, List<ActivePlayer> activePlayers1, List<ActivePlayer> activePlayers2)
        {
            int firstTeamScore = (from a in activePlayers1 select a.ScoredPoints).Sum();
            int secontTeamScore = (from a in activePlayers2 select a.ScoredPoints).Sum();

            return new Tuple<int, int>(firstTeamScore, secontTeamScore);
        }
        public IEnumerable<Game> GetAll()
        {
            return this.gameRepository.FindAll().ToList();
        }
    }
}
