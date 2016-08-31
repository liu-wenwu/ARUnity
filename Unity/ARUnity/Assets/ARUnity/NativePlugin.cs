using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using System;



namespace ARUnity
{
    public class NativePlugin
    {
        private const string LIBRARY_NAME = "arunity";
        public delegate void LogCallback(int level, [MarshalAs(UnmanagedType.LPStr)] string msg);

        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void register_logger(LogCallback callback);

        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void update_camera_frame(IntPtr colors32);


        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void get_camera_size(out int width, out int height);


        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool start_camera();


        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool start_algorithm();


        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool get_projection([MarshalAs(UnmanagedType.LPArray, SizeConst = 16)] float[] matrix, float width, float height, float near_plane, float far_plane);


        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void add_marker(int id, float length);

        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool get_marker_pose(int id, [MarshalAs(UnmanagedType.LPArray, SizeConst = 16)] float[] pose);


        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int get_markers_count();

        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool get_marker_texture(int id, int size, [MarshalAs(UnmanagedType.LPStr)] string filepath);

        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int get_dictionary_words();


        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern int get_dictionary();


        [DllImport(LIBRARY_NAME, CallingConvention = CallingConvention.Cdecl)]
        public static extern void set_dictionary(int dict);

    }


}