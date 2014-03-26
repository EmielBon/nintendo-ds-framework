using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using GameEditor;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;

namespace WavefrontObj
{
    class Loader
    {
        public static List<Vector3> Positions;
        public static List<Vector3> Normals;
        public static List<Vector2> UVs;

        public static SimpleModel Load(string inputFile, int modelId)
        {
            Positions = new List<Vector3>();
            Normals = new List<Vector3>();
            UVs = new List<Vector2>();
            
            String[] text = File.ReadAllText(inputFile).Split(System.Environment.NewLine.ToCharArray());
            
            String modelName = Path.GetFileNameWithoutExtension(inputFile);
            
            List<ObjectGroup> meshes = new List<ObjectGroup>();
            Dictionary<string, string> textureBindings = new Dictionary<string, string>();

            ObjectGroup currentMesh = null;
            var model = new GameEditor.SimpleModel(modelId, modelName);

            foreach (string line in text)
            {
                string[] tokens = line.Trim().Split(' ');

                if (tokens[0] == "")
                    continue;

                switch (tokens[0])
                {
                    case "v":  Positions.Add(ReadVector3(tokens)); break;
                    case "vn": Normals.Add(ReadVector3(tokens)); break;
                    case "vt": UVs.Add(ReadVector2(tokens)); break;
                    case "f":  if (currentMesh == null)
                               {
                                   currentMesh = new ObjectGroup(modelName); // First mesh has just the name of the model
                                   meshes.Add(currentMesh);
                               }
                               currentMesh.Faces.Add( ReadFace(tokens) );
                               break;
                    case "o":  currentMesh = new ObjectGroup(tokens[1]);
                               meshes.Add(currentMesh);
                               break;
                    case "#":  if (tokens[1] == "texture")
                               {
                                   textureBindings.Add(tokens[2], tokens[3]);
                               }
                               break;
                    default:   break;
                }
            }

            foreach (var mesh in meshes)
            {
                mesh.GenerateVerticesAndIndices();

                var vertices = mesh.Vertices;
                var indices = mesh.Indices;

                var _mesh = new GameEditor.Mesh(vertices, indices);

                string texturesFolder = Path.GetDirectoryName(inputFile) + @"\..\textures\";

                string textureName = textureBindings.ContainsKey(mesh.Name) ? textureBindings[mesh.Name] : "no_texture";
                
                FileStream stream = File.OpenRead(texturesFolder + textureName + ".png");
                _mesh.Texture = Texture2D.FromStream(Game1.Instance.GraphicsDevice, stream);
                stream.Close();

                model.AddMesh(_mesh);
            }

            //Console.WriteLine("Meshes: " + model.Meshes.Count + " Vertices: " + model.Meshes[0].VertexBuffer.VertexCount);
            model.bbox = model.BoundingBoxFromMeshes();            
            return model;
        }

        static Vector2 ReadVector2(string[] tokens)
        {
            return new Vector2(float.Parse(tokens[1]), float.Parse(tokens[2]));
        }

        static Vector3 ReadVector3(string[] tokens)
        {
            return new Vector3(float.Parse(tokens[1]), float.Parse(tokens[2]), float.Parse(tokens[3]));
        }

        static Face ReadFace(string[] tokens)
        {
            Face face = new Face();

            for (int i = 1; i < tokens.Length; ++i) // Each token is a vertex (tuple of position, uv and normal index)
            {
                string[] split = tokens[i].Split('/');

                var vertex = new VertexPositionNormalTexture();

                switch (split.Length)
                {
                    case 1:
                        vertex.Position = Positions[int.Parse(split[0]) - 1];
                        //Console.WriteLine(vertex.Position);
                        break;
                    case 2:
                        if (split[1] != "")
                            vertex.TextureCoordinate = UVs[int.Parse(split[1]) - 1];
                        goto case 1;
                    case 3:
                        if (split[2] != "")
                            vertex.Normal = Normals[int.Parse(split[2]) - 1];
                        goto case 2;
                    default:
                        Console.WriteLine("Parse error: Invalid amount of vertex properties");
                        break;
                }

                face.Vertices.Add(vertex);
            }

            return face;
        }
    }
}
