#include "VAO.h"


VAO::VAO() {
    glGenVertexArrays(1, &ID);
}


void VAO::LinkVBO(VBO vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    vbo.Bind();

    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);

    vbo.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(ID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Draw(GLenum mode, GLuint cout, GLenum type, const GLvoid* indices) {
    this,Bind();
    glDrawElements(mode, cout, type, indices);
    this->Unbind();
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &ID);
}
