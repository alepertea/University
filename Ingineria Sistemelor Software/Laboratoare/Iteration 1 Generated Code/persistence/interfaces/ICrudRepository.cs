
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace interfaces{
    public interface ICrudRepository {

        public void FindAll(): IEnumerable<E>();

        /// <summary>
        /// @param id 
        /// @return
        /// </summary>
        public E FindOne(ID id);

        /// <summary>
        /// @param entity 
        /// @return
        /// </summary>
        public void Save(E entity);

        /// <summary>
        /// @param entity 
        /// @return
        /// </summary>
        public void Update(E entity);

        /// <summary>
        /// @param entity 
        /// @return
        /// </summary>
        public void Delete(E entity);

    }
}