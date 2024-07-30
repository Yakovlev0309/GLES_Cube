#ifndef GLES_CUBE_GLOBJECT_H
#define GLES_CUBE_GLOBJECT_H

#include <GLES3/gl3.h>

class GLObject {
public:
    GLuint ID;

public:
    GLObject() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual void destroy() = 0;
};

#endif //GLES_CUBE_GLOBJECT_H
