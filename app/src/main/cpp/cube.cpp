#include <jni.h>
#include <string>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "cube.h"
#include "shaders.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"

GLuint shaderProgram;
int width, height;
VAO vao;
VBO vbo;
EBO ebo;
float delta_x;
float delta_y;

GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*)malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*)malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

void setupGraphics(int w, int h)
{
    width = w;
    height = h;

    shaderProgram = createProgram(vertexShaderSource, fragmentShaderSource);
    if (!shaderProgram) {
        return;
    }

    glViewport(0, 0, width, height);

    // VAO
    vao.bind();

    // VBO
    vbo = VBO(vertices, sizeof(vertices));

    // EBO
    ebo = EBO(indices, sizeof(indices));

    // Привязка атрибутов
    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.linkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glEnable(GL_DEPTH_TEST);
}

void renderFrame()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Активация шейдера
    glUseProgram(shaderProgram);

    auto model = glm::mat4(1.0f);
    auto view = glm::mat4(1.0f);
    auto proj = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(std::abs(delta_x)), glm::vec3(1.0f, delta_x, 1.0f));
    model = glm::rotate(model, glm::radians(std::abs(delta_y)), glm::vec3(delta_y, 1.0f, 1.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
    proj = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projLoc = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    vao.bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void deleteObjects()
{
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    glDeleteProgram(shaderProgram);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_gles_1cube_JNILib_init(
        JNIEnv* env,
        jclass /* this */,
        int w,
        int h) {
    setupGraphics(w, h);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_gles_1cube_JNILib_step(
        JNIEnv* env,
        jclass /* this */) {
    renderFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_gles_1cube_JNILib_move(
        JNIEnv* env,
        jclass /* this */,
        float start_x, float start_y, float x, float y) {
    delta_x = x - start_x;
    delta_y = y - start_y;
}
