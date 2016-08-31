using UnityEngine;
using System.Collections;


namespace ARUnity
{
    public class VideoCamera : MonoBehaviour
    {

        // Use this for initialization
        void Start()
        {
            Camera camera = gameObject.GetComponent<Camera>();
            camera.projectionMatrix = Matrix4x4.Ortho(-0.5f, 0.5f, -0.5f, 0.5f, -1.0f, 1.0f);

        }

        // Update is called once per frame
        void Update()
        {

        }
    }


}