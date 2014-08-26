using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
	class Identifier : Node
	{
		public String Content
		{
			get;
			private set;
		}
		
		public Identifier(String content)
		{
			Content = content;
		}
	}
}
