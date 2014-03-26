using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using System.Diagnostics;
using Microsoft.Xna.Framework.Graphics;

namespace GameEditor
{
    partial class Editor
    {
        void HandleActions()
        {
            if (ControlState.TransformationMode != TransformationMode.None)
                KeyFrameControl.Playing = false;

            switch (ControlState.TransformationMode)
            {
                case TransformationMode.Select: HandleSelecting();
                                                ControlState.ResetState();
                                                break;
                case TransformationMode.Commit: SelectedModel.SavedTransformation = false;
                                                ControlState.ResetState();
                                                break;
                case TransformationMode.Cancel: SelectedModel.ResetTransformation();
                                                ControlState.ResetState();
                                                break;
                case TransformationMode.Grab:   HandleGrabbing(); break;
                case TransformationMode.Rotate: HandleRotating(); break;
                case TransformationMode.Scale:  HandleScaling(); break;
                default:                        break;
            }

            if (!SelectedModel.SavedTransformation)
                SelectedModel.SaveTransformation();
        }

        void HandleHotKeys()
        {
            switch (ControlState.HotKey)
            {
                case HotKeys.Add:        LoadModelWithDialog(); break;
                case HotKeys.Save:       SaveScene(); break;
                case HotKeys.Open:       OpenScene(); break;
                case HotKeys.Insert:     KeyFrameControl.InsertKeyFrameOnCurrentFrame(SelectedModel); break;
                case HotKeys.Previous:   if (!KeyFrameControl.AutoPlay)
                                             KeyFrameControl.CurrentFrameIndex--; 
                                             break;
                case HotKeys.Next:       if (!KeyFrameControl.AutoPlay)
                                             KeyFrameControl.CurrentFrameIndex++;
                                             break;
                case HotKeys.PlayMode:   if (Models.Count == 0) break;
                                         KeyFrameControl.Playing = true;
                                         KeyFrameControl.AutoPlay = true;
                                         KeyFrameControl.CalculateFrames();
                                         break;
                case HotKeys.TogglePlay: KeyFrameControl.AutoPlay = !KeyFrameControl.AutoPlay; break;
                case HotKeys.Delete:     DeleteModel(SelectedModel);
                                         SelectedModel = new SimpleModel(); 
                                         break;
                case HotKeys.Make:       ProcessStartInfo startInfo = new ProcessStartInfo();
                                         startInfo.FileName = "make";
                                         startInfo.Arguments = "run";
                                         startInfo.WorkingDirectory = NDSFrameworkHelper.CodeDirectory;
                                         startInfo.UseShellExecute = false;
                                         Process pr = Process.Start(startInfo);
                                         pr.WaitForExit();
                                         break;
                case HotKeys.Camera0:    Camera.Eye   = RailCamera.Eye;
                                         Camera.Focus = RailCamera.Focus;
                                         break;
                default:                 break;
            }

            ControlState.HotKey = HotKeys.None;
        }

        void HandleSelecting()
        {
            int width = MeshIdRender.Width;
            int height = MeshIdRender.Height;

            Color[] pixels = new Color[width * height];
            MeshIdRender.GetData(pixels);
            MouseState mouse = Mouse.GetState();

            if (mouse.X < 0 || mouse.X >= width || mouse.Y < 0 || mouse.Y >= height)
                return;

            int colorId = pixels[mouse.X + mouse.Y * width].R;

            if (colorId == 255)
                return;
            SelectedModel = Models[colorId];
        }

