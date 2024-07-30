#include <jni.h>
#include <string>

extern "C" JNIEXPORT void JNICALL
Java_com_example_gles_1cube_JNILib_init(
        JNIEnv* env,
        jclass /* this */,
        int w,
        int h) {
    // ...
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_gles_1cube_JNILib_step(
        JNIEnv* env,
        jclass /* this */) {
    // ...
}
