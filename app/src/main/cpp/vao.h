#ifndef GLES_CUBE_VAO_H
#define GLES_CUBE_VAO_H

#include "GLObject.h"
#include "vbo.h"

class VAO : public GLObject
{
public:
    VAO();

    void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

    void bind() override;
    void unbind() override;
    void destroy() override;
};

#endif //GLES_CUBE_VAO_H
