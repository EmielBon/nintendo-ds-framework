using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameGen
{
    class Program
    {
        static void Main(string[] args)
        {
            GameObject obj = GameObject.Parse(File.ReadAllText(Environment.GetEnvironmentVariable("ARPIGI") + "/ZeldaGameLink.txt"));

            Console.WriteLine("-------" + obj.ClassName + ".h -------\n");
            Console.WriteLine(obj.ExportHeader());
            Console.WriteLine("\n-------" + obj.ClassName + ".cpp -------\n");
            Console.WriteLine(obj.ExportCpp());
            Console.ReadKey();


        }
    }
}
