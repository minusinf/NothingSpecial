/****************************************************************************
 Copyright (C) 2012 Adrian Blumer (blumer.adrian@gmail.com)
 Copyright (C) 2016 Pascal Spörri (me@pascalspoerri.ch)
 
 All Rights Reserved.
 
 You may use, distribute and modify this code under the terms of the
 MIT license (http://opensource.org/licenses/MIT).
 *****************************************************************************/

#ifndef TEXTUREBUFFER2D_HPP
#define TEXTUREBUFFER2D_HPP

#include "base.hpp"
#include "TextureBuffer.hpp"
#include <map>

namespace Graphics
{

    template<typename T, TextureFormat FORMAT = TextureFormat::Float>
    class TextureBuffer2D : public TextureBuffer
    {
    public:
        TextureBuffer2D():
            TextureBuffer()
        {
            
        }
        
        TextureBuffer2D(const GLTextureParameters_t& textureParameters):
            TextureBuffer(textureParameters)
        {
    
        }
        
        TextureBuffer2D(TextureBuffer2D&& other):
            TextureBuffer(other)
        {
            
        }
        
        TextureBuffer2D(const TextureBuffer2D&) = delete;
        TextureBuffer2D& operator=(const TextureBuffer2D&)& = delete;
        TextureBuffer2D& operator=(TextureBuffer2D&&)& = delete;
        
        
        void SetData(const T* data, size_t x, size_t y);
        
        void Map(uint textureUnit);
        
        virtual GL::ShaderVariableType shaderVariableType() const
        {
            return GL::ShaderVariableType::sampler2D_t;
        }
    private:
    };
    
    template<typename T, TextureFormat FORMAT> void
    TextureBuffer2D<T,FORMAT>::Map(uint textureUnit)
    {
        m_textureUnit = textureUnit;
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glActiveTexture(GL_TEXTURE0);
    }
    
    template<typename T, TextureFormat FORMAT> void
    TextureBuffer2D<T,FORMAT>::SetData(const T* data, size_t x, size_t y)
    {
        glBindTexture(GL_TEXTURE_2D, m_texture);
        setTextureParameters(GL_TEXTURE_2D);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL::InternalTextureFormat<FORMAT,
                                               GL::TypeInfo<T>::BitsPerChannel,
                                               GL::TypeInfo<T>::ElementCount >(),
                     x, y,
                     0,
                     GL::TypeInfo<T>::TexFormat,
                     GL::TypeInfo<T>::ElementType,
                     data);
        GLWrapper::GLErrorThrow();
        
        glBindTexture(GL_TEXTURE_2D, 0);
        GLWrapper::GLErrorThrow();
    }
}
#endif
