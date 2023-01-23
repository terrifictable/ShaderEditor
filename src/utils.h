#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

//std::string read_file(const char* filename) {
//    std::string shader_src_file_contents;
//    std::fstream file;
//
//    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
//
//    try {
//
//        file.open(filename);
//        std::stringstream file_stringstream;
//
//        file_stringstream << file.rdbuf();
//
//        file.close();
//
//        shader_src_file_contents = file_stringstream.str();
//
//    } catch(std::ifstream::failure e) {
//        std::cout << "File " << filename << " could not be read" << std::endl;
//    }
//
//#ifdef DEBUG
//    std::cout << "ShaderFile: " << shader_src_file_contents << std::endl;
//#endif
//
//    return shader_src_file_contents;
//}

#endif
