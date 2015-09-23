//
//  MeshFactory.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 23/09/15.
//  Copyright (c) 2015 Pascal Spörri. All rights reserved.
//

#include "MeshFactory.h"
#include "Mesh.hpp"
#include "GraphicsException.hpp"
#include "tiny_obj_loader.h"

using namespace Graphics;

void
MeshFactory::loadObj(Scene &scene, const std::string &path)
{
    std::vector<tinyobj::shape_t> m_shapes;
    std::vector<tinyobj::material_t> m_materials;
    std::string err = tinyobj::LoadObj(m_shapes, m_materials, path.c_str());
    if (!err.empty())
    {
        if (err.find("Warning"))
        {
            std::cerr << err << std::endl;
        }
        else
        {
            throw GraphicsException(err);
        }
    }
    
    for (const auto& shape: m_shapes)
    {
        
    }
}