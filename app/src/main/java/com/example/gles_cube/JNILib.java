package com.example.gles_cube;

public class JNILib {

    static {
        System.loadLibrary("gles_cube");
    }

    public static native void init(int w, int h);
    public static native void step();
    public static native void move(float start_x, float start_y, float x, float y);
}
