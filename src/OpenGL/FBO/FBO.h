#ifndef FBO_H
#define FBO_H

#include "glad/glad.h"

class FBO {
    GLuint fboId;

public:
    FBO();
    ~FBO();

    void bind();
    void unbind();
};

#endif //SHADER_EDITOR_FBO_H
