//
//  GraphicsException.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 19/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef GraphicsException_h
#define GraphicsException_h

#include "base.hpp"
#include <exception>

namespace Graphics {
    class GraphicsException: std::exception
    {
    public:
        GraphicsException(const std::string& msg):
            m_msg(msg)
        {
            
        }
        GraphicsException(const GraphicsException& other):
            m_msg(other.m_msg)
        {
            
        }
        virtual const char* what() const _NOEXCEPT
        {
            return m_msg.c_str();
        }
        virtual void print() const _NOEXCEPT
        {
            std::cerr << "Encountered a Graphics Exception:\n" << m_msg << std::endl;
        }
    private:
        const std::string m_msg;
    };
    
    class ShaderException: public GraphicsException
    {
    public:
        ShaderException(const std::string& msg):
            GraphicsException(msg)
        {
            print();
        }
        ShaderException(const ShaderException& other):
            GraphicsException(other)
        {
            
        }
        virtual void print() const _NOEXCEPT
        {
            std::cerr << "Encountered a Shader Exception:\n" << what() << std::endl;
        }
    };
    
    class OpenGLException: public GraphicsException
    {
    public:
        OpenGLException(const std::string& msg):
            GraphicsException(msg)
        {
            print();
        }
        OpenGLException(const OpenGLException& other):
            GraphicsException(other)
        {
            
        }
        virtual void print() const _NOEXCEPT
        {
            std::cerr << "Encountered an OpenGL Exception:\n" << what() << std::endl;
        }
    };
    
    class MeshException: public GraphicsException
    {
    public:
        MeshException(const std::string& msg):
            GraphicsException(msg)
        {
            print();
        }
        MeshException(const MeshException& other):
            GraphicsException(other)
        {
            
        }
        virtual void print() const _NOEXCEPT
        {
            std::cerr << "Encountered a Mesh Exception:\n" << what() << std::endl;
        }
    };
}


#endif /* GraphicsException_h */
