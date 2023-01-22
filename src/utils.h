#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

std::string readFile(const char* filename) {
    std::string file_contents;
    std::fstream file;

    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {

        file.open(filename);
        std::stringstream file_stringstream;

        file_stringstream << file.rdbuf();

        file.close();

        file_contents = file_stringstream.str();

    } catch(std::ifstream::failure e) {
        std::cout << "File " << filename << " could not be read" << std::endl;
    }

    return file_contents;
}

#endif
