//
//  TextureBuffer.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 02/01/16.
//  Copyright © 2016 Pascal Spörri. All rights reserved.
//

#ifndef TextureBuffer_hpp
#define TextureBuffer_hpp

#include "base.hpp"

namespace Graphics {
    class TextureBuffer
    {
    public:
        TextureBuffer() = 0;
        virtual ~TextureBuffer()
        {
            
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
