using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    enum TokenType
    {
        Identifier,
        Operator,
        EndOfStatement,
        Symbol,
        Keyword,
        IntegerLiteral,
        FloatLiteral,
        StringLiteral,
        BooleanLiteral,
    }

    class Token
    {
        public string Content = "";
        public TokenType Type;
        public string Name;

        public Token(TokenType type, string name)
        {
            Type = type;
            Name = name;
        }
    }
}
