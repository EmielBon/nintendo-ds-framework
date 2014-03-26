using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    class ControlState
    {
        public Vector3 SelectedAxes;

        public ControlState()
        {

        }

        public TransformationMode TransformationMode
        {
            get; private set;
        }

        public HotKeys HotKey
        {
            get; set;
        }

        public void ResetState()
        {
            TransformationMode = TransformationMode.None;
            SelectedAxes = new Vector3(0, 0, 0);
            HotKey = HotKeys.None;
        }

        void DetermineTransformationMode()
        {
            var keys = InputState.KeyboardState;

            if (keys.IsKeyDown(Keys.G))
            {
                TransformationMode = TransformationMode.Grab;
            }
            else if (keys.IsKeyDown(Keys.R))
            {
                TransformationMode = TransformationMode.Rotate;
            }
            else if (keys.IsKeyDown(Keys.S))
            {
                TransformationMode = TransformationMode.Scale;
            }
        }

        void PollHotKeys()
        {
            var keys = InputState.KeyboardState;

            if (keys.IsKeyDown(Keys.LeftShift))
            {
                if (InputState.IsKeyPressed(Keys.A))
                    HotKey = HotKeys.Add;
                else if (InputState.IsKeyPressed(Keys.I))
                    HotKey = HotKeys.Insert;
            }
            if (keys.IsKeyDown(Keys.LeftControl))
            {
                if (InputState.IsKeyPressed(Keys.O))
                    HotKey = HotKeys.Open;
                else if (InputState.IsKeyPressed(Keys.P))
                    HotKey = HotKeys.PlayMode;
                else if (InputState.IsKeyPressed(Keys.S))
                    HotKey = HotKeys.Save;
            }
                
            if (InputState.IsKeyPressed(Keys.Delete))
                if (TransformationMode == TransformationMode.None)
                    HotKey = HotKeys.Delete;
            if (InputState.IsKeyPressed(Keys.M))
                HotKey = HotKeys.Make;
            if (InputState.IsKeyPressed(Keys.Space))
                HotKey = HotKeys.TogglePlay;
            if (keys.IsKeyDown(Keys.Subtract))
                HotKey = HotKeys.Previous;
            if (keys.IsKeyDown(Keys.Add))
                HotKey = HotKeys.Next;
            if (keys.IsKeyDown(Keys.NumPad0))
                HotKey = HotKeys.Camera0;
            // Cancel any transformation operations when the pressed key is part of a hotkey command
            if (HotKey != HotKeys.None)
                TransformationMode = TransformationMode.None;
        }

        void PollMouseAction()
        {
            if (InputState.MouseLeftButtonPressed)
            {
                if (TransformationMode != TransformationMode.None)
                    TransformationMode = TransformationMode.Commit;
            }
            else if (InputState.MouseRightButtonPressed)
            {
                if (TransformationMode == TransformationMode.None)
                    TransformationMode = TransformationMode.Select;
                else 
                    TransformationMode = TransformationMode.Cancel;
            }
        }

        void DetermineSelectedAxis()
        {
            var keys = InputState.KeyboardState;

            if (TransformationMode != TransformationMode.None && SelectedAxes == new Vector3(0, 0, 0))
            {
                if (keys.IsKeyDown(Keys.LeftShift))
                {
                    if (keys.IsKeyDown(Keys.X))
                        SelectedAxes = new Vector3(0, 1, 1);
                    else if (keys.IsKeyDown(Keys.Y))
                        SelectedAxes = new Vector3(1, 0, 1);
                    else if (keys.IsKeyDown(Keys.Z))
                        SelectedAxes = new Vector3(1, 1, 0);
                }
                else
                {
                    if (keys.IsKeyDown(Keys.X))
                        SelectedAxes = new Vector3(1, 0, 0);
                    else if (keys.IsKeyDown(Keys.Y))
                        SelectedAxes = new Vector3(0, 1, 0);
                    else if (keys.IsKeyDown(Keys.Z))
                        SelectedAxes = new Vector3(0, 0, 1);
                }
            }
        }

        public void Update()
        {
            DetermineTransformationMode();
            DetermineSelectedAxis();
            PollHotKeys();
            PollMouseAction();
        }
    }
}
