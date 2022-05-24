using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TrackAndField.model;

namespace TrackAndField.repository
{
    interface ICrudRepository<ID, E> where E : Entity<ID>
    {
        /**
         * param: id - the id of the entity to be returned
         *           id must not be null
         * return: the entity with the specified id
         *         or null - if there is no entity with the given id
         */
        E FindOne(ID id);

        /**
         *
         * return: all entities
         */
        IEnumerable<E> FindAll();

        /**
         *
         * param: entity
         *        entity must be not null
         * return: null- if the given entity is saved
         *         otherwise returns the entity (id already exists)
         */
        E Save(E entity);
    }
}
