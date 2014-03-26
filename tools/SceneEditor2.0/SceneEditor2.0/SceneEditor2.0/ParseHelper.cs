using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    static class ParseHelper
    {
        public static String FormatVector3(Vector3 input)
        {
            return String.Format("({0}, {1}, {2})", input.X, input.Y, input.Z);
        }

        public static Vector3 ParseVector3(String input)
        {
            String[] filterTokens = {"{", "}", "(", ")", ";"};
            String filtered = RemoveSubstrings(input, filterTokens);
            filtered = filtered.Replace(',', ' ');
            String[] elements = filtered.Split(' ');
            Vector3 result = new Vector3();
            result.X = float.Parse(elements[0]);
            result.Y = float.Parse(elements[1]);
            result.Z = float.Parse(elements[2]);
            return result;
        }

        public static String RemoveSubstrings(String input, String[] subStrings)
        {
            String filtered = input;
            foreach (var subString in subStrings)
            {
                filtered = filtered.Replace(subString, "");
            }
            return filtered;
        }
    }
}
