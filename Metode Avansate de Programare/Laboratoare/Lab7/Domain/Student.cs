using System;
using System.Collections.Generic;
using System.Text;

namespace Lab7.Domain
{
    class Student : Entity<int>
    {
        public string Name { get; set; }
        public string School { get; set; }

        public Student(int id, string name, string school)
        {
            this.ID = id;
            this.Name = name;
            this.School = school;
        }
        public Student() { }
        public override string ToString()
        {
            return this.ID + " | " + this.Name + " | " + this.School;
        }
    }
}
