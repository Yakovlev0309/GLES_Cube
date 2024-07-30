#include "shader.h"

Shader::Shader() {}

Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    compileErrors(ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate()
{
    glUseProgram(ID);
}

void Shader::destroy()
{
    glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
    GLint hasCompiled;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//            std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
            LOGE("SHADER_COMPILATION_ERROR for:", type);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
//            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
            LOGE("SHADER_LINKING_ERROR for: ", type);
        }
    }
}
