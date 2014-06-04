using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Function
    {
        public String Name;
        public List<FunctionArgument> Arguments;
        public List<Statement> Body;
        public String ReturnType;

        public void ParseArguments(String arguments)
        {
            if (arguments.Trim() == String.Empty) return;

            Lexer lexer = new Lexer(arguments);
            
            while(lexer.HasNext(3))
            {
                Arguments.Add(new FunctionArgument( lexer.ReadToken(), lexer.ReadToken() ));
                lexer.SkipToken();
            }
            Arguments.Add(new FunctionArgument(lexer.ReadToken(), lexer.ReadToken()));
        }

        public void ParseBody(String body)
        {
            Lexer lexer = new Lexer(body);

            while (lexer.HasNext())
            {
                // Conditional
                if (lexer.PeekToken() == "if")
                {
                    lexer.ReadToken();      // Absorb if
                    String condition = lexer.ReadBlock("(", ")");
                    IfStatement statement = new IfStatement();
                    statement.Condition = new Expression(condition);
                    statement.Body = new Block(lexer.ReadBlock("{", "}"));
                    Body.Add(statement);
                }
                else
                {

                    Statement statement = lexer.ReadUntil(";");
                }
            }
        }
    }
}
