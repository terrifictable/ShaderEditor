#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "../VBO/VBO.h"


class VAO {

public:
    GLuint ID;

    VAO();


    void LinkVBO(VBO vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Draw(GLenum mode, GLuint cout, GLenum type, const GLvoid* indices);
    void Delete();

};


#endif
