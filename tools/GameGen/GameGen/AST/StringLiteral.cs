using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
	class StringLiteral : Node
	{
		public String Content
		{
			get;
			private set;
		}

		public StringLiteral(String content)
		{
			Content = content;
		}
	}
}
