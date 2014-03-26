using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;

namespace WavefrontObj
{
    class ObjectGroup
    {
        public String Name;

        public List<Face> Faces = new List<Face>();
        public List<VertexPositionNormalTexture> Vertices = new List<VertexPositionNormalTexture>();
        public List<int> Indices = new List<int>();

        public ObjectGroup(String name)
        {
            Name = name;
        }

        public void GenerateVerticesAndIndices()
        {
            foreach (Face face in Faces)
            {
                foreach (var vertex in face.Vertices)
                {
                    if (!Vertices.Contains(vertex))
                        Vertices.Add(vertex);
                    Indices.Add((short)Vertices.IndexOf(vertex));
                }
            }
        }
    }
}
