using UnityEngine;
using System.Collections;
using System;

namespace ARUnity
{
    public class ARCamera : MonoBehaviour
    {
        private int screenWidth = 0;
        private int screenHeight = 0;


        // Use this for initialization
        void Start()
        {

        }


        public Matrix4x4 MatrixFromFloatArray(float[] values)
        {
            if (values == null || values.Length < 16)
                throw new ArgumentException("Expected 16 elements in values array", "values");

            Matrix4x4 mat = new Matrix4x4();
            for (int i = 0; i < 16; i++) mat[i] = values[i];
            return mat;
        }


        // Update is called once per frame
        void Update()
        {

            if (screenWidth != Screen.width || screenHeight != Screen.height)
            {
                screenWidth = Screen.width;
                screenHeight = Screen.height;

                float[] projection = new float[16];
                NativePlugin.get_projection(projection, 640, 480, 0.1f, 500);

                Camera camera = gameObject.GetComponent<Camera>();
                camera.projectionMatrix = MatrixFromFloatArray(projection);


                transform.position = new Vector3(0, 0, 0);
                transform.rotation = Quaternion.AngleAxis(90, Vector3.right);
            }



        }
    }



}