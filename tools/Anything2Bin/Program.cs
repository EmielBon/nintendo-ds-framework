using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.Globalization;
using Anything2Bin.Models;
using System.Text.RegularExpressions;

    class Program
    {
        static void Main(string[] args)
        {
            string inputFile  = Path.GetFullPath(args[0]);
            string outputFile = Path.GetFullPath(args[1]);
            string type = args[2];
            
            Thread.CurrentThread.CurrentCulture = new CultureInfo("", false);

            string prefix = FindLongestCommonPrefix(inputFile, outputFile);
            string relativeInput  = inputFile.Substring(prefix.Length);
            string relativeOutput = outputFile.Substring(prefix.Length);

            Console.WriteLine("Creating " + relativeOutput);
            Console.WriteLine("- Input: " + relativeInput);

            switch (type)
            {
                case "-model":   Model2Bin.ObjToBin(inputFile, outputFile);    break;
                case "-tileset": Image2Bin.TileSet2Bin(inputFile, outputFile); break;
                case "-bitmap":  Image2Bin.Bitmap2Bin(inputFile, outputFile);  break;
                default: Console.WriteLine("Error: Unsupported type");         break;
            }
        }

        static string FindLongestCommonPrefix(string str1, string str2)
        {
            string s1 = (str1.Length <= str2.Length) ? str1 : str2; // Shortest string
            string s2 = (str1.Length >  str2.Length) ? str1 : str2;

            int index = 0;

            while (index < s1.Length)
            {
                if (s1[index] != s2[index])
                    return s1.Substring(0, index - 1);
                index++;
            }
            return s1;
        }
    }
