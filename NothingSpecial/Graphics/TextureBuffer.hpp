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

namespace Graphics {
    class TextureBuffer
    {
    public:
        TextureBuffer()
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
    protected:
        OpenGLTextureBufferID_t m_texture;
        GLuint m_textureUnit;
        
    };
}

#endif /* TextureBuffer_hpp */
