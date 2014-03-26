using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace GameEditor
{
    class Grid
    {
        VertexPositionColor[] vertices;
        BasicEffect effect;
        GraphicsDevice device;
        Camera camera;

        public Grid(GraphicsDevice device, Camera camera)
        {
            this.device = device;
            this.camera = camera;

            vertices = new VertexPositionColor[17 * 17];
            int counter = 0;

            for (int x = -8; x <= 8; ++x)
            {
                vertices[counter++] = new VertexPositionColor(new Vector3(x, 0, -8), Color.White);
                vertices[counter++] = new VertexPositionColor(new Vector3(x, 0, 8), Color.White);
            }
            for (int y = -8; y <= 8; ++y)
            {
                vertices[counter++] = new VertexPositionColor(new Vector3(-8, 0, y), Color.White);
                vertices[counter++] = new VertexPositionColor(new Vector3(8, 0, y), Color.White);
            }

            effect = new BasicEffect(device);
            effect.LightingEnabled = false;
            effect.TextureEnabled = false;
            effect.VertexColorEnabled = true;
        }

        public void Draw()
        {
            effect.Parameters["WorldViewProj"].SetValue(camera.ViewMatrix * camera.ProjectionMatrix);
            effect.CurrentTechnique.Passes[0].Apply();
            device.DrawUserPrimitives(PrimitiveType.LineList, vertices, 0, vertices.Length / 2);
        }
    }
}
