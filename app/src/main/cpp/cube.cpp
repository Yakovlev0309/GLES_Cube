#include <jni.h>
#include <string>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* vertexShaderSource =
        "# version 300 es\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "layout (location = 2) in vec2 aTex;\n"
        "out vec3 color;\n"
        "out vec2 texCoord;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 proj;\n"
        "void main() {\n"
        "   gl_Position = proj * view * model * vec4(aPos, 1.0);\n"
        "   color = aColor;\n"
        "   texCoord = aTex;\n"
        "}\n";

const char* fragmentShaderSource =
        "# version 300 es\n"
        "precision mediump float;\n"
        "out vec4 FragColor;\n"
        "in vec3 color;\n"
        "in vec2 texCoord;\n"
        "void main() {\n"
        "   FragColor = vec4(color, 1.0f);\n"
        "}\n";

// Вершины
GLfloat vertices[] =
        {    // Координаты                      Цвета			                 Координаты текстур
                -0.25f,  0.25f, -0.25f,         255.0f, 0.0f, 0.0f,             0.0f, 0.0f,
                0.25f,  0.25f, -0.25f,         255.0f, 0.0f, 0.0f,             5.0f, 0.0f,
                -0.25f, -0.25f, -0.25f,         255.0f, 0.0f, 0.0f,             0.0f, 0.0f,
                0.25f, -0.25f, -0.25f,         255.0f, 0.0f, 0.0f,             5.0f, 0.0f,

                -0.25f,  0.25f,  0.25f,         0.0f, 255.0f, 0.0f,             2.5f, 5.0f,
                0.25f,  0.25f,  0.25f,         0.0f, 255.0f, 0.0f,             0.0f, 0.0f,
                -0.25f, -0.25f,  0.25f,         0.0f, 255.0f, 0.0f,             5.0f, 0.0f,
                0.25f, -0.25f,  0.25f,         0.0f, 255.0f, 0.0f,             0.0f, 0.0f,

                -0.25f,  0.25f, -0.25f,         0.0f, 0.0f, 255.0f,             0.0f, 0.0f,
                -0.25f, -0.25f, -0.25f,         0.0f, 0.0f, 255.0f,             5.0f, 0.0f,
                -0.25f, -0.25f,  0.25f,         0.0f, 0.0f, 255.0f,             0.0f, 0.0f,
                -0.25f,  0.25f,  0.25f,         0.0f, 0.0f, 255.0f,             5.0f, 0.0f,

                0.25f,  0.25f, -0.25f,         255.0f, 255.0f, 255.0f,         2.5f, 5.0f,
                0.25f, -0.25f, -0.25f,         255.0f, 255.0f, 255.0f,         0.0f, 0.0f,
                0.25f, -0.25f,  0.25f,         255.0f, 255.0f, 255.0f,         5.0f, 0.0f,
                0.25f,  0.25f,  0.25f,         255.0f, 255.0f, 255.0f,         0.0f, 0.0f,

                -0.25f, -0.25f, -0.25f,         255.0f, 255.0f, 0.0f,           0.0f, 0.0f,
                -0.25f, -0.25f,  0.25f,         255.0f, 255.0f, 0.0f,           5.0f, 0.0f,
                0.25f, -0.25f,  0.25f,         255.0f, 255.0f, 0.0f,           0.0f, 0.0f,
                0.25f, -0.25f, -0.25f,         255.0f, 255.0f, 0.0f,           5.0f, 0.0f,

                -0.25f,  0.25f, -0.25f,         0.0f, 255.0f, 255.0f,           2.5f, 5.0f,
                -0.25f,  0.25f,  0.25f,         0.0f, 255.0f, 255.0f,           0.0f, 0.0f,
                0.25f,  0.25f,  0.25f,         0.0f, 255.0f, 255.0f,           5.0f, 0.0f,
                0.25f,  0.25f, -0.25f,         0.0f, 255.0f, 255.0f,           0.0f, 0.0f,
        };
// Индексы вершин
GLuint indices[] =
        {
                0, 2, 3,
                0, 1, 3,
                4, 6, 7,
                4, 5, 7,
                8, 9, 10,
                11, 8, 10,
                12, 13, 14,
                15, 12, 14,
                16, 17, 18,
                16, 19, 18,
                20, 21, 22,
                20, 23, 22
        };


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

GLuint shaderProgram;
GLuint vaoID, vboID, eboID;
int width, height;

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
    glBindVertexArray(vaoID);

    // VBO
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // EBO
    glGenBuffers(1, &eboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Привязка атрибутов
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);
}

void renderFrame()
{
    static float rotation;
    rotation += 5.0f;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // Активация шейдера
    glUseProgram(shaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 1.0f, 1.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
    proj = glm::perspective(glm::radians(60.0f), (float)width / height, 0.1f, 100.0f);

    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projLoc = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, indices);
}

void deleteObjects()
{
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
    glDeleteBuffers(1, &eboID);
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
