using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System;


namespace ARUnity
{
    public class VideoQuad : MonoBehaviour
    {


        private Color32[] cameraVideoData = null;


        private Texture2D cameraVideoTexture = null;
        private Material cameraVideoMaterial = null;

        private int screenWidth = 0;
        private int screenHeight = 0;


        // Use this for initialization
        void Start()
        {

        }


        private Mesh newVideoMesh(bool flipX, bool flipY)
        {
            Mesh m = new Mesh();
            m.Clear();

            float r = 0.5f;

            m.vertices = new Vector3[] {
                new Vector3(-r, -r, 0.5f),
                new Vector3( r, -r, 0.5f),
                new Vector3( r,  r, 0.5f),
                new Vector3(-r,  r, 0.5f),
            };

            m.normals = new Vector3[] {
                new Vector3(0.0f, 0.0f, 1.0f),
                new Vector3(0.0f, 0.0f, 1.0f),
                new Vector3(0.0f, 0.0f, 1.0f),
                new Vector3(0.0f, 0.0f, 1.0f),
            };

            float u1 = flipX ? 1.0f : 0.0f;
            float u2 = flipX ? 0.0f : 1.0f;

            float v1 = flipY ? 1.0f : 0.0f;
            float v2 = flipY ? 0.0f : 1.0f;

            m.uv = new Vector2[] {
                new Vector2(u1, v1),
                new Vector2(u2, v1),
                new Vector2(u2, v2),
                new Vector2(u1, v2)
            };

            m.triangles = new int[] {
                2, 1, 0,
                3, 2, 0
            };

            m.Optimize();
            return m;
        }


        // Update is called once per frame
        void Update()
        {

            if (cameraVideoData == null)
            {
                int width, height;
                NativePlugin.get_camera_size(out width, out height);
                cameraVideoData = new Color32[width * height];
                cameraVideoTexture = new Texture2D(width, height, TextureFormat.ARGB32, false);

                cameraVideoTexture.hideFlags = HideFlags.HideAndDontSave;
                cameraVideoTexture.filterMode = FilterMode.Bilinear;
                cameraVideoTexture.wrapMode = TextureWrapMode.Clamp;
                cameraVideoTexture.anisoLevel = 0;


                Shader shaderSource = Shader.Find("VideoPlaneNoLight");
                cameraVideoMaterial = new Material(shaderSource);
                cameraVideoMaterial.hideFlags = HideFlags.HideAndDontSave;
                cameraVideoMaterial.mainTexture = cameraVideoTexture;



                MeshRenderer meshRenderer = gameObject.GetComponent<MeshRenderer>();
                MeshFilter meshFilter = gameObject.GetComponent<MeshFilter>();
                meshFilter.mesh = newVideoMesh(false, true);

                meshRenderer.receiveShadows = false;
                meshRenderer.material = cameraVideoMaterial;

            }





            GCHandle handle = GCHandle.Alloc(cameraVideoData, GCHandleType.Pinned);
            IntPtr address = handle.AddrOfPinnedObject();
            NativePlugin.update_camera_frame(address);
            handle.Free();

            cameraVideoTexture.SetPixels32(cameraVideoData);
            cameraVideoTexture.Apply(false);


        }
    }


}