//
//  ShaderException.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "ShaderException.hpp"

using namespace::Graphics;

ShaderException::ShaderException(const std::string& msg):
    m_msg(msg)
{
    
}
ShaderException::ShaderException(const ShaderException& other):
    m_msg(other.m_msg)
{
    
}

const char*
ShaderException::what() const _NOEXCEPT
{
    return m_msg.c_str();
}