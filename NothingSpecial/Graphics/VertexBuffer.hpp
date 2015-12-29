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
#include "GraphicsException.hpp"

namespace Graphics {
    
    template<typename T, bool ELEMENT_BUFFER = false>
    class VertexBuffer
    {
    public:
        VertexBuffer();
        VertexBuffer(VertexBuffer&&) = default;
        // A vertex buffer can only exist once
        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&)& = delete;
        VertexBuffer& operator=(VertexBuffer&&)& = delete;
        ~VertexBuffer();
        
        void set(const std::vector<T>& data);
        void map(const Shader& shader, GLuint location, bool normalized);
        void bind() const;
        size_t length() const
        {
            return m_size;
        }
    private:
        size_t m_size;
        OpenGLVertexBufferID_t m_vbo;
    };

    template<typename T, bool ELEMENT_BUFFER>
    VertexBuffer<T, ELEMENT_BUFFER>::VertexBuffer():
        m_size(0)
    {
        glGenBuffers(1, &m_vbo);
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T, bool ELEMENT_BUFFER>
    VertexBuffer<T, ELEMENT_BUFFER>::~VertexBuffer()
    {
        glDeleteVertexArrays(1, &m_vbo);
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T, bool ELEMENT_BUFFER> void
    VertexBuffer<T, ELEMENT_BUFFER>::bind() const
    {
        if (ELEMENT_BUFFER)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo);
            GLWrapper::GLErrorThrow();
        }
        else
        {
            glBindVertexArray(m_vbo);
            GLWrapper::GLErrorThrow();
        }
    }
    
    template<typename T, bool ELEMENT_BUFFER> void
    VertexBuffer<T, ELEMENT_BUFFER>::set(const std::vector<T> &data)
    {
        m_size = sizeof(T)*data.size();
        if (ELEMENT_BUFFER)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size, &data[0], GL_STATIC_DRAW);
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            glBufferData(GL_ARRAY_BUFFER, m_size, &data[0], GL_STATIC_DRAW);
        }
        GLWrapper::GLErrorThrow();
    }
    
    template<typename T, bool ELEMENT_BUFFER> void
    VertexBuffer<T, ELEMENT_BUFFER>::map(const Shader& shader,
                                         GLuint location, bool normalized)
    {
        // I don't know what to do in this case
        static_assert(!ELEMENT_BUFFER, "Element array buffers are not supported");
        
        glBindVertexArray(shader.getVAO());
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glVertexAttribPointer(location,
                              GL::TypeInfo<T>::ElementCount,
                              GL::TypeInfo<T>::ElementType,
                              normalized,
                              0, 0);
        GLWrapper::GLErrorThrow();
    }
}

#endif /* VertexBuffer_hpp */
