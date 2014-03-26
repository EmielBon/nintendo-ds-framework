using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    class InputState
    {
        static MouseState oldMouseState;
        static KeyboardState oldKeyboardState;

        public static MouseState MouseState
        {
            get; private set;
        }

        public static KeyboardState KeyboardState
        {
            get; private set;
        }

        public static Vector2 MousePosition
        {
            get 
            {
                return new Vector2(MouseState.X, MouseState.Y);
            } 
        }
        
        public static Vector2 OldMousePosition
        {
            get 
            {
                return new Vector2(oldMouseState.X, oldMouseState.Y);
            } 
        }

        public static Vector2 DeltaMousePosition
        {
            get
            {
                return OldMousePosition - MousePosition;
            }
        }

        public static int DeltaMouseScrollWheelValue
        {
            get
            {
                return MouseState.ScrollWheelValue - oldMouseState.ScrollWheelValue;
            }
        }

        public static bool MouseLeftButtonPressed
        {
            get
            {
                return MouseState.LeftButton == ButtonState.Pressed/* && oldMouseState.LeftButton == ButtonState.Released*/;
            }
        }

        public static bool MouseRightButtonPressed
        {
            get
            {
                return MouseState.RightButton == ButtonState.Pressed/* && oldMouseState.RightButton != ButtonState.Pressed*/;
            }
        }

        public static bool MouseInClientArea()
        {
            // todo: remove hardcoded window values
            float x = MousePosition.X;
            float y = MousePosition.Y;
            return x >= 0 && x < 1024 && y >= 0 && y < 768;
        }

        public static bool IsKeyPressed(Keys key)
        {
            return KeyboardState.IsKeyDown(key) && oldKeyboardState.IsKeyUp(key);
        }

        public static void Initialize()
        {
            MouseState = Mouse.GetState();
            KeyboardState = Keyboard.GetState();
        }

        public static void Update()
        {
            oldMouseState = MouseState;
            oldKeyboardState = KeyboardState;

            MouseState = Mouse.GetState();
            KeyboardState = Keyboard.GetState();
        }
    }
}
