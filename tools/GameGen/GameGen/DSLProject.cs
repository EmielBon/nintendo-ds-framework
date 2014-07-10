using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace GameGen
{
    class DSLProject
    {
        public String ProjectRoot;
        public List<CompilationUnit> CompilationUnits = new List<CompilationUnit>();

        public void Generate()
        {
            String genPath     = ProjectRoot + @"\gen";
            String includePath = genPath + @"\include";
            String sourcePath  = genPath + @"\source";

            foreach (var fileName in Directory.EnumerateFiles(ProjectRoot, "*.dsl"))
            {
                if (Path.GetFileName(fileName) == "TypeDefinitions.dsl")
                    continue;
                var sourceFile = CompilationUnit.Parse(fileName, this);
                    CompilationUnits.Add(sourceFile);
            }
            
            /*foreach (CompilationUnit unit in CompilationUnits)
            {
                AddFunctionIfNotDefined(unit.ClassDefinition, "void Initialize");

                String header = source.GenerateHeader();
                String cpp    = source.GenerateCpp();

                foreach (var className in Classes)
                {
                    header = header.Replace(className + "()", String.Format("New<{0}>()", className));
                    cpp    =    cpp.Replace(className + "()", String.Format("New<{0}>()", className));
                }

                foreach (Member member in Members)
                {
                    if (member.Type.MetaType == MetaType.ReferenceType)
                    {
                        header = header.Replace(member.Name + ".", member.Name + "->");
                        header = header.Replace(member.Name + "[", member.Name + "->at(");
                        header = header.Replace("]", ")"); 
                        cpp    =    cpp.Replace(member.Name + ".", member.Name + "->");
                        cpp    =    cpp.Replace(member.Name + "[", member.Name + "->at(");
                        cpp    =    cpp.Replace("]", ")");
                    }
                }

                File.WriteAllText(String.Format(@"{0}\{1}.h",   includePath, source.ClassName), header);
                File.WriteAllText(String.Format(@"{0}\{1}.cpp", sourcePath,  source.ClassName), cpp);
            }

            String typesSource = "#include \"types.h\"\n#include \"GlobalFunctions.h\"\n\n";

            foreach (var namespace_ in Namespaces)
            {
                typesSource += String.Format("#include \"{0}.h\"\n", namespace_);
            }

            typesSource += "\n";
            
            foreach (var className in Classes)
            {
                typesSource += String.Format("class {0};\n", className);
            }

            typesSource += "\n";

            foreach (var namespace_ in Namespaces)
            {
                typesSource += String.Format("using namespace {0};\n", namespace_);
            }

            File.WriteAllText(String.Format(@"{0}\{1}.h", includePath, Name + "Types"), typesSource);

            FormatGeneratedFiles();

            ExportFormattedFiles();*/
        }

        private void FormatGeneratedFiles()
        {
            Process formatter = new Process();
            formatter.StartInfo.FileName = "call_Artistic_Style.bat";
            formatter.StartInfo.Arguments = ProjectRoot + " cpp h";
            formatter.StartInfo.UseShellExecute = false;
            formatter.StartInfo.RedirectStandardOutput = false;
            formatter.Start();
            formatter.WaitForExit();
            formatter.StartInfo.Arguments = ProjectRoot + " h";
            formatter.Start();
            formatter.WaitForExit();
            formatter.Close();

            foreach (var file in Directory.EnumerateFiles(ProjectRoot, "*.orig", SearchOption.AllDirectories))
                File.Delete(file);
        }

        private void ExportFormattedFiles()
        {
            String gen  = ProjectRoot + @"\gen";
            String arm9 = NDSFrameworkHelper.CodeDirectory + @"\arm9";

            CopyDirectoryContents(gen + @"\include", arm9 + @"\include");
            CopyDirectoryContents(gen + @"\source",  arm9 + @"\source");
        }

        private void CopyDirectoryContents(String sourceDir, String destDir)
        {
            foreach (var file in Directory.GetFiles(sourceDir))
                File.Copy(file, destDir + @"\" + Path.GetFileName(file), true);
        }

        public DSLProject(String projectRoot)
        {
            ProjectRoot = projectRoot;
        }

        public String Name
        {
            get { return new DirectoryInfo(ProjectRoot).Name ; }
        }
    }
}
