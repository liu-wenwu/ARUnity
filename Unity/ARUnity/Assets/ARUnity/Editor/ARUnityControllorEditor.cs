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

    [CustomEditor(typeof(ARUnityControllor))]
    public class ARUnityControllorEditor : Editor
    {
     
        void OnEnable()
        {
        }



        void OnDestroy()
        {
        }


        public override void OnInspectorGUI()
        {
            ARUnityControllor controllor = (ARUnityControllor)target;
            EditorGUILayout.HelpBox("Welcome to use CVUnity\nAuthor : liu-wenwu , UESTC AA",MessageType.Info);

            controllor.setDict((ARUnityControllor.DICT)EditorGUILayout.EnumPopup("DICT", controllor.dict));
        }



    }



}