        void HandleGrabbing()
        {
            Vector3 scaleX = Camera.GetScreenCoordinates(Vector3.UnitX);
            Vector3 scaleY = Camera.GetScreenCoordinates(Vector3.UnitY);
            Vector3 scaleZ = Camera.GetScreenCoordinates(Vector3.UnitZ);
            float scale1 = (scaleX - Camera.GetScreenCoordinates(new Vector3(0, 0, 0))).Length();

            float scale2 = (scaleY - Camera.GetScreenCoordinates(new Vector3(0, 0, 0))).Length();
            float scale3 = (scaleZ - Camera.GetScreenCoordinates(new Vector3(0, 0, 0))).Length();
            float deltaX = -GetMouseDistanceForAxis(Vector3.UnitX) / scale1;
            float deltaY = -GetMouseDistanceForAxis(Vector3.UnitY) / scale2;
            float deltaZ = -GetMouseDistanceForAxis(Vector3.UnitZ) / scale3;

            Console.WriteLine(ControlState.SelectedAxes);
            if (ControlState.SelectedAxes != new Vector3(0, 0, 0))
                SelectedModel.Translate(new Vector3(deltaX, deltaY, deltaZ) * ControlState.SelectedAxes);

        }

        void HandleRotating()
        {
            Vector3 center = SelectedModel.Center;

            Vector3 screenCenter = Camera.GetScreenCoordinates(center);
            Vector2 screenCenter2D = new Vector2(screenCenter.X, screenCenter.Y);
            Vector2 mouse1 = InputState.MousePosition - screenCenter2D;
            Vector2 mouse2 = InputState.OldMousePosition - screenCenter2D;
            if (mouse1 - mouse2 == new Vector2(0, 0)) return;
            float delta = (float)(Math.Atan2(mouse1.X, mouse1.Y) - Math.Atan2(mouse2.X, mouse2.Y));
            if (delta < -1) delta = delta + MathHelper.TwoPi;
            else if (delta > 1) delta = delta - MathHelper.TwoPi;
            //float delta = -(float)Math.Acos(Vector2.Dot(Vector2.Normalize(mouse1), Vector2.Normalize(mouse2)));
            Console.WriteLine(delta);

            if (ControlState.SelectedAxes != new Vector3(0, 0, 0))
                SelectedModel.Rotate(delta * ControlState.SelectedAxes);
        }

        void HandleScaling()
        {
            Vector3 center = SelectedModel.Center;

            Vector3 screenCenter = Camera.GetScreenCoordinates(center);
            Vector2 screenCenter2D = new Vector2(screenCenter.X, screenCenter.Y);

            float d1 = (InputState.MousePosition - screenCenter2D).Length();
            float d2 = (InputState.OldMousePosition - screenCenter2D).Length();
            float scale =  (float)Math.Abs((Camera.GetScreenCoordinates(Vector3.UnitX) - Camera.GetScreenCoordinates(new Vector3(0, 0, 0))).Length());
            float delta = (d1 - d2) / scale;
            SelectedModel.Scale(delta * ControlState.SelectedAxes);
            /*switch (ControlState.SelectedAxes)
            {
                case SelectedAxis.X: SelectedModel.Scale(new Vector3(delta, 0, 0)); break;
                case SelectedAxis.Y: SelectedModel.Scale(new Vector3(0, delta, 0)); break;
                case SelectedAxis.Z: SelectedModel.Scale(new Vector3(0, 0, delta)); break;
                case SelectedAxis.None: SelectedModel.Scale(new Vector3(delta, delta, delta)); break;
                default: break;
            }*/
        }

        void DeleteModel(Model3D model)
        {
            model.MarkForDeletion();
        }

        protected float GetMouseDistanceForAxis(Vector3 selectedAxis)
        {
            Vector3 p1 = Camera.GetScreenCoordinates(new Vector3(0, 0, 0));
            Vector3 p2 = Camera.GetScreenCoordinates(selectedAxis);

            Vector3 axis3d = (p2 - p1);
            Vector2 axis = new Vector2(axis3d.X, axis3d.Y);
            axis.Normalize();

            Vector2 dPos = InputState.DeltaMousePosition;
            float dx = dPos.X;
            float dy = dPos.Y;
            return dx * axis.X + dy * axis.Y;
        }
    }
}
