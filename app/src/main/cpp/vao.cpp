#include "vao.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    VBO.bind();
    // Настройка атрибута вершин, чтобы OpenGL знал, как читать VBO
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    // Включение атрибута вершин, чтобы OpenGL использовал его
    glEnableVertexAttribArray(layout);
    VBO.unbind();
}

void VAO::bind()
{
    glBindVertexArray(ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::destroy()
{
    glDeleteVertexArrays(1, &ID);
}
