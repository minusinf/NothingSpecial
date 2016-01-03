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

namespace Graphics
{

    template<typename T, TextureFormat FORMAT = TextureFormat::Float>
    class TextureBuffer2D : public TextureBuffer
    {
    public:
        TextureBuffer2D() = default;
        TextureBuffer2D(TextureBuffer2D&&) = default;
        TextureBuffer2D(const TextureBuffer2D&) = delete;
        TextureBuffer2D& operator=(const TextureBuffer2D&)& = delete;
        TextureBuffer2D& operator=(TextureBuffer2D&&)& = delete;
        
        void SetData(const T* data, size_t x, size_t y);
        void Map(uint textureUnit);
        virtual GL::ShaderVariableType shaderVariableType() const
        {
            return GL::ShaderVariableType::sampler2D_t;
        }
    };
    
    // Implementation
    ///////////////////////////////////////////////
    
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
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        // (x,y,z) = (s,t,r)
        
        
        //    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        //    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        //    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
        
        
        //    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        
        
        //        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        //        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        //        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
#endif
