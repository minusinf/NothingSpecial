/*******************************************************************************
 Copyright (C) 2012 Adrian Blumer (blumer.adrian@gmail.com)
    TerrainErosion Graphics Library
 Copyright (C) 2015 Pascal Spörri (me@pascalspoerri.ch)
 
 All Rights Reserved.
 
 You may use, distribute and modify this code under the terms of the
 MIT license (http://opensource.org/licenses/MIT).
 *******************************************************************************/

#include "Shader.hpp"
#include "GraphicsException.hpp"
#include "GLWrapper.hpp"
#include "GLHelper.hpp"
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
    glGenVertexArrays(1, &m_vao);
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
        glBindVertexArray(getVAO());

        Shader::ms_boundShader = this;
    }
    else
    {
        throw ShaderException("Binding uncompiled program");
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

GLuint
Shader::getVAO() const
{
    return m_vao;
}

void
Shader::reload()
{
    // Load shader
    std::string vertexShaderStr = loadShader(m_vertexShaderPath);
    std::string fragmentShaderStr = loadShader(m_fragmentShaderPath);
    
    std::string errorString;
    
    // Vertex shader
    OpenGLShaderID_t vID = glCreateShader(GL_VERTEX_SHADER);
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
    if (!GL::GetCompileStatus(vID))
    {
        std::cerr << "Error compiling the vertex shader " << m_vertexShaderPath
                  << " with error: \n" << GL::GetCompileStatus(vID) << std::endl;
        glDeleteShader(vID);
        return;
    }
    
    // Fragment shader
    OpenGLShaderID_t fID = glCreateShader(GL_FRAGMENT_SHADER);
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
    if (!GL::GetCompileStatus(fID))
    {
        std::cerr << "Error compiling the fragment shader " << m_fragmentShaderPath
                  << " with error: \n" << GL::GetCompileStatus(fID) << std::endl;
        glDeleteShader(vID);
        glDeleteShader(fID);
        return;
    }
    
    // Create and link
    OpenGLShaderProgramID_t pID = glCreateProgram();
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
    if (!GL::GetLinkStatus(pID))
    {
        std::cerr << "Error linking the shader program: " << GL::GetProgramInfoLog(pID) << std::endl;

        glDetachShader(pID, vID);
        glDetachShader(pID, fID);
        glDeleteShader(vID);
        glDeleteShader(fID);
        glDeleteProgram(pID);
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
    
    loadAttributeInfo();
    loadUniformInfo();
    
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

const std::string&
Shader::vertexShaderPath()
{
    return m_vertexShaderPath;
}

const std::string&
Shader::fragmentShaderPath()
{
    return m_fragmentShaderPath;
}

OpenGLShaderProgramID_t
Shader::programID()
{
    return m_pId;
}



bool Shader::setUniform(const std::string &name, const glm::vec3 &v)
{
    try
    {
        UniformInfo& info = m_uniformInfo.at(name);
        assert(info.Type == GL::ShaderVariableType::vec3_t);
        assert(info.Length == 1);
        assert(Shader::ms_boundShader == this);
        glUniform3fv(info.Location,1, &v.x);
        return true;
    }
    catch (std::out_of_range& oor)
    {
        return false;
    }
}

bool Shader::setUniform(const std::string &name, const glm::vec4 &v)
{
    try
    {
        UniformInfo& info = m_uniformInfo.at(name);
        
        assert(info.Type == GL::ShaderVariableType::vec4_t);
        assert(info.Length == 1);
        assert(Shader::ms_boundShader == this);
        glUniform4fv(info.Location,1, &v.x);
        return true;
    }
    catch (std::out_of_range& oor)
    {
        return false;
    }
}

bool Shader::setUniform(const std::string &name, const glm::mat4 &v, bool transpose)
{
    try
    {
        UniformInfo& info = m_uniformInfo.at(name);
        assert(info.Type == GL::ShaderVariableType::mat4_t);
        assert(info.Length == 1);
        assert(Shader::ms_boundShader == this);
        glUniformMatrix4fv(info.Location,1, transpose, &v[0].x);
        return true;
    }
    catch (std::out_of_range& oor)
    {
        return false;
    }
}

bool Shader::setUniform(const std::string &name, bool v)
{
    try
    {
        UniformInfo& info = m_uniformInfo.at(name);
        assert(info.Type == GL::ShaderVariableType::bool_t);
        assert(info.Length == 1);
        assert(Shader::ms_boundShader == this);
        glUniform1i(info.Location,v);
        return true;
    }
    catch (std::out_of_range& oor)
    {
        return false;
    }
}

bool Shader::setUniform(const std::string &name, int v)
{
    try
    {
        UniformInfo& info = m_uniformInfo.at(name);
        assert(info.Type == GL::ShaderVariableType::int_t);
        assert(info.Length == 1);
        assert(Shader::ms_boundShader == this);
        glUniform1i(info.Location,v);
        return true;
    }
    catch (std::out_of_range& oor)
    {
        return false;
    }
}

bool Shader::mapAttribute(const std::string& name, uint location)
{
    AttributeInfo& at = m_attributeInfo[name];
    at.Location = location;
    at.Name = location;
    
    if (at.Present)
    {
        glBindAttribLocation(m_pId, location, name.c_str());
        
        // Relink shader
        glLinkProgram(m_pId);
        if (!GL::GetLinkStatus(m_pId))
        {
            auto infoLog = GL::GetProgramInfoLog(m_pId);
            throw ShaderException(infoLog+" with shader "+vertexShaderPath());
        }
    }
    
    return at.Present;
}

uint Shader::attributeLocation(const std::string &name)
{
    try
    {
        AttributeInfo& at = m_attributeInfo.at(name);
        if (at.Location == -1)
        {
            throw ShaderException("Attribute "+name+" is not mapped with shader "+vertexShaderPath());
        }
        if (!at.Present)
        {
            throw ShaderException("Attribute "+name+" is currently not present in the shader "+vertexShaderPath());

        }
        return at.Location;
    }
    catch (std::out_of_range& oor)
    {
        throw ShaderException("Attribute "+name+" not found in shader "+vertexShaderPath());
    }
}

void Shader::loadUniformInfo()
{
    m_uniformCount = GL::GetProgramProperty(m_pId, GL::ProgramProperty::UniformCount);
    
    std::cout << "UniformCount: " << m_uniformCount << "\n"; // DEBUG
    
    m_uniformInfo.clear();
    for (uint32_t i=0; i<m_uniformCount; i++)
    {
        UniformInfo info;
        GL::GetUniformInfo(m_pId, i, info.Length, info.Type, info.Name);
        info.Location = GL::GetUniformLocation(m_pId, info.Name);
        
        std::cout << "\t" << info.Name << " (" << GL::StringOf(info.Type) << "," << info.Length << "): " << info.Location << std::endl; // DEBUG
        
        m_uniformInfo[info.Name] = info;
    }
}

void Shader::loadAttributeInfo()
{
    m_attributeCount = GL::GetProgramProperty(m_pId, GL::ProgramProperty::AttributeCount);
    std::cout << "AttributeCount: " << m_attributeCount << std::endl; // DEBUG
    int32_t location = 0;
    for (GLuint i=0; i<m_attributeCount; i++)
    {
        AttributeInfo info;
        GL::GetAttributeInfo(m_pId, i, info.Length, info.Type, info.Name);
        info.Location = location;
        info.Present = true;
        
        
        auto iter = m_attributeInfo.find(info.Name);
        if (iter != m_attributeInfo.end())
        {
            AttributeInfo& oldAt  = (*iter).second;
            info.Location = oldAt.Location;

        }
        location++;
        if (info.Present)
        {
            glBindAttribLocation(m_pId, info.Location, info.Name.c_str());
        }
        std::cout << "\t" << info.Name << " (" << GL::StringOf(info.Type) << "," << info.Length << "): " << info.Location << "\n"; // DEBUG
        
        m_attributeInfo[info.Name] = info;
    }
    
    // Relink shader
    glLinkProgram(m_pId);
    if (!GL::GetLinkStatus(m_pId))
    {
        auto infoLog = GL::GetProgramInfoLog(m_pId);
        throw ShaderException("Linking error after attribute mapping: "+infoLog+" with shader "+vertexShaderPath());
    }
}