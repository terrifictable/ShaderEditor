#pragma once

#ifndef SHADER_EDITOR_SHADER_H
#define SHADER_EDITOR_SHADER_H

#include <glad/glad.h>
#include <string>


class Shader {
private:
    GLuint vertexID;
    GLuint fragmentID;
    std::string vertex_shader_src;
    std::string fragment_shader_src;

    void readShadersFromFile(std::string vertex_shader_src_path, std::string fragment_shader_src_path);
    void init();

public:
    GLuint programID;

    Shader(std::string vertex_path, std::string fragment_path);
    Shader();
    ~Shader();


    void use();

    void setBool(   const std::string &name, bool     value   );
    void setInt(    const std::string &name, int      value   );
    void setFloat(  const std::string &name, float    value   );
};

#endif //SHADER_EDITOR_SHADER_H
