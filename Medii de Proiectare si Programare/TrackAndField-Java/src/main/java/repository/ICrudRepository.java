package repository;

import model.Entity;

public interface ICrudRepository<ID, E extends Entity<ID>> {
    /**
     *
     * @param id - the id of the entity to be returned
     *           id must not be null
     * @return the entity with the specified id
     *         or null - if there is no entity with the given id
     */
    E findOne(ID id);

    /**
     *
     * @return all entities
     */
    Iterable<E> findAll();

    /**
     *
     * @param entity
     *         entity must be not null
     * @return null- if the given entity is saved
     *         otherwise returns the entity (id already exists)
     */
    E save(E entity);
}
