using System;
using System.Collections.Generic;
using System.Text;
using UnityEditor;
using UnityEngine;
using System.IO;
using System.Runtime.InteropServices;
using System.Collections;


namespace ARUnity
{

    class ARMarkerGizmo
    {
        private static Color SelectedColor = new Color(1f, 1f, 1f, 0.5f);
        private static Color NotInSelectionHierarchyColor = new Color(0.0f, 0.7f, 0.7f, 0.5f);

        private static Color CubeColor = new Color(1, 0, 0, 1);

        [DrawGizmo(GizmoType.NonSelected | GizmoType.NotInSelectionHierarchy | GizmoType.Selected | GizmoType.Pickable)]
        static void RenderARTrackedObjectGizmo(ARMarker to, GizmoType gizmoType)
        {
          
            if (to == null) return;
            Matrix4x4 pose = to.gameObject.transform.localToWorldMatrix;
            DrawTarget(to, pose, gizmoType);
        }


        private static void DrawTarget(ARMarker m, Matrix4x4 mat, GizmoType type)
        {
 
            float length = m.length;

            if (length > 0.0f)
            {


                Vector3 origin = mat.GetColumn(3);
                Vector3 right = mat.GetColumn(0);
                Vector3 up = mat.GetColumn(1);


                Vector3 centre = origin - right * 0.5f + up * 0.5f;
                Vector3 size = new Vector3(0.01f, 0.01f, 0.01f);
                Gizmos.color = CubeColor;
                Gizmos.DrawCube(centre, size);


                if ((type & GizmoType.Selected) != 0)
                {
                    DrawRectangle(centre, up, right, 0.05f, SelectedColor);
                }
                else if ((type & GizmoType.NotInSelectionHierarchy) != 0)
                {
                    DrawRectangle(centre, up, right, 0.05f, NotInSelectionHierarchyColor);
                }

            }
        }

        private static void DrawRectangle(Vector3 centre, Vector3 up, Vector3 right, float length, Color color)
        {

            
            Gizmos.color = color;

            Vector3 u = up * length;
            Vector3 r = right * length;
            Vector3 p = centre - (u * 0.5f) - (r * 0.5f);

            Gizmos.DrawLine(p, p + u);
            Gizmos.DrawLine(p + u, p + u + r);
            Gizmos.DrawLine(p + u + r, p + r);
            Gizmos.DrawLine(p + r, p);
        }





    }



}