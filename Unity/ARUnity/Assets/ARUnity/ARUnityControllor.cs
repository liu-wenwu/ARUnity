using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System;

namespace ARUnity
{
    [Serializable]
    public class ARUnityControllor : MonoBehaviour
    {

        public enum DICT
        {

            DICT_4X4_50,
            DICT_4X4_100,
            DICT_4X4_250,
            DICT_4X4_1000,
            DICT_5X5_50,
            DICT_5X5_100,
            DICT_5X5_250,
            DICT_5X5_1000,
            DICT_6X6_50,
            DICT_6X6_100,
            DICT_6X6_250,
            DICT_6X6_1000,
            DICT_7X7_50,
            DICT_7X7_100,
            DICT_7X7_250,
            DICT_7X7_1000,
            DICT_ARUCO_ORIGINAL_1024
        };



        public DICT dict = DICT.DICT_7X7_1000;

        private static GCHandle logCallbackGCH;
        private static NativePlugin.LogCallback logCallback = null;

        public static void RegisterLogCallback(NativePlugin.LogCallback lcb)
        {
            if (lcb != null)
            {
                logCallback = lcb;
                logCallbackGCH = GCHandle.Alloc(logCallback);
            }

            NativePlugin.register_logger(logCallback);

            if (lcb == null)
            {
                logCallback = null;
                logCallbackGCH.Free();
            }
        }


        void log(int level, string msg)
        {
            Debug.LogError("Plugin Log:" + msg);
        }


        // Use this for initialization
        void Start()
        {
            RegisterLogCallback(log);

            NativePlugin.start_camera();
            NativePlugin.start_algorithm();
        }

        // Update is called once per frame
        void Update()
        {

        }


        public void setDict(DICT _dict)
        {
            if (_dict == dict)
                return;

            dict = _dict;

            NativePlugin.set_dictionary((int)dict);

            ARMarker[] markers = GameObject.FindObjectsOfType<ARMarker>();

            foreach (ARMarker marker in markers)
            {
                marker.DictionaryChanged();
            }


        }

    }


}