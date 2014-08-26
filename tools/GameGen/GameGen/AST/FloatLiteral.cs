using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
	class FloatLiteral : Node
	{
		public String Content
		{
			get;
			private set;
		}

		public FloatLiteral(String content)
		{
			Content = content;
		}
	}
}
