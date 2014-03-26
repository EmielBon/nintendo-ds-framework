using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using System.Globalization;

namespace Anything2Bin.Models
{
    class Model2Bin
    {
        public static List<Vector3> Positions = new List<Vector3>();
        public static List<Vector3> Normals = new List<Vector3>();
        public static List<Vector2> UVs = new List<Vector2>();
        
        public static void ObjToBin(String inputFile, String outputFile)
        {
            String modelName = Path.GetFileNameWithoutExtension(inputFile);
            String outputDir = Path.GetDirectoryName(outputFile) + @"\";
            String meshPrefix = "mesh_";

            List<Mesh> meshes = new List<Mesh>();
            Mesh currentMesh  = null;
            StreamReader file = new StreamReader(inputFile);
            
            while (true)
            {
                // Read a line
                string line = file.ReadLine();
                
                if (line == null)
                    break;

                if (line == "")
                    continue;

                String[] tokens = line.Split(' ');

                switch (tokens[0])
                {
                    case "v":  Positions.Add(ReadVector3(tokens)); break;
                    case "vn": Normals.Add(ReadVector3(tokens)); break;
                    case "vt": UVs.Add(ReadVector2(tokens)); break;
                    case "f":  if (currentMesh == null)
                               {
                                  currentMesh = new Mesh(meshPrefix + modelName); // First mesh has just the name of the model
                                  meshes.Add(currentMesh);
                               }
                               currentMesh.AddFace(tokens); 
                               break;
                    case "o":  currentMesh = new Mesh(meshPrefix + modelName + "_" + tokens[1]);
                               meshes.Add(currentMesh);
                               break;
                    default:   break;
                }
            }

            WriteDescriptor(modelName, meshes, outputDir);
            WriteToFile(outputDir, meshes);
        }

        static Vector2 ReadVector2(string[] tokens)
        {
            return new Vector2(float.Parse(tokens[1]), float.Parse(tokens[2]));
        }

        static Vector3 ReadVector3(string[] tokens)
        {
            return new Vector3(float.Parse(tokens[1]), float.Parse(tokens[2]), float.Parse(tokens[3]));
        }

        static void WriteDescriptor(String modelName, List<Mesh> meshes, String outputDir)
        {
            StreamWriter writer = new StreamWriter(outputDir + modelName + ".bin");

            foreach (Mesh mesh in meshes)
            {
                writer.WriteLine(mesh.Name + " " + "no_texture" /*"mesh.Texture.Name"*/);
            }

            writer.Close();
        }

        // Makes a binary format cube.
        // File layout:
        // [Vertex Count] 4 bytes, integer specifying the number of vertices in the model
        // [Vertex Data]  3 * 4 bytes per vertex, 3 floats specifying positional (x,y,z) data of vertices
        // [Normal Data]  3 * 4 bytes per normal, 3 floats specifying directional (x,y,z) data of normals
        // [Index Data]   2 bytes (1 short) per index. Every 3 indices specify a triangle
        // Todo: Assumes the faces are defined after all positions, normals and texture coordinates have been defined, solve by doing 2 scans of the input file
        static void WriteToFile(String outputDir, List<Mesh> meshes)
        {
            int counter = 1;

            foreach (Mesh mesh in meshes)
            {
                Console.WriteLine("- Mesh " + counter + " " + mesh.Name);
                WriteMesh(outputDir, mesh);
            }
        }

        static void WriteMesh(String outputDir, Mesh mesh)
        {
            FileStream stream = new FileStream(outputDir + mesh.Name + ".bin", FileMode.Create);
            BinaryWriter output = new BinaryWriter(stream);

            mesh.GenerateVerticesAndIndices();

            List<Vertex> vertices = mesh.Vertices;
            List<short> indices   = mesh.Indices;
           
            output.Write(vertices.Count);
            //output.Write(indices.Count);

            Console.Write("- Vertices: " + vertices.Count);

            foreach (Vertex vertex in vertices)
            {
                WriteVector3(output, vertex.Position);
                WriteVector3(output, vertex.Normal);
                WriteVector2(output, vertex.TextureCoordinates);
            }

            Console.Write("- Indices: " + indices.Count);

            for (int i = 0; i < indices.Count; ++i)
                output.Write(indices[i]);

            Console.WriteLine(" done");
            output.Close();
        }

        static void WriteVector3(BinaryWriter output, Vector3 vector)
        {
            output.Write(vector.x);
            output.Write(vector.y);
            output.Write(vector.z);
        }

        static void WriteVector2(BinaryWriter output, Vector2 vector)
        {
            output.Write(vector.x);
            output.Write(vector.y);
        }

    }
}
