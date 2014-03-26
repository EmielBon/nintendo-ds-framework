using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using System.Diagnostics;

namespace GameEditor
{
    partial class Editor
    {
        public RenderTarget2D NormalRender;
        public RenderTarget2D MeshIdRender;
        public RenderTarget2D UIRender;
        public Color BackgroundColor;

        SpriteBatch spriteBatch;
        BasicEffect normalRenderingEffect;
        Grid grid;

        protected override void LoadContent()
        {
            NormalRender = RenderTargetFactory.CreateRenderTarget(GraphicsDevice, 1, true);
            MeshIdRender = RenderTargetFactory.CreateRenderTarget(GraphicsDevice, 1, false);
            UIRender = RenderTargetFactory.CreateRenderTarget(GraphicsDevice, 1, true);

            grid = new Grid(GraphicsDevice, Camera);

            normalRenderingEffect = new BasicEffect(GraphicsDevice);
            normalRenderingEffect.TextureEnabled = true;

            spriteBatch = new SpriteBatch(GraphicsDevice);

            base.LoadContent();
        }

        public override void Draw(GameTime gameTime)
        {
            PrepareSelection();
            DrawModelsAndGrid();

            GraphicsDevice.SetRenderTarget(UIRender);
            GraphicsDevice.Clear(Color.Transparent);
            KeyFrameControl.Draw(gameTime);
            GraphicsDevice.SetRenderTarget(null);

            spriteBatch.Begin();
            spriteBatch.Draw(NormalRender, GraphicsDevice.Viewport.Bounds, Color.White);
            spriteBatch.Draw(UIRender, GraphicsDevice.Viewport.Bounds, Color.White);
            spriteBatch.End();
        }

        public void DrawModelsAndGrid()
        {
            GraphicsDevice.SetRenderTarget(NormalRender);
            GraphicsDevice.Clear(ClearOptions.Target | ClearOptions.DepthBuffer, BackgroundColor, 1.0f, 0);
            RenderModels();
            RenderSelectedModelOutline();

            grid.Draw();
            GraphicsDevice.SetRenderTarget(null);
        }

        void RenderModels()
        {
            foreach (var model in Models)
            {
                if (!model.Visible)
                    continue;

                normalRenderingEffect.Parameters["WorldViewProj"].SetValue(model.TransformationMatrix * Camera.ViewMatrix * Camera.ProjectionMatrix);

                foreach (var mesh in model.Meshes)
                {
                    normalRenderingEffect.Parameters["Texture"].SetValue(mesh.Texture);

                    foreach (EffectPass pass in normalRenderingEffect.CurrentTechnique.Passes)
                    {
                        pass.Apply();
                        mesh.Draw();
                    }
                }
            }
        }

        void RenderModelIds()
        {
            Effect effect = EffectCatalog.ColorEffect;

            foreach (var model in Models)
            {
                var meshes = model.Meshes;

                if (!model.Visible)
                    continue;

                Debug.Assert(model.Id >= 0 && model.Id < 256, "Color ID out of bounds");
                effect.Parameters["WorldViewProj"].SetValue(model.TransformationMatrix * Camera.ViewMatrix * Camera.ProjectionMatrix);

                for (int i = 0; i < meshes.Count; ++i)
                {
                    effect.Parameters["Color"].SetValue(new Color(model.Id, i, 0, 1).ToVector4());
                    effect.CurrentTechnique.Passes[0].Apply();
                    meshes[i].Draw();
                }
            }
        }

        void RenderSelectedModelOutline()
        {
            Effect effect = EffectCatalog.ColorEffect;
            RasterizerState oldState = GraphicsDevice.RasterizerState;
            GraphicsDevice.RasterizerState = new RasterizerState { FillMode = FillMode.WireFrame, CullMode = CullMode.CullCounterClockwiseFace };

            var model = SelectedModel;

            if (!model.Visible)
                return;

            effect.Parameters["WorldViewProj"].SetValue(model.TransformationMatrix * Camera.ViewMatrix * Camera.ProjectionMatrix);
            effect.Parameters["Color"].SetValue(Color.Yellow.ToVector4());

            foreach (var mesh in model.Meshes)
            {
                effect.CurrentTechnique.Passes[0].Apply();
                mesh.Draw();
            }

            GraphicsDevice.RasterizerState = oldState;
        }

        public void PrepareSelection()
        {
            GraphicsDevice.SetRenderTarget(MeshIdRender);
            GraphicsDevice.Clear(ClearOptions.Target | ClearOptions.DepthBuffer, Color.White, 1.0f, 0);
            RenderModelIds();
            GraphicsDevice.SetRenderTarget(null);
        }

        /*void RenderSelectedMeshOutline()
        {
            var mesh   = objectEditor.SelectedMesh;
            var effect = EffectCatalog.ColorEffect;

            if (mesh == null)
                return;
            
            RasterizerState oldState = GraphicsDevice.RasterizerState;

            GraphicsDevice.RasterizerState = new RasterizerState { FillMode = FillMode.WireFrame, CullMode = CullMode.CullCounterClockwiseFace };

            effect.Parameters["WorldViewProj"].SetValue(SelectedModel.TransformationMatrix * Camera.ViewMatrix * Camera.ProjectionMatrix);
            effect.Parameters["Color"].SetValue(Color.Yellow.ToVector4());

            effect.CurrentTechnique.Passes[0].Apply();
            mesh.Draw();

            GraphicsDevice.RasterizerState = oldState;
        }*/
    }
}
