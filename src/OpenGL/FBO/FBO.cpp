#include "FBO.h"

FBO::FBO() {
    glGenFramebuffers(GL_FRAMEBUFFER, &fboId);
}

FBO::~FBO() {
//    glDeleteFramebuffers(1, &fboId);
}

void FBO::bind() {

}

void FBO::unbind() {

}
