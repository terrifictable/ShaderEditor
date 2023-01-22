#include "../../VAO/VAO.h"
#include "../../EBO/EBO.h"
#include "../../Shader/Shader.h"


class Rectangle {

public:
    VAO vao;
    VBO vbo;
    EBO ebo;

    // x, y, w, h => -1.0 : 1.0
    Rectangle(float top_left[], float top_right[], float bottom_left[], float bottom_right[]);

    void Draw(Shader shader);
    void Draw();
    void Delete();
};
