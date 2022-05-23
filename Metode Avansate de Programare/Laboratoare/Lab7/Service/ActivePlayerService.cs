using System;
using System.Collections.Generic;
using System.Linq;
using Lab7.Domain;
using Lab7.Repository;
using Lab7.Validator;
using Lab7.Exceptions;

namespace Lab7.Service
{
    class ActivePlayerService
    {
        private IRepository<Tuple<int, int>, ActivePlayer> activePlayerRepository;
        private IRepository<int, Player> playerRepository;
        private IValidator<ActivePlayer> activePlayerValidator;

        public ActivePlayerService(IRepository<Tuple<int, int>, ActivePlayer> activePlayerRepository, IRepository<int, Player> playerRepository,IValidator<ActivePlayer> activePlayerValidator)
        {
            this.activePlayerRepository = activePlayerRepository;
            this.playerRepository = playerRepository;
            this.activePlayerValidator = activePlayerValidator;
        }
        public IEnumerable<ActivePlayer> GetActivePlayersFromGame(Game game)
        {
            List<ActivePlayer> activePlayers = this.GetAll().ToList();
            var result = activePlayers.Where(a => a.GameID.Equals(game.ID));
            return result.ToList();
        }
        public IEnumerable<ActivePlayer> GetAllFromGameAndTeam(Game game, Team team)
        {
            if (!game.FirstTeam.Name.Equals(team.Name) && !game.SecondTeam.Name.Equals(team.Name))
                throw new ServiceException(team.Name + " does not play in this game!");

            List<Player> allPlayers = this.playerRepository.FindAll().ToList();
            List<ActivePlayer> allActivePlayers = this.GetAll().ToList();

            var result = from players in allPlayers
                         join activePlayers in allActivePlayers on players.ID equals activePlayers.ID.Item1
                         where activePlayers.GameID.Equals(game.ID) && players.Team.Name.Equals(team.Name)
                         select activePlayers;

            return result.ToList();
        }
        public IEnumerable<ActivePlayer> GetAll()
        {
            return this.activePlayerRepository.FindAll().ToList();
        }
    }
}
