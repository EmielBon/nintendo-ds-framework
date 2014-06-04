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
            string path = args[0];// Environment.GetEnvironmentVariable("ARPIGI");
            DSLProject project = new DSLProject(path);
            File.WriteAllText(includePath + @"\GameGenProject.h", String.Format("#pragma once\n\n#include \"{0}.h\"\n\nusing GameGenProject = {0};", Name));
            project.Generate();
        }
    }
}