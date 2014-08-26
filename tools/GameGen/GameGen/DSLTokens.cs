using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class DSLTokens
    {
        // Logic
        public static int AND = 0;
		public static int EQ = 1;
		public static int GEQ = 2;
		public static int LEQ = 3;
		public static int NEQ = 4;
		public static int OR = 5;

        // Keywords
        public static int CLASS = 6;
		public static int ELSE = 7;
		public static int FOR = 8;
		public static int IF = 9;
		public static int IN = 10;
		public static int VAR = 11;
		public static int WHILE = 12;
        
        // Literals
		public static int BOOLEANLITERAL = 13;
		public static int FLOATLITERAL = 14;
		public static int INTEGERLITERAL = 15;
		public static int STRINGLITERAL = 16;

        // Special
		public static int IDENTIFIER = 17;
    }
}
