using System;
using System.Collections.Generic;
using Lab7.Exceptions;
using Lab7.Validator;
using Lab7.Repository;
using Lab7.Domain;
using System.Linq;

namespace Lab7.Service
{
    class TeamService
    {
        private IRepository<int, Team> teamRepository;
        private IValidator<Team> teamValidator;

        public TeamService(IRepository<int, Team> teamRepository, IValidator<Team> teamValidator)
        {
            this.teamRepository = teamRepository;
            this.teamValidator = teamValidator;
        }
        public Team Save(Team entity)
        {
            this.teamValidator.Validate(entity);
            return this.teamRepository.Save(entity);
        }
        public Team GetTeamByName(string name)
        {
            List<Team> teams = this.teamRepository.FindAll().ToList();
            var result = teams.Where(t => t.Name.Equals(name));
            Team resultTeam = result.FirstOrDefault();
            if (resultTeam == null)
                throw new ServiceException("There is no team named " + name);
            return resultTeam;
        }
        public IEnumerable<Team> GetAll()
        {
            return this.teamRepository.FindAll().ToList();
        }
    }
}
