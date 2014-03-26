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

namespace _3DTest
{
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        GraphicsDevice device;
        SpriteBatch spriteBatch;
        BasicEffect effect;

        public List<Model3D> models;
        public Model3D selectedModel;
        public Camera camera;

        RenderTarget2D renderTarget;
        Texture2D targetMap;

        Vector3 oldTrans;
        Vector3 oldScale;
        Vector3 oldRotate;

        Vertex[] grid;

        int mode = Mode.None;

        int mouseX, mouseY;

        IntPtr drawSurface;
        SceneEditor parentForm;
        System.Windows.Forms.PictureBox pictureBox;
        System.Windows.Forms.Control gameForm;

        public Game1(IntPtr drawSurface, SceneEditor parentForm, System.Windows.Forms.PictureBox pictureBox)
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            this.drawSurface = drawSurface;
            this.parentForm = parentForm;
            this.pictureBox = pictureBox;

            graphics.PreparingDeviceSettings += new EventHandler<PreparingDeviceSettingsEventArgs>(graphics_PreparingDeviceSettings);
            Mouse.WindowHandle = drawSurface;

            gameForm = System.Windows.Forms.Control.FromHandle(this.Window.Handle);
            gameForm.VisibleChanged += new EventHandler(gameForm_Hide);
        }

        protected override void Initialize()
        {
            models = new List<Model3D>();
            graphics.PreferredBackBufferWidth = 600;
            graphics.PreferredBackBufferHeight = 600;
            graphics.IsFullScreen = false;
            graphics.SynchronizeWithVerticalRetrace = false;
            graphics.ApplyChanges();

            this.IsFixedTimeStep = false;
            base.Initialize();
        }

        protected override void LoadContent()
        {
            device = graphics.GraphicsDevice;

            PresentationParameters pp = device.PresentationParameters;
            renderTarget = new RenderTarget2D(device, 600, 600, true, device.DisplayMode.Format, DepthFormat.Depth24);

            spriteBatch = new SpriteBatch(device);
            effect = new BasicEffect(device);
            //effect.VertexColorEnabled = true;
            effect.LightingEnabled = true;
            effect.DirectionalLight0.Enabled = true;
            effect.DirectionalLight0.DiffuseColor = Color.White.ToVector3();
            effect.DirectionalLight0.Direction = new Vector3(0, -1, 0);
            effect.AmbientLightColor = new Vector3(0.3f);
            camera = new Camera(new Vector3(0, 15, 20), new Vector3(0, 0, 0), new Vector3(0, 1, 0));
            SetupGrid(new Vector3(-5, 0, -5), new Vector3(5, 0, 5), 10);
        }

        protected override void Update(GameTime gameTime)
        {
            float timeStep = (float)gameTime.ElapsedGameTime.TotalSeconds * 60.0f;
            float deltaAngleY = 0.0f;

            KeyboardState keyState = Keyboard.GetState();
            MouseState mouseState = Mouse.GetState();

            if (mode != Mode.None)
            {
                if (selectedModel == null) { mode = Mode.None; return; }
                if (mouseState.LeftButton == ButtonState.Pressed)
                {
                    mode = Mode.None;
                    return;
                }
                if (mouseState.RightButton == ButtonState.Pressed)
                {
                    selectedModel.translate = oldTrans;
                    selectedModel.scale = oldScale;
                    selectedModel.rotate = oldRotate;
                    mode = Mode.None;
                    return;
                }
                if (mode == Mode.Translate || mode == Mode.Rotate || mode == Mode.Scale)
                {
                    if (keyState.IsKeyDown(Keys.X))
                        mode -= 9;
                    else if (keyState.IsKeyDown(Keys.Y))
                        mode -= 8;
                    else if (keyState.IsKeyDown(Keys.Z))
                        mode -= 7;
                    return;
                }
                if (mode == Mode.TranslateX || mode == Mode.TranslateY || mode == Mode.TranslateZ)
                {
                    Vector3 translate = new Vector3(0);

                    if (mode == Mode.TranslateX)
                        translate.X = (mouseState.X - mouseX) / 20.0f;
                    else if (mode == Mode.TranslateY)
                        translate.Y = (mouseState.X - mouseX) / 20.0f;
                    else if (mode == Mode.TranslateZ)
                        translate.Z = (mouseState.X - mouseX) / 20.0f;
                    selectedModel.translate = oldTrans + translate;
                }
                else if (mode == Mode.ScaleX)
                {
                    double startDistance = Math.Sqrt(Math.Pow(mouseX - 300, 2) + Math.Pow((mouseY - 300), 2));
                    double distance = Math.Sqrt(Math.Pow(mouseState.X - 300, 2) + Math.Pow((mouseState.Y - 300), 2));

                    selectedModel.Scale((new Vector3((float)(distance / startDistance)) * oldScale));
                }
                else if (mode == Mode.RotateX)
                {
                    double distance = Math.Sqrt(Math.Pow(mouseState.X - mouseX, 2) + Math.Pow((mouseState.Y - mouseY), 2));
                    selectedModel.RotateX((int)(oldRotate.X - distance));
                }
                else if (mode == Mode.RotateY)
                {
                    double distance = Math.Sqrt(Math.Pow(mouseState.X - mouseX, 2) + Math.Pow((mouseState.Y - mouseY), 2));
                    selectedModel.RotateY((int)(oldRotate.Y - distance));
                }
                else if (mode == Mode.RotateZ)
                {
                    double distance = Math.Sqrt(Math.Pow(mouseState.X - mouseX, 2) + Math.Pow((mouseState.Y - mouseY), 2));
                    selectedModel.RotateZ((int)(oldRotate.Z - distance));
                }
                return;
            }
            float scale = 1.0f;
            float dx = 0;
            float dy = 0;

            if (keyState.IsKeyDown(Keys.Right))         // Rotate camera left/right
                deltaAngleY = 0.05f * timeStep;
            if (keyState.IsKeyDown(Keys.Left))
                deltaAngleY = -0.05f * timeStep;

            if (keyState.IsKeyDown(Keys.Up))            // Scale camera
                scale -= 0.025f * timeStep;
            if (keyState.IsKeyDown(Keys.Down))
                scale += 0.025f * timeStep;
            /*
            if (keyState.IsKeyDown(Keys.W))             // Pan camera
                dy += 0.05f * timeStep;
            if (keyState.IsKeyDown(Keys.S))
                dy -= 0.05f * timeStep;
            if (keyState.IsKeyDown(Keys.A))
                dx -= 0.05f * timeStep;
            if (keyState.IsKeyDown(Keys.D))
                dx += 0.05f * timeStep;
            */
            if (keyState.IsKeyDown(Keys.G))
            {
                if (selectedModel == null) return;
                mode = Mode.Translate;
                mouseX = mouseState.X;
                oldTrans = selectedModel.translate;
                oldScale = selectedModel.scale;
                oldRotate = selectedModel.rotate;
            }
            if (keyState.IsKeyDown(Keys.S))
            {
                if (selectedModel == null) return;
                mode = Mode.ScaleX;
                mouseX = mouseState.X;
                mouseY = mouseState.Y;
                oldTrans = selectedModel.translate;
                oldScale = selectedModel.scale;
                oldRotate = selectedModel.rotate;
            }
            if (keyState.IsKeyDown(Keys.R))
            {
                if (selectedModel == null) return;
                mode = Mode.Rotate;
                mouseX = mouseState.X;
                mouseY = mouseState.Y;
                oldTrans = selectedModel.translate;
                oldScale = selectedModel.scale;
                oldRotate = selectedModel.rotate;
            }
            if (keyState.IsKeyDown(Keys.LeftAlt) && keyState.IsKeyDown(Keys.H))
            {
                foreach (Model3D m in models)
                    m.visible = true;
            }
            else if (keyState.IsKeyDown(Keys.H))
            {
                if (selectedModel == null) return;
                selectedModel.visible = false;
            }
            if (keyState.IsKeyDown(Keys.LeftShift) && keyState.IsKeyDown(Keys.X))
            {
                if (selectedModel == null) return;
                int i = models.IndexOf(selectedModel);
                models.RemoveAt(i);
                parentForm.models.RemoveAt(i);
                parentForm.modelList.Items.RemoveAt(i);
                selectedModel = null;
            }
            if (keyState.IsKeyDown(Keys.LeftShift) && keyState.IsKeyDown(Keys.A))
            {
                parentForm.LoadModel();
            }
            if (keyState.IsKeyDown(Keys.LeftControl) && keyState.IsKeyDown(Keys.E))
            {
                parentForm.Export();
            }
            if (keyState.IsKeyDown(Keys.LeftControl) && keyState.IsKeyDown(Keys.I))
            {
                parentForm.Import();
            }
            if (mouseState.RightButton == ButtonState.Pressed)
            {
                device.SetRenderTarget(renderTarget);
                device.Clear(Color.Black);
                int i = 1;
                int x = mouseState.X;
                int y = mouseState.Y;
                Effect e = Content.Load<Effect>("Target");
                foreach (Model3D m in models)
                {
                    m.model.Meshes[0].MeshParts[0].Effect = e;
                    ModelMesh mesh = m.model.Meshes[0];

                    Matrix[] transforms = new Matrix[m.model.Bones.Count];
                    m.model.CopyAbsoluteBoneTransformsTo(transforms);

                    e.CurrentTechnique = e.Techniques["Target"];

                    e.Parameters["World"].SetValue(m.GetWorld(mesh));
                    e.Parameters["View"].SetValue(camera.ViewMatrix);
                    e.Parameters["Projection"].SetValue(camera.ProjectionMatrix);
                    e.Parameters["Color"].SetValue(50.0f * i);

                    i++;
                    mesh.Draw();
                    m.model.Meshes[0].MeshParts[0].Effect = effect;
                }
                device.SetRenderTarget(null);
                targetMap = renderTarget;
                Color[] mapColors = new Color[targetMap.Width * targetMap.Height];
                targetMap.GetData<Color>(mapColors);
                if (mapColors[y * 600 + x].R > 0)
                    selectedModel = models[mapColors[y * 600 + x].B / 50 - 1];
            }

            camera.Eye += new Vector3(dx, dy, 0);
            camera.Focus += new Vector3(dx, dy, 0);
            camera.Eye = Vector3.Transform(camera.Eye, Matrix.CreateRotationY(deltaAngleY));
            camera.Eye = Vector3.Transform(camera.Eye, Matrix.CreateScale(scale));

            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            device.RasterizerState = new RasterizerState() { CullMode = CullMode.None };
            device.Clear(ClearOptions.Target | ClearOptions.DepthBuffer, Color.DarkGray, 1.0f, 0);
            effect.Projection = camera.ProjectionMatrix;
            effect.View = camera.ViewMatrix;

            effect.World = Matrix.Identity;
            foreach (EffectPass pass in effect.CurrentTechnique.Passes)
            {
                pass.Apply();
                if (parentForm.showGrid.Checked)
                    device.DrawUserPrimitives<Vertex>(PrimitiveType.LineList, grid, 0, grid.Count() / 2, Vertex.VertexDeclaration);
                foreach (Model3D m in models)
                    m.Draw(camera);
            }
            base.Draw(gameTime);
        }


        public void addModel(String file)
        {
            Model3D m = new Model3D();
            m.model = Content.Load<Model>(file);
            m.visible = true;
            m.name = file;
            models.Add(m);
        }

        protected void SetupGrid(Vector3 start, Vector3 end, int n)
        {
            grid = new Vertex[4 * n + 6];

            Vector3 delta = (end - start) / n;
            Console.WriteLine(delta);
            for (int i = 0; i < n + 1; i++)
            {
                if (i == n / 2)
                {
                    grid[4 * i].Color = Color.Red;
                    grid[4 * i + 1].Color = Color.Red;
                    grid[4 * i + 2].Color = Color.Green;
                    grid[4 * i + 3].Color = Color.Green;
                }
                else
                {
                    grid[4 * i].Color = Color.DarkGray;
                    grid[4 * i + 1].Color = Color.DarkGray;
                    grid[4 * i + 2].Color = Color.DarkGray;
                    grid[4 * i + 3].Color = Color.DarkGray;
                }
                grid[4 * i].Position = new Vector3(start.X, 0, start.Z + delta.Z * i);
                grid[4 * i].Normal = new Vector3(0.1f, 0.1f, 0.1f);
                grid[4 * i + 1].Position = new Vector3(end.X, 0, start.Z + delta.Z * i);
                grid[4 * i + 1].Normal = new Vector3(0.1f, 0.1f, 0.1f);
                grid[4 * i + 2].Position = new Vector3(start.X + delta.X * i, 0, start.Z);
                grid[4 * i + 2].Normal = new Vector3(0.1f, 0.1f, 0.1f);
                grid[4 * i + 3].Position = new Vector3(start.X + delta.X * i, 0, end.Z);
                grid[4 * i + 3].Normal = new Vector3(0.1f, 0.1f, 0.1f);
            }
            grid[4 * n + 4].Position = new Vector3(0, 0, 0);
            grid[4 * n + 4].Normal = new Vector3(0.1f, 0.1f, 0.1f);
            grid[4 * n + 4].Color = Color.Blue;
            grid[4 * n + 5].Position = new Vector3(0, 5, 0);
            grid[4 * n + 5].Normal = new Vector3(0.1f, 0.1f, 0.1f);
            grid[4 * n + 5].Color = Color.Blue;

        }

        void graphics_PreparingDeviceSettings(object sender, PreparingDeviceSettingsEventArgs e)
        {
            e.GraphicsDeviceInformation.PresentationParameters.
            DeviceWindowHandle = drawSurface;
        }

        private void gameForm_Hide(object sender, EventArgs e)
        {
            if (gameForm.Visible == true)
                gameForm.Visible = false;
        }
    }

    struct Mode
    {
        public static int None = 0,
                            TranslateX = 1,
                            TranslateY = 2,
                            TranslateZ = 3,
                            ScaleX = 4,
                            ScaleY = 5,
                            ScaleZ = 6,
                            RotateX = 7,
                            RotateY = 8,
                            RotateZ = 9,
                            Translate = 10,         // todo: fix?
                            Scale = 13,
                            Rotate = 16;
    }

    struct View
    {
        public static Vector3 None = new Vector3(0, 0, 0),
                                Left = new Vector3(-1, 0, 0),
                                Right = new Vector3(1, 0, 0),
                                Front = new Vector3(0, 0, -1),
                                Back = new Vector3(0, 0, 1),
                                Top = new Vector3(0, 1, 0.001f),            // Todo: fix for z = 0
                                Bottom = new Vector3(0, -1, 0.001f);
    }
}
