using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MapEditor
{
    public static class MathHelper
    {
        public static int Clamp(int min, int value, int max)
        {
            return Math.Max(min, Math.Min(value, max));
        }
    }
}
