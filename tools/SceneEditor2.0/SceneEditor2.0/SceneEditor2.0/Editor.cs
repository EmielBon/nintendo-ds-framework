using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using GameEditor;
using Microsoft.Xna.Framework.Graphics;
using System.Diagnostics;
using Microsoft.Xna.Framework.Input;
using System.IO;
using WavefrontObj;

namespace GameEditor
{
    partial class Editor : DrawableGameComponent
    {
        public EditorCamera Camera;
        public RailCamera RailCamera;
        public Model3D SelectedModel;
        public List<Model3D> Models;
        public ControlState ControlState;
        
        public Editor(Game game) : base(game)
        {
            Instance = this;
            KeyFrameControl = new KeyFrameControl(game);
            Models = new List<Model3D>();
            SelectedModel = new SimpleModel();
            ControlState = new ControlState();
        }

        public override void Initialize()
        {
            KeyFrameControl.Initialize();

            BackgroundColor = Color.CornflowerBlue;
            Camera = new EditorCamera(new Vector3(12, 12, 12), new Vector3(0, 0, 0), new Vector3(0, 1, 0));
            RailCamera = new RailCamera(new Vector3(2, 4, 1), new Vector3(0, 0, 0), new Vector3(0, 1, 0));

            

            base.Initialize();
        }

        public override void Update(GameTime gameTime)
        {
            Camera.Update();
            ControlState.Update();
            KeyFrameControl.Update(gameTime);
            RailCamera.Update();
            HandleActions();
            HandleHotKeys();
            Animate();

        }

        public static Editor Instance
        {
            get; private set;
        }
    }
}
