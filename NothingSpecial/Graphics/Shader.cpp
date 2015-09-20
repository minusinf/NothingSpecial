//
//  Shader.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Shader.hpp"
#include "GraphicsException.hpp"
#include "GLWrapper.hpp"

#include <fstream>

using namespace Graphics;

const Shader*
Shader::ms_boundShader = NULL;

Shader::Shader(const std::string& vertexShaderPath,
               const std::string& fragmentShaderPath):
    m_vertexShaderPath(vertexShaderPath),
    m_fragmentShaderPath(fragmentShaderPath),
    m_compiled(false)
{
    if (GLWrapper::GLError())
    {
        throw ShaderException("Prexisting OpenGL Error: Aborting");
    }
    reload();
}

Shader::~Shader()
{
    unbind();
    if (m_compiled)
    {
        glDetachShader(m_pId, m_fId);
        glDetachShader(m_pId, m_vId);
        glDeleteShader(m_fId);
        glDeleteShader(m_vId);
        glDeleteProgram(m_pId);
        GLWrapper::GLErrorThrow();
    }
}

void
Shader::bind() const
{
    if (m_compiled)
    {
        glUseProgram(m_pId);
        Shader::ms_boundShader = this;
    }
}

void
Shader::unbind() const
{
    if (ms_boundShader == this)
    {
        unbindCurrent();
    }
}

void
Shader::unbindCurrent()
{
    glUseProgram(0);
    ms_boundShader = NULL;
}

void
Shader::reload()
{
    // Load shader
    std::string vertexShaderStr = loadShader(m_vertexShaderPath);
    std::string fragmentShaderStr = loadShader(m_fragmentShaderPath);
    
    std::string errorString;
    
    // Vertex shader
    GLuint vID = glCreateShader(GL_VERTEX_SHADER);
    GLWrapper::GLErrorThrow();
    
    const char* vertexShaderCstr = vertexShaderStr.c_str();
    glShaderSource(vID, 1, &vertexShaderCstr, NULL);
    if (GLWrapper::GLError(errorString))
    {
        glDeleteShader(vID);
        std::cerr << "Error loading the vertex shader " << m_vertexShaderPath
                  << " with error:\n" << errorString << std::endl;
        return;
    }
    glCompileShader(vID);
    if (GLWrapper::GLError(errorString))
    {
        glDeleteShader(vID);
        std::cerr << "Error compiling the vertex shader " << m_vertexShaderPath
            << " with error: \n" << errorString << std::endl;
        return;
    }
    
    // Fragment shader
    GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);
    GLWrapper::GLErrorThrow();
    
    const char* fragmentShaderCstr = fragmentShaderStr.c_str();
    glShaderSource(fID, 1, &fragmentShaderCstr, NULL);
    if (GLWrapper::GLError(errorString))
    {
        glDeleteShader(vID);
        glDeleteShader(fID);
        std::cerr << "Error loading the fragment shader " << m_fragmentShaderPath
                  << " with error:\n" << errorString << std::endl;
        return;
    }
    glCompileShader(fID);
    if (GLWrapper::GLError(errorString))
    {
        glDeleteShader(vID);
        glDeleteShader(fID);
        std::cerr << "Error compiling the fragment shader " << m_fragmentShaderPath
                  << " with error: \n" << errorString << std::endl;
        return;
    }
    
    // Create and link
    GLuint pID = glCreateProgram();
    if (GLWrapper::GLError(errorString))
    {
        glDeleteShader(vID);
        glDeleteShader(fID);
        glDeleteProgram(pID);
        std::cerr << "Error creating shader program: " << errorString << std::endl;
        return;
    }
    
    glAttachShader(pID, vID);
    GLWrapper::GLErrorThrow();
    glAttachShader(pID, fID);
    GLWrapper::GLErrorThrow();
    
    glLinkProgram(pID);
    if (GLWrapper::GLError(errorString))
    {
        glDetachShader(pID, vID);
        glDetachShader(pID, fID);
        glDeleteShader(vID);
        glDeleteShader(fID);
        glDeleteProgram(pID);
        std::cerr << "Error linking the shader program: " << errorString << std::endl;
        return;
    }
    
    bool previouslyBound = false;
    if (m_compiled)
    {
        if (ms_boundShader == this)
        {
            previouslyBound = true;
        }
        unbind();
        glDetachShader(m_pId, m_fId);
        glDetachShader(m_pId, m_vId);
        glDeleteShader(m_fId);
        glDeleteShader(m_vId);
        glDeleteProgram(m_pId);
        GLWrapper::GLErrorThrow();
    }
    m_pId = pID;
    m_fId = fID;
    m_vId = vID;
    
    if (previouslyBound)
    {
        bind();
    }
    m_compiled = true;
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


void
Shader::toggleShaderRefresh()
{
    m_refreshShaders = !m_refreshShaders;
}

bool
Shader::m_refreshShaders = true;