//
//  Shader.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Shader.hpp"
#include "ShaderException.hpp"

#include <exception>
#include <fstream>
#include <streambuf>

using namespace Graphics;

Shader::Shader(const std::string& vertexShaderSource,
               const std::string& fragmentShaderSource):
    m_vertexShaderSource(vertexShaderSource),
    m_fragmentShaderSource(fragmentShaderSource)
{
    loadShader(vertexShaderSource);
    loadShader(fragmentShaderSource);
}

std::string
Shader::loadShader(const std::string &source)
{
    std::ifstream file(source);
    if (!file)
    {
        throw ShaderException("The file "+source+" could not be loaded");
    }
    
    std::string str;
    
    // Reserve buffer
    file.seekg(0, std::ios::end);
    str.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    
    // Read file
    str.assign(std::istreambuf_iterator<char>(file),
               std::istreambuf_iterator<char>());
    return str;
}