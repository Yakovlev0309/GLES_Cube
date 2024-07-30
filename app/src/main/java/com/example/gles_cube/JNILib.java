package com.example.gles_cube;

public class JNILib {

    static {
        System.loadLibrary("gles_cube");
    }

    public static native void init(int w, int h);
    public static native void step();
}
