using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Member
    {
        public String Name;
        public String Type;
        public String InitialValue;

        public string ToString(int depth)
        {
            //todo: intitial value
            return String.Format("{0}{1} {2}", Statement.GetTabs(depth), Type, Name);
        }
     }
}
