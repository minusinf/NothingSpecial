/*******************************************************************************
 Copyright (C) 2012 Adrian Blumer (blumer.adrian@gmail.com) 
    TerrainErosion Graphics Library
 Copyright (C) 2015 Pascal Spörri (me@pascalspoerri.ch)
 
 All Rights Reserved.
 
 You may use, distribute and modify this code under the terms of the
 MIT license (http://opensource.org/licenses/MIT).
 *******************************************************************************/

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#include "base.hpp"
#include "GLHelper.hpp"
#include "GLWrapper.hpp"
namespace Graphics {
    template<typename T>
    class VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();
        
        void set(const std::vector<T>& data);
        void map(GLuint location, bool normalized);
        void bind();
    private:
        OpenGLVertexBufferID_t m_vbo;
    };

    template<typename T>
    VertexBuffer<T>::VertexBuffer()
    {
        glGenBuffers(1, &m_vbo);
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T>
    VertexBuffer<T>::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_vbo);
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T> void
    VertexBuffer<T>::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T> void
    VertexBuffer<T>::set(const std::vector<T> &data)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        size_t size = sizeof(T)*data.size();
        glBufferData(GL_ARRAY_BUFFER, size, &data[0], GL_STATIC_DRAW);
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T> void
    VertexBuffer<T>::map(GLuint location, bool normalized)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glEnableVertexAttribArray(location);
        GLWrapper::GLErrorThrow();
        glVertexAttribPointer(location,
                              GL::TypeInfo<T>::ElementCount,
                              GL::TypeInfo<T>::ElementType,
                              normalized, 0, 0);
        GLWrapper::GLErrorThrow();
    }
}

#endif /* VertexBuffer_hpp */
