#ifndef GLES_CUBE_EBO_H
#define GLES_CUBE_EBO_H

#include "GLObject.h"

class EBO : public GLObject
{
public:
    EBO();
    EBO(GLuint* indices, GLsizeiptr size);

    void bind() override;
    void unbind() override;
    void destroy() override;
};

#endif //GLES_CUBE_EBO_H
