//
//  OpenGLWrapper.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "GLWrapper.hpp"
#include "base.hpp"
#include "GraphicsException.hpp"
#include <sstream>
using namespace Graphics;


bool
GLWrapper::GLError()
{
    GLenum error = glGetError();
    if (error == GL_NO_ERROR)
    {
        return false;
    }
    return true;
}

bool
GLWrapper::GLError(std::string &errorString)
{
    GLenum error = glGetError();
    if (error == GL_NO_ERROR)
    {
        return false;
    }
    std::stringstream stream;
    const char* charstr = (const char*)glGetString(error);
    if (charstr != NULL)
    {
        stream << glGetString(error);
    }
    else
    {
        stream << "Code " << std::to_string(error);
    }
    errorString = stream.str();
    return true;
}

void
GLWrapper::GLErrorThrow()
{
    std::string error;
    if (GLError(error))
    {
        throw OpenGLException(error);
    }
}