using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using WavefrontObj;

namespace GameEditor
{
    class RailCamera : Camera
    {
        public QModel model;
        public SimpleModel focusModel;

        public RailCamera(Vector3 camEye, Vector3 camFocus, Vector3 camUp) 
            : base(camEye, camFocus, camUp)
        {
            model = QModel.FromSimpleModel( Editor.Instance.LoadModel("camera.obj", false) );
            
            focusModel = Editor.Instance.LoadModel("focus_pin.obj", false);

            model.Transformation.Translation = Eye;
            focusModel.Transformation.Translation = Focus;
            focusModel.Transformation.Scaling = new Vector3(0.2f, 0.2f, 0.2f);

            Editor.Instance.AddModel(focusModel);
            Editor.Instance.AddModel(model);

            model.Meshes[0].WireFrame = true;
            Update();
        }

        Vector2 YawPitchFromLookAt()
        {
            Vector2 yawPitch = new Vector2();
            Vector3 lookAt = LookAt;
            lookAt.Y = 0;
            lookAt.Normalize();
            yawPitch.X = (float)Math.Acos(Vector3.Dot(lookAt, Vector3.UnitX)) * -Math.Sign(lookAt.Z);

            lookAt = LookAt;
            lookAt = Vector3.Transform(lookAt, Matrix.CreateRotationY(-yawPitch.X));
            lookAt.Z = 0;
            lookAt.Normalize();
            yawPitch.Y = (float)Math.Acos(Vector3.Dot(lookAt, Vector3.UnitX)) * -Math.Sign(lookAt.Y);

            return yawPitch;
        }

        public void Update()
        {
            Eye = model.Transformation.Translation;
            Focus = focusModel.Transformation.Translation;
            model.Transformation.Rotation = new Vector3();
            Vector2 rot = YawPitchFromLookAt();
            model.Rotate(new Vector3(rot.X, 0, -rot.Y));
        }

        public static RailCamera Parse(String[] input)
        {
            RailCamera camera = new RailCamera(Vector3.UnitZ, Vector3.Zero, Vector3.UnitY);

            int keyFrameIndex = 0;
            var keyFrameControl = Editor.Instance.KeyFrameControl;
            for (int i = 0; i < input.Length; ++i)
            {
                var line = input[i];
                string[] tokens = line.Split(' ');
                
                if (tokens[0].StartsWith("keyframe"))
                {
                    keyFrameIndex = int.Parse( tokens[0].Substring("keyframe".Length) );
                    keyFrameControl.InsertKeyFrame(camera.model, keyFrameIndex);
                    keyFrameControl.InsertKeyFrame(camera.focusModel, keyFrameIndex);
                }
                if (tokens[0] == "eye") keyFrameControl.SetTransformation(camera.model, keyFrameIndex, Transformation.CreateTranslation(ParseHelper.ParseVector3(tokens[1])));
                if (tokens[0] == "focus") keyFrameControl.SetTransformation(camera.focusModel, keyFrameIndex, Transformation.CreateTranslation(ParseHelper.ParseVector3(tokens[1])));
            }

            return camera;
        }

        public String ToExportFormat()
        {
            var keyFrameControl = Editor.Instance.KeyFrameControl;
            var keyFrames = keyFrameControl.KeyFrameIndicesForModel[model];
            
            String str = "RailCamera { ";
            foreach (var i in keyFrames)
            {
                var eye = keyFrameControl.GetTransformation(model, i).Translation;
                var focus = keyFrameControl.GetTransformation(focusModel, i).Translation;
                str += String.Format("keyframe{0} {{ eye = {1}; focus = {2}; }}", i, ParseHelper.FormatVector3(eye), ParseHelper.FormatVector3(focus));
            }
            str += " }";

            return str;
        }
    }
}
