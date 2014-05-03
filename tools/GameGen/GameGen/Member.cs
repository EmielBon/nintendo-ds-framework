using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    abstract class Member
    {
        public String Name;
        public Type Type;
        protected Value initialValue;

        abstract public Value InitialValue { get; set; }
    }
}
