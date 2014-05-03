using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Value
    {
        public Value(Type type, String value)
        {
            Type  = type;
            Val = value;
        }

        public Type Type;
        public String Val;
    }
}
