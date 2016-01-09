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
    class TextureBuffer3D: public TextureBuffer
    {
    public:
        TextureBuffer3D():
            TextureBuffer()
        {
            
        }
        
        TextureBuffer3D(const GLTextureParameters_t& textureParameters):
            TextureBuffer(textureParameters)
        {
            
        }
        
        TextureBuffer3D(TextureBuffer3D&& other):
            TextureBuffer(other)
        {
            
        }
        
        TextureBuffer3D(const TextureBuffer3D&) = delete;
        TextureBuffer3D& operator=(const TextureBuffer3D&)& = delete;
        TextureBuffer3D& operator=(TextureBuffer3D&&)& = delete;
        
        virtual ~TextureBuffer3D()
        {
            
        }
        
        // RAW Data: HELL YEAH
        void set(const T* data, size_t x, size_t y, size_t z);
        
        virtual void bind() const;
        
        virtual GL::ShaderVariableType shaderVariableType() const
        {
            return GL::ShaderVariableType::sampler3D_t;
        }
    };
    
    template<typename T, TextureFormat FORMAT> void
    TextureBuffer3D<T, FORMAT>::bind() const
    {
        glBindTexture(GL_TEXTURE_3D, m_texture);
    }
    
    template<typename T, TextureFormat FORMAT> void
    TextureBuffer3D<T, FORMAT>::set(const T* data, size_t x, size_t y, size_t z)
    {
        bind();
        GLWrapper::GLErrorThrow();
        setTextureParameters(GL_TEXTURE_3D);
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
}

#endif /* TextureBuffer3D_hpp */
