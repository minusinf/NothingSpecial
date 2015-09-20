//
//  ObjMesh.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 19/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "ObjMesh.hpp"

using namespace Graphics;

#include "GraphicsException.hpp"

#define SHADER_PATH "Graphics/shaders/"


ObjMesh::ObjMesh(const std::string& path, const Shader& shader):
    m_shader(shader)
{
    std::string err = tinyobj::LoadObj(m_shapes, m_materials, path.c_str());
    if (!err.empty())
    {
        if (err.find("Warning"))
        {
            std::cerr << err << std::endl;
        }
        else
        {
            throw MeshException(err);
        }
    }
    std::cout << "Loaded the mesh " << path << " containing "
              << std::to_string(m_shapes.size()) << " shapes and "
              << std::to_string(m_materials.size()) << " materials" << std::endl;
}

ObjMesh::ObjMesh(const std::string& path):
    ObjMesh::ObjMesh(path,
                     Shader(BASE_PATH SHADER_PATH "simple.vert",
                            BASE_PATH SHADER_PATH "simple.frag"))
{

    
}



ObjMesh::~ObjMesh()
{
    
}

void
ObjMesh::render() const
{
    
}