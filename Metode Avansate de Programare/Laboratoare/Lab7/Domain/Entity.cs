using System;
using System.Collections.Generic;
using System.Text;

namespace Lab7.Domain
{
    class Entity<TID>
    {
        public TID ID { get; set; }
    }
}
