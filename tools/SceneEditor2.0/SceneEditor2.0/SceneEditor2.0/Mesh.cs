using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    class Mesh
    {
        public VertexBuffer VertexBuffer;
        public IndexBuffer IndexBuffer;
        public BoundingBox BoundingBox;
        public Texture2D Texture;
        public bool WireFrame = false;

        public Mesh(List<VertexPositionNormalTexture> vertices, List<int> indices)
        {
            GraphicsDevice device = Game1.Instance.GraphicsDevice;

            VertexBuffer = new VertexBuffer(device, typeof(VertexPositionNormalTexture), vertices.Count, BufferUsage.WriteOnly);
            IndexBuffer  = new IndexBuffer(device, typeof(int), indices.Count, BufferUsage.WriteOnly);

            VertexBuffer.SetData(vertices.ToArray());
            IndexBuffer.SetData(indices.ToArray());

            BoundingBox = BoundingBoxFromVertices(vertices);
        }

        public void Draw()
        {
            GraphicsDevice device = Game1.Instance.GraphicsDevice;

            var oldState = device.RasterizerState;

            if (WireFrame)
            {
                device.RasterizerState = new RasterizerState { CullMode = CullMode.None, FillMode = FillMode.WireFrame };
            }

            device.SetVertexBuffer(VertexBuffer);
            device.Indices = IndexBuffer;
            device.DrawIndexedPrimitives(PrimitiveType.TriangleList, 0, 0, VertexBuffer.VertexCount, 0, IndexBuffer.IndexCount / 3);

            if (WireFrame)
            {
                device.RasterizerState = oldState;
            }
        }

        public BoundingBox BoundingBoxFromVertices(List<VertexPositionNormalTexture> vertices)
        {
            Vector3 min = new Vector3(float.MaxValue);
            Vector3 max = new Vector3(float.MinValue);

            foreach (var v in vertices)
            {
                Vector3 pos = v.Position;
                if (pos.X < min.X) min.X = pos.X;
                if (pos.Y < min.Y) min.Y = pos.Y;
                if (pos.Z < min.Z) min.Z = pos.Z;
                if (pos.X > max.X) max.X = pos.X;
                if (pos.Y > max.Y) max.Y = pos.Y;
                if (pos.Z > max.Z) max.Z = pos.Z;
            }
            return new BoundingBox(min, max);
        }
    }
}
