using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using WavefrontObj;
using System.Diagnostics;
using System.IO;

namespace GameEditor
{
    public class Game1 : Game
    {
        GraphicsDeviceManager graphics;
        Editor editor;
        
        public Game1()
        {
            Instance = this;

            graphics = new GraphicsDeviceManager(this);
            graphics.PreferredBackBufferWidth = 1024;
            graphics.PreferredBackBufferHeight = 768;
            graphics.PreferMultiSampling = true;
            IsMouseVisible = true;
            Window.AllowUserResizing = true;
            graphics.ApplyChanges();
            Content.RootDirectory = "Content";
        }

        protected override void Initialize()
        {
            InputState.Initialize();
            EffectCatalog.Initialize(Content);

            editor = new Editor(this);
            Components.Add(editor);
            
            Window.Title = "Scene Editor 2.0";

            base.Initialize();
        }

        protected override void Update(GameTime gameTime)
        {
            InputState.Update();

            base.Update(gameTime);
        }
        
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.BlendState = BlendState.Opaque;
            GraphicsDevice.DepthStencilState = DepthStencilState.Default;
            GraphicsDevice.RasterizerState = new RasterizerState { CullMode = CullMode.None };
            GraphicsDevice.SamplerStates[0] = SamplerState.LinearWrap;

//             if (objectEditor.Enabled)
//             {
//                 RenderSelectedMeshOutline();
//             }

            base.Draw(gameTime);
        }

        public static Game1 Instance
        {
            get; private set;
        }
    }
}
