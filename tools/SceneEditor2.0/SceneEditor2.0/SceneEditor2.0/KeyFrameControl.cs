using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using System.IO;
using WavefrontObj;
using System.Diagnostics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;

namespace GameEditor
{
    class KeyFrameControl : DrawableGameComponent
    {
        int currentFrameIndex;
        
        public SortedList<int, KeyFrame> KeyFrameForIndex = new SortedList<int, KeyFrame>();
        public Dictionary<Model3D, List<int>> KeyFrameIndicesForModel = new Dictionary<Model3D, List<int>>();
        List<Frame> frames = new List<Frame>();

        SpriteBatch spriteBatch;
        SpriteFont font1;

        DrawableRect frameBar;
        DrawableRect currentFrameBar;
        
        int minFrameIndex = 0;
        int maxFrameIndex = 250;

        public KeyFrameControl(Game game) : base(game)
        {
            int hOffset = 16;
            int x1 = hOffset;
            int x2 = 1024 - hOffset;
            int y1 = 768 - 96;
            int y2 = 768;

            spriteBatch = new SpriteBatch(Game.GraphicsDevice);

            frameBar = new DrawableRect(x1, y1, x2, y2, Color.LightGray);
            currentFrameBar = new DrawableRect(-2, 0, 2, 100, Color.Yellow);
        }

        protected override void LoadContent()
        {
            font1 = Game.Content.Load<SpriteFont>("Fonts/Font1");
        }

        public override void Update(GameTime gameTime)
        {
            if (Playing && AutoPlay)
                CurrentFrameIndex = ++CurrentFrameIndex % FrameCount;
        }

        public void InsertKeyFrame(Model3D model, int frameIndex)
        {
            if (!KeyFrameForIndex.ContainsKey(frameIndex))
            {
                KeyFrameForIndex[frameIndex] = new KeyFrame(frameIndex);
            }
            if (!KeyFrameForIndex[frameIndex].TransformationForModel.ContainsKey(model))
            {
                KeyFrameForIndex[frameIndex].TransformationForModel[model] = Transformation.Identity;
            }

            KeyFrameForIndex[frameIndex].TransformationForModel[model] = model.Transformation;

            if (!KeyFrameIndicesForModel.ContainsKey(model))
            {
                KeyFrameIndicesForModel[model] = new List<int>();
            }
            KeyFrameIndicesForModel[model].Add(frameIndex);
            KeyFrameIndicesForModel[model].Sort();

            // Make sure there are enough frames for interpolation step later
            while (frames.Count < frameIndex + 1)
            {
                frames.Add(new Frame(frames.Count));
            }
            CalculateFrames();
        }

        public void InsertKeyFrameOnCurrentFrame(Model3D model)
        {
            InsertKeyFrame(model, CurrentFrameIndex);
        }

        public bool HasTransformation(Model3D model, int frameIndex)
        {
            if (frameIndex > frames.Count - 1)
                return false;
            return frames[frameIndex].TransformationForModel.ContainsKey(model);
        }

        public Transformation GetTransformation(Model3D model, int frameIndex)
        {
            return frames[frameIndex].TransformationForModel[model];
        }

        public void SetTransformation(Model3D model, int keyFrameIndex, Transformation transformation)
        {
            KeyFrameForIndex[keyFrameIndex].TransformationForModel[model] = transformation;
        }

        public void CalculateFrames()
        {
            foreach(var model in KeyFrameIndicesForModel.Keys)
            {
                var keyFrames = KeyFrameIndicesForModel[model];

                if (keyFrames.Count == 1)
                {
                    frames[0].TransformationForModel[model] = KeyFrameForIndex[0].TransformationForModel[model];
                    continue;
                }

                for (int i = 0; i < keyFrames.Count - 1; ++i)
                {
                    int kf1 = keyFrames[i];
                    int kf2 = keyFrames[i + 1];

                    Transformation t1 = KeyFrameForIndex[kf1].TransformationForModel[model];
                    Transformation t2 = KeyFrameForIndex[kf2].TransformationForModel[model];
                    
                    for (int j = kf1; j < kf2; ++j)
                    {
                        frames[j].TransformationForModel[model] = Transformation.Lerp(t1, t2, (j - kf1) / (float)(kf2 - kf1));
                    }
                }
            }
        }

        public override void Draw(GameTime gameTime)
        {
            var effect = EffectCatalog.ScreenSpaceEffect;
            effect.Parameters["ScreenWidth"].SetValue(1024f);
            effect.Parameters["ScreenHeight"].SetValue(768f);

            if (currentFrameIndex > maxFrameIndex)
            {
                int diff = currentFrameIndex - maxFrameIndex;
                minFrameIndex += diff;
                maxFrameIndex += diff;
            }
            if (currentFrameIndex < minFrameIndex)
            {
                int diff = currentFrameIndex - minFrameIndex;
                minFrameIndex += diff;
                maxFrameIndex += diff;
            }

            DrawRect(frameBar, Matrix.Identity);
            DrawRect(currentFrameBar, Matrix.CreateTranslation(GetOffsetOnFrameBar(currentFrameIndex), 768 - 100, 0));

            foreach (var keyFrame in KeyFrameForIndex.Values)
            {
                if (keyFrame.TransformationForModel.ContainsKey(Editor.Instance.SelectedModel))
                    DrawRect(currentFrameBar, Matrix.CreateScale(0.5f, 1, 1) * Matrix.CreateTranslation(GetOffsetOnFrameBar(keyFrame.FrameIndex), 768 - 100, 0));
            }
            
            spriteBatch.Begin();
            DrawCenteredString(minFrameIndex, 16, 768 - 96 - 32, Color.White);
            DrawCenteredString(maxFrameIndex, 1024 - 16, 768 - 96 - 32, Color.White);
            DrawCenteredString(currentFrameIndex, GetOffsetOnFrameBar(currentFrameIndex), 768 - 96 - 32, Color.LightPink);
            spriteBatch.End();
        }

        int GetOffsetOnFrameBar(int frameIndex)
        {
            return (int)MathHelper.Lerp(16, 1024 - 16, (frameIndex - minFrameIndex) / (float)(maxFrameIndex - minFrameIndex));
        }

        void DrawCenteredString(object str, int x, int y, Color color)
        {
            string s = str.ToString();
            spriteBatch.DrawString(font1, s, new Vector2(x - font1.MeasureString(s).X / 2, y), color);
        }
        /*
        public void DrawKeyFrameIndicator(int index)
        {
            var rect = new DrawableRect(-1, 0, 1, 100, Color.Yellow);
            DrawRect(rect, Matrix.CreateTranslation(16 + ((1024 - 2 * 16) / 250f) * index, 768 - 100, 0));
        }
        */
        public void DrawRect(DrawableRect rect, Matrix transformation)
        {
            var effect = EffectCatalog.ScreenSpaceEffect;
            effect.Parameters["World"].SetValue(transformation);
            effect.CurrentTechnique.Passes[0].Apply();
            GraphicsDevice.DrawUserIndexedPrimitives(PrimitiveType.TriangleList, rect.Vertices, 0, rect.Vertices.Length, rect.Indices, 0, rect.Indices.Length / 3);
        }

        public int CurrentFrameIndex
        {
            get { return currentFrameIndex; }
            set { currentFrameIndex = (int)MathHelper.Clamp(value, 0, int.MaxValue); }
        }

        public bool Playing
        {
            get; set;
        }

        public bool AutoPlay
        {
            get; set;
        }

        public int FrameCount
        {
            get { return frames.Count; }
        }
    }
}
