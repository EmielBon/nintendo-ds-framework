using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Statement : Node
    {
        public String Content;

        public Statement(String content = "")
        {
            Content = content;
        }

        public virtual string ToString(int depth)
        {
            return GetTabs(depth) + Content;
        }

        public static string GetTabs(int depth)
        {
            string str = "";
            for (int i = 0; i < depth; i++)
                str += "   ";
            return str;
        }
    }
}
