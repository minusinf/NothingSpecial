/****************************************************************************
 Copyright (C) 2012 Adrian Blumer (blumer.adrian@gmail.com)
 Copyright (C) 2015 Pascal Spörri (me@pascalspoerri.ch)
 
 All Rights Reserved.
 
 You may use, distribute and modify this code under the terms of the
 MIT license (http://opensource.org/licenses/MIT).
 *****************************************************************************/

#include "GLHelper.hpp"

namespace Graphics
{
    namespace GL
    {
        bool GetCompileStatus(OpenGLShaderID_t id)
        {
            GLint status;
            glGetShaderiv(id, GL_COMPILE_STATUS, &status);
            return status != GL_FALSE;
        }
        
        bool GetLinkStatus(OpenGLShaderProgramID_t id)
        {
            GLint status;
            glGetProgramiv(id, GL_LINK_STATUS, &status);
            return status != GL_FALSE;
        }
        
        std::string GetShaderInfoLog(OpenGLShaderProgramID_t id)
        {
            GLint len = 42;
            glGetShaderiv(id,GL_INFO_LOG_LENGTH,&len);
            GLchar* s = new GLchar[len];
            glGetShaderInfoLog(id,len, &len,s);
            std::string r = std::string(s,len);
            
            delete s;
            return r;
        }
        
        std::string GetProgramInfoLog(OpenGLShaderProgramID_t id)
        {
            GLint len;
            glGetProgramiv(id,GL_INFO_LOG_LENGTH,&len);
            assert(len >= 0);
            
            GLchar* s = new GLchar[len];
            glGetProgramInfoLog(id,len, &len,s);
            std::stringstream stream;
            stream << s;
            delete s;
            
            return stream.str();
        }
        
        /// Sets the source code of a shader.
        void ShaderSource(OpenGLShaderID_t id, const std::string& source)
        {
            GLint l = (GLint)source.size();
            const char* s = source.c_str();
            glShaderSource(id,1,&s,&l);
        }
        
        
        /// Access to different properties of a shader program.
        GLint GetProgramProperty(OpenGLShaderProgramID_t id, ProgramProperty p)
        {
            GLint v;
            glGetProgramiv(id,(GLenum)p, &v);
            return v;
        }
        
        void GetUniformInfo(OpenGLShaderProgramID_t programId,
                            GLuint index,
                            int& outSize,
                            ShaderVariableType& outType,
                            std::string& outName)
        {
            GLsizei maxLen = GetProgramProperty(programId, ProgramProperty::MaxUniformNameLength);
            GLchar* n = new char[maxLen];
            GLint len;
            GLenum t;
            glGetActiveUniform(programId, index, maxLen, &len, &outSize, &t, n);
            
            outName = std::string(n,len);
            delete n;
            outType = (ShaderVariableType)t;
        }
        
        GLint GetUniformLocation(OpenGLShaderProgramID_t programId,
                                 std::string& name)
        {
            return glGetUniformLocation(programId, name.c_str());
        }
        
        std::string StringOf(ShaderVariableType e)
        {
            switch(e)
            {
                case ShaderVariableType::float_t: return "float";
                case ShaderVariableType::vec2_t:  return "vec2";
                case ShaderVariableType::vec3_t:  return "vec3";
                case ShaderVariableType::vec4_t:  return "vec4";
                case ShaderVariableType::int_t:   return "int";
                case ShaderVariableType::ivec2_t: return "ivec2";
                case ShaderVariableType::ivec3_t: return "ivec3";
                case ShaderVariableType::ivec4_t: return "ivec4";
                case ShaderVariableType::uint_t:  return "uint";
                case ShaderVariableType::uvec2_t: return "uvec2";
                case ShaderVariableType::uvec3_t: return "uvec3";
                case ShaderVariableType::uvec4_t: return "uvec4";
                case ShaderVariableType::bool_t:  return "bool";
                case ShaderVariableType::bvec2_t: return "bvec2";
                case ShaderVariableType::bvec3_t: return "bvec3";
                case ShaderVariableType::bvec4_t: return "bvec4";
                case ShaderVariableType::mat2_t:  return "mat2";
                case ShaderVariableType::mat3_t:  return "mat3";
                case ShaderVariableType::mat4_t:  return "mat4";
                case ShaderVariableType::sampler1D_t: return "sampler1D";
                case ShaderVariableType::sampler2D_t: return "sampler2D";
                case ShaderVariableType::sampler3D_t: return "sampler3D";
                default: return "unknown";
            }
        }
        
