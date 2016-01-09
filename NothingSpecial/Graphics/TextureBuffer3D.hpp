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
#include <exception>

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
        
        virtual GL::ShaderVariableType shaderVariableType() const;
    };
    
    template<typename T, TextureFormat FORMAT> void
    TextureBuffer3D<T, FORMAT>::bind() const
    {
        glBindTexture(GL_TEXTURE_3D, m_texture);
    }
    
    template<typename T, TextureFormat FORMAT> void
    TextureBuffer3D<T, FORMAT>::set(const T* data, size_t x, size_t y, size_t z)
    {
        // https://www.opengl.org/sdk/docs/man/html/glTexImage3D.xhtml
        if (x < 16)
        {
            throw std::invalid_argument("x has to have a length of at least 16 texels");
        }
        if (y < 256)
        {
            throw std::invalid_argument("y has to have a length of at least 16 texels");
        }
        if (z < 256)
        {
            throw std::invalid_argument("z has to have a length of at least 16 texels");
        }        
        bind();
        GLWrapper::GLErrorThrow();
        setTextureParameters(GL_TEXTURE_3D);        
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
    
    template<typename T, TextureFormat FORMAT> GL::ShaderVariableType
    TextureBuffer3D<T, FORMAT>::shaderVariableType() const
    {
        if (FORMAT == TextureFormat::Integer)
        {
            return GL::ShaderVariableType::isampler3D_t;
        }
        
        if (FORMAT == TextureFormat::UnsignedInteger)
        {
            return GL::ShaderVariableType::usampler3D_t;
        }
        // Floating point
        return GL::ShaderVariableType::sampler3D_t;
    }
}

#endif /* TextureBuffer3D_hpp */
