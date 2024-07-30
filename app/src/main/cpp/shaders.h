#ifndef GLES_CUBE_SHADERS_H
#define GLES_CUBE_SHADERS_H

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

#endif //GLES_CUBE_SHADERS_H
