using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace GameEditor
{
    struct Transformation
    {
        public Vector3 Translation;
        public Vector3 Rotation;
        public Vector3 Scaling;

        public static Transformation Identity
        {
            get 
            {
                Transformation t = new Transformation();
                t.Scaling = new Vector3(1, 1, 1);
                return t;
            }
        }

        public static Transformation Lerp(Transformation t1, Transformation t2, float value)
        {
            Transformation t = new Transformation();

            t.Translation = Vector3.Lerp(t1.Translation, t2.Translation, value);
            t.Rotation    = Vector3.Lerp(t1.Rotation,    t2.Rotation,    value);
            t.Scaling     = Vector3.Lerp(t1.Scaling,     t2.Scaling,     value);

            return t;
        }

        public static Transformation CreateTranslation(Vector3 translation)
        {
            Transformation t = Transformation.Identity;
            t.Translation = translation;
            return t;
        }

        public static Transformation Parse(String input)
        {
            Transformation t = new Transformation();

            var lines = input.Split('\n');
            foreach (var line in lines)
            {
                var line2 = line.Replace(" ", "");
                var tokens = line2.Split('=');
                if (tokens[0] == "translation") t.Translation = ParseHelper.ParseVector3(tokens[1]);
                if (tokens[0] == "rotation") t.Rotation = ParseHelper.ParseVector3(tokens[1]);
                if (tokens[0] == "scaling") t.Scaling = ParseHelper.ParseVector3(tokens[1]);
            }

            return t;
        }

        public String ToExportFormat()
        {
            return String.Format("translation = {0};rotation = {1};scaling = {2};", ParseHelper.FormatVector3(Translation), ParseHelper.FormatVector3(Rotation), ParseHelper.FormatVector3(Scaling));
        }
    }
}
