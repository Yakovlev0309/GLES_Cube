#ifndef GLES_CUBE_CUBE_H
#define GLES_CUBE_CUBE_H

#include <GLES3/gl3.h>

// Вершины
GLfloat vertices[] =
        {    // Координаты                     Цвета			               Координаты текстур
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

#endif //GLES_CUBE_CUBE_H
