using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using UnityEditor;
using UnityEngine;

namespace ARUnity
{

    [CustomEditor(typeof(ARMarker))]
    public class ARMarkerEditor : Editor
    {
        void OnEnable()
        {
        }


        void OnDestroy()
        {
        }


        public override void OnInspectorGUI()
        {

            ARMarker marker = (ARMarker)target;

            if (marker == null) return;

 
            string idlabel = String.Format("id [0,{0})",NativePlugin.get_dictionary_words());
            EditorGUILayout.BeginHorizontal();
            EditorGUILayout.LabelField(idlabel);
            marker.SetID(EditorGUILayout.IntField(marker.id));
          
            EditorGUILayout.EndHorizontal();


            EditorGUILayout.BeginHorizontal();
            EditorGUILayout.LabelField("length(m)");
            marker.length = EditorGUILayout.FloatField(marker.length);
            EditorGUILayout.EndHorizontal();


            EditorGUILayout.BeginHorizontal();
            EditorGUILayout.LabelField("use background color");
            marker.SetUseBackgroundColor(EditorGUILayout.Toggle(marker.useBackgroundColor));
            EditorGUILayout.EndHorizontal();

            if (marker.useBackgroundColor)
                marker.SetBackgroundColor(EditorGUILayout.ColorField("background color", marker.backgroundColor));
            else
                EditorGUILayout.ObjectField("texture", marker.texture, typeof(Texture2D), true);


        }

    }



}