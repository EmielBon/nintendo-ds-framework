using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace GameGen
{
	class Lexer2 : DSLTokens
	{
		static Dictionary<String, int> Symbols;

		static Lexer2()
		{
			Symbols = new Dictionary<string, int>();
			Symbols.Add("class", CLASS);
			Symbols.Add("else", ELSE);
			Symbols.Add("for", FOR);
			Symbols.Add("if", IF);
			Symbols.Add("in", IN);
			Symbols.Add("var", VAR);
			Symbols.Add("while", WHILE);
		}

		string source;
		char c;
		int index = -1;

		public int Token
		{
			get;
			private set;
		}

		public Node Semantic
		{
			get;
			private set;
		}

		public Lexer2(String source)
		{
			this.source = source;
			Token = -1;
			NextChar();
		}

		void NextChar()
		{
			if (++index < source.Length)
				c = source[index];
		}

		public int ReadToken()
		{
			//string[]   symbols   = { "(", ")", "{", "}", "[", "]", "<", ">", ".", ",", ";", "\"", "'", " "};
			bool inComment = false;
			String data = "";
			while (index < source.Length)
			{
				// Skip whitespace
				while (c == ' ' || c == '\t' || c == '\n' || c == '\r')
					NextChar();

				switch (c)
				{
					// Statement end
					case ';':
						NextChar();
						return Token = ';';

					// Block tokens
					case '}':
						NextChar();
						return Token = '}';
					case '{':
						NextChar();
						return Token = '{';

					// Parenthesis
					case ')':
						NextChar();
						return Token = ')';
					case '(':
						NextChar();
						return Token = '(';

					// End of multiline comment (*/) token, or arithmetic multiplication (*) token
					case '*':
						{
							NextChar();
							if (inComment && c == '/')
							{
								inComment = false;
								NextChar();
								continue;
							}
							return Token = '*';
						}

					// Arithmetic addition (+) token
					case '+':
						NextChar();
						return Token = '+';

					// Arithmetic subtraction (-) token
					case '-':
						NextChar();
						return Token = '-';

					// Logical AND (&&) token
					case '&':
						NextChar();
						if (c == '&')
						{
							NextChar();
							return Token = AND;
						}
						throw new Exception("Unexpected character: " + (char)c);

					// Logical OR (||) token
					case '|':
						NextChar();
						if (c == '|')
						{
							NextChar();
							return Token = OR;
						}
						throw new Exception("Unexpected character: " + (char)c);

					// Logical NOT (!) token
					case '!':
						NextChar();
						return Token = '!';

					// Relational < and LEQ (<=) tokens
					case '<':
						NextChar();
						if (c == '=')
						{
							NextChar();
							return Token = LEQ;
						}
						return Token = '<';

					// Relational EQ (==) token
					case '=':
						NextChar();
						if (c == '=')
						{
							NextChar();
							return Token = EQ;
						}
						return Token = '=';

					// Relational > and GEQ (>=) tokens
					case '>':
						NextChar();
						if (c == '=')
						{
							NextChar();
							return Token = GEQ;
						}
						return Token = '>';

					// String literal
					case '"':
						data = "";
						do
						{
							data += c;
							NextChar();
						}
						while (c != '"');
						data += c;
						NextChar();
						Semantic = new StringLiteral(data);
						return Token = STRINGLITERAL;

					default:
						// Numerical literal                    
						if (Char.IsDigit(c))
						{
							data = "";
							int dots = 0;
							while (true)
							{
								if (Char.IsDigit(c))
									data += Char.GetNumericValue(c);
								else if (c == '.')
								{
									data += '.';
									dots++;
								}
								else
									break;
								NextChar();
							}
							if (dots == 0)
							{
								Semantic = new IntegerLiteral(data);
								return Token = INTEGERLITERAL;
							}
							else if (dots == 1)
							{
								Semantic = new FloatLiteral(data);
								return Token = FLOATLITERAL;
							}

						}
						if (Char.IsLetter(c))
						{
							data = "";
							do
							{
								data += c;
								NextChar();
							}
							while (Char.IsLetterOrDigit(c));
							// Boolean literal                                    
							if (data == "true" || data == "false")
							{
								Semantic = new BooleanLiteral(data);
							}
							// Keyword
							if (Symbols.ContainsKey(data))
								return Token = Symbols[data];

							Semantic = new Identifier(data);
							return Token = IDENTIFIER;
						}
						throw new Exception("Unexpected character: " + (char)c);
				}
			}
			return Token = -1;
		}
	}
}


            /*
            operators[ 0] = new string[]{ "++", "--", "." };
            operators[ 1] = new string[]{ "-", "!", "~" };
            operators[ 2] = new string[]{ "*", "/", "%" };
            operators[ 3] = new string[]{ "+", "-" };
            operators[ 4] = new string[]{ "<<", ">>" };
            operators[ 5] = new string[]{ "<", "<=", ">", ">=" };
            operators[ 6] = new string[]{ "==", "!=" };
            operators[ 7] = new string[]{ "&" };
            operators[ 8] = new string[]{ "^" };
            operators[ 9] = new string[]{ "|" };
            operators[10] = new string[]{ "&&" };
            operators[11] = new string[]{ "||" };
            operators[12] = new string[]{ "=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|=" };
            operators[13] = new string[]{ "," };
			*/
