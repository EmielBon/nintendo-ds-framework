using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Anything2Bin.Models
{
    class Mesh
    {
        public String Name;

        public List<Face> Faces = new List<Face>();
        public List<Vertex> Vertices = new List<Vertex>();
        public List<short> Indices = new List<short>();

        public Mesh(String name)
        {
            Name = name;
        }

        public void AddFace(string[] tokens)
        {
            Faces.Add(ReadFace(tokens));
        }

        Face ReadFace(string[] tokens)
        {
            Face face = new Face();

            for (int i = 1; i < tokens.Length; ++i) // Each token is a vertex (tuple of position, uv and normal index)
            {
                string[] split = tokens[i].Split('/');

                Vertex vertex = new Vertex();

                switch (split.Length)
                {
                    case 1:
                        vertex.Position = Model2Bin.Positions[int.Parse(split[0]) - 1];
                        break;
                    case 2:
                        if (split[1] != "")
                            vertex.TextureCoordinates = Model2Bin.UVs[int.Parse(split[1]) - 1];
                        goto case 1;
                    case 3:
                        if (split[2] != "")
                            vertex.Normal = Model2Bin.Normals[int.Parse(split[2]) - 1];
                        goto case 2;
                    default:
                        Console.WriteLine("Parse error: Invalid amount of vertex properties");
                        break;
                }

                face.Vertices.Add(vertex);
            }

            return face;
        }

        public void GenerateVerticesAndIndices()
        {
            foreach (Face face in Faces)
            {
                foreach (Vertex vertex in face.Vertices)
                {
                    if (!Vertices.Contains(vertex))
                        Vertices.Add(vertex);
                    Indices.Add((short)Vertices.IndexOf(vertex));
                }
            }
        }
    }
}
