using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;
using System.IO;
using System.Collections.Generic;

namespace ARUnity
{

    [Serializable]
    public class ARMarker : MonoBehaviour
    {

        public int id = -1;

        public float length = 0.01f;

        public bool useBackgroundColor = false;

        public Texture2D texture = null;

        public Color backgroundColor = Color.white;

        public Material material = null;

        private float[] pose = new float[16];

        private Matrix4x4 transformationMatrix;

        private string filepath;

        private const int size = 128;


        private static HashSet<int> markers = new HashSet<int>();




        void Start()
        {
            NativePlugin.add_marker(id, length);

            MeshRenderer meshRenderer = gameObject.GetComponent<MeshRenderer>();
            meshRenderer.enabled = false;
        }

        void OnEnable()
        {
        }

        public void SetUseBackgroundColor(bool use)
        {
            if (use == useBackgroundColor)
                return;

            useBackgroundColor = use;
            if (!useBackgroundColor)
                RefreshTexture();
            else
                SetBackgroundColor(backgroundColor);

        }


        public void SetBackgroundColor(Color color)
        {

            InitTexture();

            backgroundColor = color;

            Color32[] colors = new Color32[size * size];
            for (int i = 0; i < size * size; ++i)
                colors[i] = color;
            texture.SetPixels32(colors);
            texture.Apply(false);

        }

        private void InitTexture()
        {
            if ((object)texture == null)
            {
                texture = new Texture2D(size, size);
                texture.filterMode = FilterMode.Bilinear;
                texture.wrapMode = TextureWrapMode.Clamp;
            }

            if ((object)material == null)
            {
                MeshRenderer meshRenderer = gameObject.GetComponent<MeshRenderer>();
                material = new Material(Shader.Find("Standard"));
                meshRenderer.material = material;
                material.mainTexture = texture;
            }

        }

        private string GetImagePath(int id)
        {
            return Application.streamingAssetsPath + "/ARUnity/" + id + ".png";
        }

        public void DictionaryChanged()
        {
            if (id > NativePlugin.get_dictionary_words())
            {
                File.Delete(GetImagePath(id));
                File.Delete(GetImagePath(id) + ".meta");
                id = 0;
            }

            RefreshTexture();

        }


        public bool RefreshTexture()
        {


            InitTexture();

            if (id < 0 || id >= NativePlugin.get_dictionary_words())
                return false;

            filepath = GetImagePath(id);

            NativePlugin.get_marker_texture(id, size, filepath);

            if (!File.Exists(filepath))
                return false;


            FileStream fileStream = new FileStream(filepath, FileMode.Open, FileAccess.Read);

            fileStream.Seek(0, SeekOrigin.Begin);

            byte[] bytes = new byte[fileStream.Length];

            fileStream.Read(bytes, 0, (int)fileStream.Length);
            fileStream.Close();
            fileStream.Dispose();

            if ((object)texture == null)
                return false;

            if (!texture.LoadImage(bytes))
                return false;

            return true;

        }

        public void SetID(int newid)
        {
            if (markers.Contains(newid))
                return;


            if (newid >= 0 && newid <= NativePlugin.get_dictionary_words() && newid != id)
            {
                markers.Add(newid);
                markers.Remove(id);

                File.Delete(GetImagePath(id));
                File.Delete(GetImagePath(id) + ".meta");

                id = newid;
                RefreshTexture();
            }

        }


        void Update()
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
        public Matrix4x4 LHMatrixFromRHMatrix(Matrix4x4 rhm)
        {
            Matrix4x4 lhm = new Matrix4x4(); ;

            // Column 0.
            lhm[0, 0] = rhm[0, 0];
            lhm[1, 0] = rhm[1, 0];
            lhm[2, 0] = -rhm[2, 0];
            lhm[3, 0] = rhm[3, 0];

            // Column 1.
            lhm[0, 1] = rhm[0, 1];
            lhm[1, 1] = rhm[1, 1];
            lhm[2, 1] = -rhm[2, 1];
            lhm[3, 1] = rhm[3, 1];

            // Column 2.
            lhm[0, 2] = -rhm[0, 2];
            lhm[1, 2] = -rhm[1, 2];
            lhm[2, 2] = rhm[2, 2];
            lhm[3, 2] = -rhm[3, 2];

            // Column 3.
            lhm[0, 3] = rhm[0, 3];
            lhm[1, 3] = rhm[1, 3];
            lhm[2, 3] = -rhm[2, 3];
            lhm[3, 3] = rhm[3, 3];

            return lhm;
        }

        public Quaternion QuaternionFromMatrix(Matrix4x4 m)
        {
            if (m.GetColumn(2) == Vector4.zero)
            {
                return Quaternion.identity;
            }
            return Quaternion.LookRotation(m.GetColumn(2), m.GetColumn(1));
        }

        public Vector3 PositionFromMatrix(Matrix4x4 m)
        {
            return m.GetColumn(3);
        }

        void LateUpdate()
        {
            transform.localScale = new Vector3(length, length, length);

            bool tracked = NativePlugin.get_marker_pose(id, pose);
      
            if (tracked)
            {
                Matrix4x4 matrixRaw = MatrixFromFloatArray(pose);

                transformationMatrix = LHMatrixFromRHMatrix(matrixRaw);

                transformationMatrix = Matrix4x4.TRS(Vector3.zero, Quaternion.AngleAxis(90, Vector3.right), Vector3.one)*transformationMatrix;
                transform.position = PositionFromMatrix(transformationMatrix);
                transform.rotation = QuaternionFromMatrix(transformationMatrix);
            }
        }
    }


}