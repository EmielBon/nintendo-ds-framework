using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
	class IntegerLiteral : Node
	{
		public String Content
		{
			get;
			private set;
		}

		public IntegerLiteral(String content)
		{
			Content = content;
		}
	}
}
