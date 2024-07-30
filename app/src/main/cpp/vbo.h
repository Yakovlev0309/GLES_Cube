#ifndef GLES_CUBE_VBO_H
#define GLES_CUBE_VBO_H

#include "GLObject.h"

class VBO : public GLObject
{
public:
    VBO();
    VBO(GLfloat* vertices, GLsizeiptr size);

    void bind() override;
    void unbind() override;
    void destroy() override;
};

#endif //GLES_CUBE_VBO_H
