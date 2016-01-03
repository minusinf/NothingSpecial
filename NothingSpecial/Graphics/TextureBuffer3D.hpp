/*******************************************************************************
 Copyright (C) 2016 Pascal Spörri (me@pascalspoerri.ch)
 
 All Rights Reserved.
 
 You may use, distribute and modify this code under the terms of the
 MIT license (http://opensource.org/licenses/MIT).
 *******************************************************************************/

#ifndef TextureBuffer3D_hpp
#define TextureBuffer3D_hpp

#include "base.hpp"
#include "Shader.hpp"
#include "GLHelper.hpp"
#include "GLWrapper.hpp"
#include "GraphicsException.hpp"
#include "TextureBuffer.hpp"

namespace Graphics {
    
    template<typename T, TextureFormat FORMAT = TextureFormat::Float>
    class TextureBuffer3D: TextureBuffer
    {
    public:
        TextureBuffer3D() = default;
        TextureBuffer3D(TextureBuffer3D&&) = default;
        TextureBuffer3D(const TextureBuffer3D&) = delete;
        TextureBuffer3D& operator=(const TextureBuffer3D&)& = delete;
        TextureBuffer3D& operator=(TextureBuffer3D&&)& = delete;
        virtual ~TextureBuffer3D()
        {
            
        }
        
        // RAW Data: HELL YEAH
        void set(const T* data, size_t x, size_t y, size_t z);
        void map(GLuint textureUnit);
    };
    
    template<typename T, TextureFormat FORMAT> void
    TextureBuffer3D<T, FORMAT>::set(const T* data, size_t x, size_t y, size_t z)
    {
        glBindTexture(GL_TEXTURE_3D, m_texture);
        GLWrapper::GLErrorThrow();
// Keeping this for now
// We may want to have a better way to specify glTexParameters
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
        GLWrapper::GLErrorThrow();
//        glPixelStorei(GL_UNPACK_ALIGNMENT,1);
        glTexImage3D(GL_TEXTURE_3D,
                     0,
                     GL::InternalTextureFormat<FORMAT,
                                               GL::TypeInfo<T>::BitsPerChannel,
                                               GL::TypeInfo<T>::ElementCount >(),
                     x,
                     y,
                     z,
                     0,
                     GL::TypeInfo<T>::TexFormat,
                     GL::TypeInfo<T>::ElementType,
                     data);
        GLWrapper::GLErrorThrow();
        
        glBindTexture(GL_TEXTURE_3D, 0);
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T, TextureFormat FORMAT> void
    TextureBuffer3D<T, FORMAT>::map(GLuint textureUnit)
    {
        m_textureUnit = textureUnit;
        glActiveTexture(GL_TEXTURE0 + m_textureUnit);
        glBindTexture(GL_TEXTURE_3D, m_texture);
        glActiveTexture(GL_TEXTURE0);
    }
}

#endif /* TextureBuffer3D_hpp */
