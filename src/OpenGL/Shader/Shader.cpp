#include "Shader.h"

//#define DEBUG


std::string readFile(const char* filename);


Shader::Shader(std::string vertex_src, std::string fragment_src) {
    readShadersFromFile(vertex_src, fragment_src);
    init();
}
Shader::Shader(std::string fragment_shader) {
    vertex_shader_src = readFile("shaders/default.vsh");
    fragment_shader_src = fragment_shader;
    init();
}
Shader::Shader() {}
Shader::~Shader() {
//    glDeleteProgram(programID);
}


void Shader::readShadersFromFile(std::string vertex_shader_src_path, std::string fragment_shader_src_path) {
    vertex_shader_src = readFile(vertex_shader_src_path.c_str());
    fragment_shader_src = readFile(fragment_shader_src_path.c_str());
}



void Shader::init() {
#ifdef DEBUG
    std::cout << fragment_shader_src << std::endl;
#endif

    int success;
    char infoLog[512];

    vertexID = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_shader_src_cstr = vertex_shader_src.c_str();
    glShaderSource(vertexID, 1, &vertex_shader_src_cstr, NULL);
    glCompileShader(vertexID);

    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
        std::cout << "ERROR Compile Vertex Shader: ID [" << vertexID << "]   error: " << infoLog << std::endl;
        exit(1);
    }



    // Compile Fragment Shader
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_shader_src_cstr = fragment_shader_src.c_str();
    glShaderSource(fragmentID, 1, &fragment_shader_src_cstr, NULL);
    glCompileShader(fragmentID);

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(1);
    }



    // Link shaders
    programID = glCreateProgram();
    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);
    glLinkProgram(programID);
    // check for linking errors
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

}


void Shader::use() {
    glUseProgram(programID);
}

void Shader::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}



std::string readFile(const char* filename) {
    std::string shader_src_file_contents;
    std::fstream file;

    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {

        file.open(filename);
        std::stringstream file_stringstream;

        file_stringstream << file.rdbuf();

        file.close();

        shader_src_file_contents = file_stringstream.str();

    } catch(std::ifstream::failure e) {
        std::cout << "File " << filename << " could not be read" << std::endl;
    }

#ifdef DEBUG
    std::cout << "ShaderFile: " << shader_src_file_contents << std::endl;
#endif

    return shader_src_file_contents;
}
