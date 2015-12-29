//
//  RenderableObject.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "RenderableObject.hpp"

using namespace Graphics;

RenderableObject::RenderableObject():
    m_ModelMatrix(mat4::Identity())
{
    
}

RenderableObject::~RenderableObject()
{
    
}

const mat4&
RenderableObject::modelMatrix() const
{
    return m_ModelMatrix;
}

mat4&
RenderableObject::modelMatrix()
{
    return m_ModelMatrix;
}