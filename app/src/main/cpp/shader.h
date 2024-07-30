#ifndef GLES_CUBE_SHADER_H
#define GLES_CUBE_SHADER_H

#include <GLES3/gl3.h>
#include <android/log.h>

#define LOG_TAG "shader"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

class Shader {
public:
    GLuint ID;

public:
    Shader();
    Shader(const char* vertexSource, const char* fragmentSource);

    void activate();
    void destroy();

private:
    void compileErrors(unsigned int shader, const char* type);
};

#endif //GLES_CUBE_SHADER_H
