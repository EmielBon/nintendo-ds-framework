using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
	class BooleanLiteral : Node
	{
		public String Content
		{
			get;
			private set;
		}

		public BooleanLiteral(String content)
		{
			Content = content;
		}
	}
}
