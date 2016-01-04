/*******************************************************************************
 Copyright (C) 2012 Adrian Blumer (blumer.adrian@gmail.com) 
   TerrainErosion Graphics Library
 Copyright (C) 2016 Pascal Spörri (me@pascalspoerri.ch)
 
 All Rights Reserved.
 
 You may use, distribute and modify this code under the terms of the
 MIT license (http://opensource.org/licenses/MIT).
 *******************************************************************************/

#ifndef TextureBuffer_hpp
#define TextureBuffer_hpp

#include "base.hpp"
#include "GLHelper.hpp"
#include "GLWrapper.hpp"
#include <unordered_map>

typedef std::unordered_map<GLenum, GLint> GLTextureParameters_t;

namespace Graphics {
    class TextureBuffer
    {
    public:
        TextureBuffer():
            TextureBuffer(GLTextureParameters_t())
        {
        }
        
        TextureBuffer(TextureBuffer&& other):
            m_texture(std::move(other.m_texture)),
            m_textureUnit(std::move(other.m_textureUnit)),
            m_textureParameters(std::move(other.m_textureParameters))
        {
        };
        
        TextureBuffer(const GLTextureParameters_t& textureParameters):
            m_textureParameters(textureParameters)
        {
            glGenTextures(1, &m_texture);
        }
        
        virtual ~TextureBuffer()
        {
            glDeleteTextures(1, &m_texture);
        }
        
        OpenGLTextureBufferID_t textureBuffer() const
        {
            return m_texture;
        }
        
        GLuint textureUnit() const
        {
            return m_textureUnit;
        }
        
        virtual GL::ShaderVariableType shaderVariableType() const = 0;
    protected:
        OpenGLTextureBufferID_t m_texture;
        GLuint m_textureUnit;
        const std::unordered_map<GLenum,GLint> m_textureParameters;

        void setTextureParameters(GLenum target)
        {
            for (const auto& kv: m_textureParameters)
            {
                glTexParameteri(target, kv.first, kv.second);
                GLWrapper::GLErrorThrow();
            }
        }
    };
}

#endif /* TextureBuffer_hpp */
