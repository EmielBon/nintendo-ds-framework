using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    class EditorCamera : Camera
    {
        public EditorCamera(Vector3 camEye, Vector3 camFocus, Vector3 camUp, float aspectRatio = 4.0f / 3.0f) 
            : base(camEye, camFocus, camUp, aspectRatio)
        {

        }

        public void Update()
        {
            KeyboardState keys = InputState.KeyboardState;
            MouseState mouse = InputState.MouseState;

            Vector2 dPos = InputState.DeltaMousePosition;
            float dx = dPos.X / 50f;
            float dy = dPos.Y / 50f;

            // Camera move and rotate
            if (mouse.MiddleButton == ButtonState.Pressed)
            {
                if (keys.IsKeyDown(Keys.LeftShift))
                    Move(dx, -dy);
                else
                    Rotate(dx, dy);
            }
            // Zooming
            if (InputState.DeltaMouseScrollWheelValue > 0)
                Zoom(1 / 1.25f);
            else if (InputState.DeltaMouseScrollWheelValue < 0)
                Zoom(1.25f);
        }
    }
}
