using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WavefrontObj;
using System.IO;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    partial class Editor
    {
        public void LoadModelWithDialog()
        {
            var dialog = new System.Windows.Forms.OpenFileDialog();
            dialog.Filter = "Wavefront OBJ files (*.obj)|*.obj|All files (*.*)|*.*";
            dialog.InitialDirectory = NDSFrameworkHelper.ModelsDirectory;

            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                SimpleModel model = LoadModel(dialog.FileName);
                AddModel(model);
            }
        }

        public SimpleModel LoadModel(string fileName, bool fullPath = true)
        {
            if (!fullPath)
                fileName = NDSFrameworkHelper.ModelsDirectory + @"\" + fileName;

            int modelId = Models.Count;
            for (int i = 0; i < Models.Count; ++i)
            {
                if (Models[i].MarkedForDeletion)
                {
                    modelId = i;
                    break;
                }
            }

            SimpleModel model = Loader.Load(fileName, modelId);

            return model;
        }

        public Model3D AddModel(Model3D model)
        {
            int modelId = Models.Count;
            for (int i = 0; i < Models.Count; ++i)
            {
                if (Models[i].MarkedForDeletion)
                {
                    modelId = i;
                    break;
                }
            }
            
            if (modelId == Models.Count)
                Models.Add(model);
            else
                Models[modelId] = model;

            KeyFrameControl.InsertKeyFrame(model, 0);

            return model;
        }

        void OpenScene()
        {
            var dialog = new System.Windows.Forms.OpenFileDialog();
            dialog.Filter = "Scene files (*.txt)|*.txt";
            dialog.InitialDirectory = NDSFrameworkHelper.ScenesDirectory;

            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                Models = new List<Model3D>();
                SelectedModel = new SimpleModel();

                String file = File.ReadAllText(dialog.FileName);
                String[] lines = file.Split('\n');

                for (int i = 0; i < lines.Length; i++)
                {
                    String currentLine = lines[i].Trim();
                    if (currentLine.Equals("GameObject"))
                    {
                        String gameObject = "";
                        i++;                          // Skip the open bracket
                        int depth = 1;
                        while (depth > 0 && i < lines.Length)
                        {
                            currentLine = lines[++i].Trim();
                            if (currentLine.Equals("{"))
                                depth++;
                            else if (currentLine.Equals("}"))
                                depth--;
                            else
                                gameObject += currentLine + '\n';
                        }
                        Model3D m = ParseGameObject(gameObject);
                    }
                }
            }
        }

        String FilterString(String s, String filter)
        {
            foreach (char c in filter)
            {
                s = s.Replace(c.ToString(), String.Empty);
            }
            return s;
        }

        Model3D ParseGameObject(String s)
        {            
            String[] lines = s.Split('\n');
            for (int i = 0; i < lines.Length; i++ )
            {
                String currentLine = lines[i];
                if (currentLine.StartsWith("keyframe"))
                {
                    Console.WriteLine("\t Keyframe nr: " + currentLine.Substring(8));
                    
                    String[] translation = FilterString(lines[++i].Split('=')[1], "();").Split(',');
                    Console.WriteLine("\t Translation: " + translation[0] + " " + translation[1] + " " + translation[2]);
                    
                    String[] rotation = FilterString(lines[++i].Split('=')[1], "();").Split(',');
                    Console.WriteLine("\t Rotation: " + rotation[0] + " " + rotation[1] + " " + rotation[2]);
                    
                    String[] scaling = FilterString(lines[++i].Split('=')[1], "();").Split(',');
                    Console.WriteLine("\t Scaling: " + scaling[0] + " " + scaling[1] + " " + scaling[2]);
                }
                else
                {
                    String[] tokens = currentLine.Split('=');
                    if (tokens[0].Trim().Equals("id"))
                        Console.WriteLine("ModelId: " + tokens[1].Replace(";", String.Empty));
                    if (tokens[0].Trim().Equals("model"))
                        Console.WriteLine("Add model: " + tokens[1].Replace(";", String.Empty));
                    if (tokens[0].Trim().Equals("solid"))
                        Console.WriteLine("Solid: " + tokens[1].Replace(";", String.Empty));
                }
            }
            return new SimpleModel();
        }

        void SaveScene()
        {
            var dialog = new System.Windows.Forms.SaveFileDialog();
            dialog.DefaultExt = ".txt";
            dialog.Filter = "Scene files (*.txt)|*.txt";
            dialog.InitialDirectory = NDSFrameworkHelper.ScenesDirectory;

            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                StreamWriter writer = new StreamWriter(dialog.FileName);

                foreach (var model in Models)
                {
                    if (model.MarkedForDeletion)
                        continue;

                    writer.Write(model.ToExportFormat());
                }

                writer.Close();
            }
        }
    }
}
