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
#include "Shader.hpp"
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
        void map(const Shader& shader, GLuint location, bool normalized);
        void bind() const;
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
        glDeleteVertexArrays(1, &m_vbo);
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T> void
    VertexBuffer<T>::bind() const
    {
        glBindVertexArray(m_vbo);
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T> void
    VertexBuffer<T>::set(const std::vector<T> &data)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(T)*data.size(), &data[0], GL_STATIC_DRAW);
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T> void
    VertexBuffer<T>::map(const Shader& shader,
                         GLuint location, bool normalized)
    {
        glBindVertexArray(shader.getVAO());
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glVertexAttribPointer(location,
                              GL::TypeInfo<T>::ElementCount,
                              GL::TypeInfo<T>::ElementType,
                              normalized,
                              0, 0);
//        glBindVertexArray(m_vbo);
//        glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
//        glVertexAttribPointer(location,
//                              GL::TypeInfo<T>::ElementCount,
//                              GL::TypeInfo<T>::ElementType,
//                              normalized, 0, 0);
//        glEnableVertexAttribArray(0);
//        glBindVertexArray(0);
        GLWrapper::GLErrorThrow();
    }
}

#endif /* VertexBuffer_hpp */
