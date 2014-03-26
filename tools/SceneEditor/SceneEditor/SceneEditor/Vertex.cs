using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace _3DTest
{
    public struct Vertex : IVertexType
    {
        public Vector3 Position;
        public Color Color;
        public Vector3 Normal;

        public Vertex(Vector3 position, Color color, Vector3 normal)
        {
            Position = position;
            Color = color;
            Normal = normal;
        }

        public static VertexElement[] VertexElements = 
        {
            new VertexElement(0, VertexElementFormat.Vector3, VertexElementUsage.Position, 0),
            new VertexElement(sizeof(float)*3, VertexElementFormat.Color, VertexElementUsage.Color, 0),
            new VertexElement(sizeof(float)*3 + 4, VertexElementFormat.Vector3, VertexElementUsage.Normal, 0),
        };

        public readonly static VertexDeclaration VertexDeclaration = new VertexDeclaration(VertexElements);

        VertexDeclaration IVertexType.VertexDeclaration
        {
            get { return VertexDeclaration; }
        }
    }
}
