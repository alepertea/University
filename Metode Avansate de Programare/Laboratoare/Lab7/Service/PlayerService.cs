using System;
using System.Collections.Generic;
using Lab7.Exceptions;
using Lab7.Repository;
using Lab7.Domain;
using Lab7.Validator;
using System.Linq;

namespace Lab7.Service
{
    class PlayerService
    {
        private IRepository<int, Player> playerRepository;
        private IValidator<Player> playerValidator;

        public PlayerService(IRepository<int, Player> playerRepository, IValidator<Player> playerValidator)
        {
            this.playerRepository = playerRepository;
            this.playerValidator = playerValidator;
        }
        public IEnumerable<Player> GetAll()
        {
            return this.playerRepository.FindAll().ToList();
        }
        public IEnumerable<Player> GetAllByTeam(Team team)
        {
            List<Player> players = this.GetAll().ToList();
            var result = players.Where(p => p.Team.Name.Equals(team.Name));
            List<Player> resultPlayers = result.ToList();
            if (resultPlayers == null)
                throw new ServiceException("No players.");
            return resultPlayers;
        }
        public Player GetByID(int ID)
        {
            return this.playerRepository.FindOne(ID);
        }
    }
}
