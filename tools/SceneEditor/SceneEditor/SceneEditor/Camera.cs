using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace _3DTest
{
    public class Camera
    {
        Matrix viewMatrix;
        Matrix projectionMatrix;

        Vector3 up;
        Vector3 eye;
        Vector3 focus;

        public Camera(Vector3 camEye, Vector3 camFocus, Vector3 camUp, float aspectRatio = 4.0f / 3.0f)
        {
            eye = camEye;
            focus = camFocus;
            up = camUp;

            viewMatrix = Matrix.CreateLookAt(eye, focus, up);
            projectionMatrix = Matrix.CreatePerspectiveFieldOfView(MathHelper.PiOver4, aspectRatio, 1.0f, 300.0f);
            UpdateViewMatrix();
        }

        public void UpdateViewMatrix()
        {
            viewMatrix = Matrix.CreateLookAt(eye, focus, up);
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

        public Matrix ViewMatrix
        {
            get { return viewMatrix; }
        }

        public Matrix ProjectionMatrix
        {
            get { return projectionMatrix; }
        }


    }
    
}
