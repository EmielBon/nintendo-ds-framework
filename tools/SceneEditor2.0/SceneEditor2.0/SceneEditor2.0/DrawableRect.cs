using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    class DrawableRect
    {
        int[] indices = { 0, 1, 2, 1, 2, 3 };
        
        public DrawableRect(int x1, int y1, int x2, int y2, Color color)
        {
            Vertices = new VertexPositionColor[4];

            Vertices[0].Position = new Vector3(x1, y1, 0);
            Vertices[1].Position = new Vector3(x2, y1, 0);
            Vertices[2].Position = new Vector3(x1, y2, 0);
            Vertices[3].Position = new Vector3(x2, y2, 0);

            for (int i = 0; i < Vertices.Length; ++i)
            {
                Vertices[i].Color = color;
            }
        }

        public VertexPositionColor[] Vertices
        {
            get;
            private set;
        }

        public int[] Indices
        {
            get { return indices; }
        }
    }
}
