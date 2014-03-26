using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace GameEditor
{
    public class Camera
    {
        Matrix viewMatrix;
        Matrix projectionMatrix;

        Vector3 eye;
        Vector3 focus;

        public Camera(Vector3 camEye, Vector3 camFocus, Vector3 camUp, float aspectRatio = 4.0f / 3.0f)
        {
            eye = camEye;
            focus = camFocus;

            viewMatrix = Matrix.CreateLookAt(Eye, Focus, Up);
            projectionMatrix = Matrix.CreatePerspectiveFieldOfView(MathHelper.PiOver4, aspectRatio, 1.0f, 300.0f);
            //projectionMatrix = Matrix.CreateOrthographicOffCenter(-10, 10, -10, 10, 1f, 300f);
            UpdateViewMatrix();
        }

        public void UpdateViewMatrix()
        {
            viewMatrix = Matrix.CreateLookAt(eye, focus, Up);
        }

        public Vector3 Eye
        {
            get { return eye; }
            set { eye = value; UpdateViewMatrix(); }
        }

        public Vector3 Focus
        {
            get { return focus; }
            set { focus = value; UpdateViewMatrix(); }
        }

        public Vector3 LookAt
        {
            get { return Vector3.Normalize(Focus - Eye); }
        }

        public Vector3 Side
        {
            get { return Vector3.Normalize( Vector3.Cross(LookAt, Up) ); }
        }

        public Vector3 Up
        {
            get 
            {
                Vector3 side = Vector3.Cross(Vector3.UnitY, LookAt);
                Vector3 up = Vector3.Cross(LookAt, side);
                up.Normalize();
                return up;
            }
        }

        public Matrix ViewMatrix
        {
            get { return viewMatrix; }
        }

        public Matrix ProjectionMatrix
        {
            get { return projectionMatrix; }
        }

        public void Move(float dx, float dy)
        {
           Move( new Vector2(dx, dy) );
        }

        public void Move(Vector2 move)
        {
            Eye += Side * move.X;
            Eye += Up * move.Y;

            Focus += Side * move.X;
            Focus += Up * move.Y;
        }

        public void Rotate(float dx, float dy)
        {
            Rotate(new Vector2(dx, dy));
        }

        public void Rotate(Vector2 rot)
        {
            Matrix transform = Matrix.CreateFromQuaternion(Quaternion.CreateFromAxisAngle(Vector3.UnitY, rot.X)) * Matrix.CreateFromQuaternion(Quaternion.CreateFromAxisAngle(Side, rot.Y));
            Vector3 focusToEye = Eye - Focus;
            float distance = focusToEye.Length();
            Eye = Focus + Vector3.Transform(Vector3.Normalize(focusToEye), transform) * distance;
        }

        public void Zoom(float amount)
        {
            Vector3 focusToEye = Eye - Focus;
            float distance = focusToEye.Length();

            if (distance * amount > 1.0f)
                Eye = Focus + focusToEye * amount;
        }

        public Vector3 GetScreenCoordinates(Vector3 point)
        {
            // todo: retrieve viewport
            Viewport v = new Viewport(0, 0, 1024, 768);
            return v.Project(point, ProjectionMatrix, viewMatrix, Matrix.Identity);
        }
    }
}
