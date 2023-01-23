#include "Shapes/Rectangle.h"
#include "../EBO/EBO.h"
#include "GLFW/glfw3.h"


Rectangle::Rectangle(float top_left[], float top_right[], float bottom_left[], float bottom_right[]) {
    GLfloat vertices[] = {
            top_right[0],    top_right[1],    top_right[2],
            bottom_right[0], bottom_right[1], bottom_right[2],
            bottom_left[0],  bottom_left[1],  bottom_left[2],
            top_left[0],     top_left[1],     top_left[2]
    };
    GLuint indices[] = {
            0, 1, 3,
            1, 2, 3
    };


    VAO ivao;
    ivao.Bind();

    VBO ivbo(vertices, sizeof(vertices));
    EBO iebo(indices, sizeof(indices));

    ivao.LinkVBO(ivbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
//    ivao.LinkVBO(ivbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    ivao.Unbind();
    ivbo.Unbind();
    iebo.Unbind();

    vao = ivao;
    vbo = ivbo;
    ebo = iebo;
}
void Rectangle::Draw(Shader shader) {
    shader.use();
    shader.setFloat("u_time", glfwGetTime());
    vao.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Rectangle::Draw() {
    vao.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Rectangle::Delete() {
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}