        void GetAttributeInfo(OpenGLShaderProgramID_t programId,
                              GLuint index,
                              GLint& outSize,
                              ShaderVariableType& outType,
                              std::string& outName)
        {
            int maxLen = GetProgramProperty(programId, ProgramProperty::MaxAttributeNameLength);
            char* n = new char[maxLen];
            int len;
            uint t;
            glGetActiveAttrib(programId, index, maxLen, &len, &outSize, &t, n);
            outName = std::string(n,len);
            delete n;
            outType = (ShaderVariableType)t;
        }
        
        // Internal Texture Format
        ////////////////////////////////////////////////////////////////////////
        template<> GLuint InternalTextureFormat<TextureFormat::FloatNormalized, 16, 4>() { return GL_RGBA16; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatNormalized, 16, 3>() { return GL_RGB16; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatNormalized, 16, 2>() { return GL_RG16; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatNormalized, 16, 1>() { return GL_R16; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::FloatNormalized, 8, 4>() { return GL_RGBA8; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatNormalized, 8, 3>() { return GL_RGB8; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatNormalized, 8, 2>() { return GL_RG8; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatNormalized, 8, 1>() { return GL_R8; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::FloatSignedNormalized, 16, 4>() { return GL_RGBA16_SNORM; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatSignedNormalized, 16, 3>() { return GL_RGB16_SNORM; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatSignedNormalized, 16, 2>() { return GL_RG16_SNORM; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatSignedNormalized, 16, 1>() { return GL_R16_SNORM; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::FloatSignedNormalized, 8, 4>() { return GL_RGBA8_SNORM; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatSignedNormalized, 8, 3>() { return GL_RGB8_SNORM; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatSignedNormalized, 8, 2>() { return GL_RG8_SNORM; }
        template<> GLuint InternalTextureFormat<TextureFormat::FloatSignedNormalized, 8, 1>() { return GL_R8_SNORM; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::Float, 16, 4>() { return GL_RGBA16F; }
        template<> GLuint InternalTextureFormat<TextureFormat::Float, 16, 3>() { return GL_RGB16F; }
        template<> GLuint InternalTextureFormat<TextureFormat::Float, 16, 2>() { return GL_RG16F; }
        template<> GLuint InternalTextureFormat<TextureFormat::Float, 16, 1>() { return GL_R16F; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::Float, 32, 4>() { return GL_RGBA32F; }
        template<> GLuint InternalTextureFormat<TextureFormat::Float, 32, 3>() { return GL_RGB32F; }
        template<> GLuint InternalTextureFormat<TextureFormat::Float, 32, 2>() { return GL_RG32F; }
        template<> GLuint InternalTextureFormat<TextureFormat::Float, 32, 1>() { return GL_R32F; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 32, 4>() { return GL_RGBA32UI; }
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 32, 3>() { return GL_RGB32UI; }
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 32, 2>() { return GL_RG32UI; }
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 32, 1>() { return GL_R32UI; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 16, 4>() { return GL_RGBA16UI; }
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 16, 3>() { return GL_RGB16UI; }
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 16, 2>() { return GL_RG16UI; }
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 16, 1>() { return GL_R16UI; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 8, 4>() { return GL_RGBA8UI; }
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 8, 3>() { return GL_RGB8UI; }
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 8, 2>() { return GL_RG8UI; }
        template<> GLuint InternalTextureFormat<TextureFormat::UnsignedInteger, 8, 1>() { return GL_R8UI; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 32, 4>() { return GL_RGBA32I; }
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 32, 3>() { return GL_RGB32I; }
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 32, 2>() { return GL_RG32I; }
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 32, 1>() { return GL_R32I; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 16, 4>() { return GL_RGBA16I; }
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 16, 3>() { return GL_RGB16I; }
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 16, 2>() { return GL_RG16I; }
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 16, 1>() { return GL_R16I; }
        
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 8, 4>() { return GL_RGBA8I; }
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 8, 3>() { return GL_RGB8I; }
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 8, 2>() { return GL_RG8I; }
        template<> GLuint InternalTextureFormat<TextureFormat::Integer, 8, 1>() { return GL_R8I; }
        
    }
}