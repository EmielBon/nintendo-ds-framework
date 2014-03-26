using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Drawing;
using System.Threading;
using System.Globalization;

namespace Model2Bin
{
    class Program
    {
        static void Main(string[] args)
        {
            string input  = Path.GetFullPath(args[0]);
            string output = Path.GetFullPath(args[1]);

            ObjToBin(input, output);
        }

        static void ObjToBin(String inputPath, string outputPath)
        {
            List<Vector3> positions = new List<Vector3>();
            List<Vector3> normals   = new List<Vector3>();
            List<Face>    faces     = new List<Face>();
            List<Vector2> uvs       = new List<Vector2>();

            Thread.CurrentThread.CurrentCulture = new CultureInfo("", false);

            StreamReader file = new StreamReader(inputPath);
            
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
                    case "v":  positions.Add(ReadVector3(tokens)); break;
                    case "vn":   normals.Add(ReadVector3(tokens)); break;
                    case "vt":       uvs.Add(ReadVector2(tokens)); break;
                    case "f":      faces.Add(ReadFace(tokens, positions, normals, null)); break;
                    default: break;
                }
            }

            List<Vertex> vertices = new List<Vertex>();
            List<short>  indices  = new List<short>();

            foreach (Face face in faces)
            {
                foreach (Vertex vertex in face.Vertices)
                {    
                    if (!vertices.Contains(vertex)) 
                        vertices.Add(vertex);
                    indices.Add((short)vertices.IndexOf(vertex));
                }
            }

            WriteToFile(outputPath, vertices, indices);
        }

        static Vector2 ReadVector2(string[] tokens)
        {
            return new Vector2(float.Parse(tokens[1]), float.Parse(tokens[2]));
        }

        static Vector3 ReadVector3(string[] tokens)
        {
            return new Vector3(float.Parse(tokens[1]), float.Parse(tokens[2]), float.Parse(tokens[3]));
        }

        static Face ReadFace(string[] tokens, List<Vector3> positions, List<Vector3> normals, List<Vector2> textureCoordinates)
        {
            Face face = new Face();

            for (int i = 1; i < tokens.Length; ++i) // Each token is a vertex (tuple of position, uv and normal index)
            {
                string[] split = tokens[i].Split('/');

                Vertex vertex = new Vertex();

                switch (split.Length)
                {
                    case 1:
                        vertex.Position = positions[ int.Parse(split[0]) - 1 ];
                        break;
                    case 2:
                        if (split[1] != "")
                            vertex.TextureCoordinates = textureCoordinates[int.Parse(split[1]) - 1];
                        goto case 1;
                    case 3: 
                        if (split[2] != "")
                            vertex.Normal = normals[int.Parse(split[2]) - 1];
                        goto case 2;
                    default: 
                        Console.WriteLine("Parse error: Invalid amount of vertex properties"); 
                        break;
                }

                face.Vertices.Add(vertex);
            }

            return face;
        }

        // Makes a binary format cube.
        // File layout:
        // [Vertex Count] 4 bytes, integer specifying the number of vertices in the model
        // [Vertex Data]  3 * 4 bytes per vertex, 3 floats specifying positional (x,y,z) data of vertices
        // [Normal Data]  3 * 4 bytes per normal, 3 floats specifying directional (x,y,z) data of normals
        // [Index Data]   2 bytes (1 short) per index. Every 3 indices specify a triangle
        // Todo: Assumes the faces are defined after all positions, normals and texture coordinates have been defined, solve by doing 2 scans of the input file
        static void WriteToFile(string outputPath, List<Vertex> vertices, List<short> indices)
        {
            FileStream   stream = new FileStream(outputPath, FileMode.Create);
            BinaryWriter writer = new BinaryWriter(stream);

            writer.Write(vertices.Count);
            
            Console.WriteLine("Writing vertices:\n");

            foreach (Vertex vertex in vertices)
            {
                WriteVector3(writer, vertex.Position);
                WriteVector3(writer, vertex.Normal);
                WriteVector2(writer, vertex.TextureCoordinates);
            }

            Console.WriteLine("\nWriting indices:");

            for (int i = 0; i < indices.Count; ++i)
            {
                writer.Write(indices[i]);
                if (i % 3 == 0) Console.WriteLine();
                Console.Write(indices[i] + " ");
            }

            writer.Close();

            Console.WriteLine("\nFinished!");
        }

        static void WriteVector3(BinaryWriter writer, Vector3 vector)
        {
            writer.Write(vector.x);
            writer.Write(vector.y);
            writer.Write(vector.z);

            Console.WriteLine("x y z : " + vector.x + " " + vector.y + " " + vector.z);
        }

        static void WriteVector2(BinaryWriter writer, Vector2 vector)
        {
            writer.Write(vector.x);
            writer.Write(vector.y);

            Console.WriteLine("u v: " + vector.x + " " + vector.y);
        }
    }
}
