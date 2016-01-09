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
#include "Geometry.hpp"

using namespace Graphics;

void
MeshFactory::loadObj(Scene &scene, const std::string &path)
{
    loadObj(scene, path, false);
}

void
MeshFactory::loadObj(Scene &scene, const std::string &path,  bool drawAsPolygon)
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
        std::cout << "Adding shape" << std::endl;
        
        const auto& objIndices = shape.mesh.indices;
        const auto& objPositions = shape.mesh.positions;
        
        if ((objPositions.size() % 3 != 0)
            && (objIndices.size() % 3 != 0))
        {
            throw GraphicsException("Obj has wrong format");
        }
        size_t nVertices = objPositions.size()/3;
        size_t nIndices = objIndices.size()/3;
        
        std::vector<vec3> vertices(nVertices);
        std::vector<vec4> colors(nVertices, vec4(1,1,1,1));
        std::vector<face> faces(nIndices);
        
        for (size_t idx=0; idx < nVertices; ++idx)
        {
            vertices[idx].x() = objPositions[idx*3];
            vertices[idx].y() = objPositions[idx*3+1];
            vertices[idx].z() = objPositions[idx*3+2];
            std::cout << "vec3(" << vertices[idx].x() << ", " << vertices[idx].y() << ", "
                      << vertices[idx].z() << ")" << std::endl;
        }
        
        for (size_t idx=0; idx < nIndices; ++idx)
        {
            faces[idx].x() = objIndices[idx*3];
            faces[idx].y() = objIndices[idx*3+1];
            faces[idx].z() = objIndices[idx*3+2];
            std::cout << "face(" << faces[idx].x() << ", " << faces[idx].y() << ", "
                      << faces[idx].z() << ")" << std::endl;
        }
        
        scene.addObject(std::make_shared<Mesh>(std::move(vertices),
                                               std::move(colors),
                                               std::move(faces),
                                               drawAsPolygon));
        std::cout << "Added obj" << std::endl;
    }
}

std::shared_ptr<Graphics::Mesh>
MeshFactory::createCube()
{
    return createCube(false);
}

std::shared_ptr<Graphics::Mesh>
MeshFactory::createCube(bool drawAsPolygon)
{
    std::vector<vec3> vertices;
    std::vector<face> faces;
    Math::Geometry::generateCube(vertices, faces);
    
    std::vector<vec4> colors(vertices.size(), vec4(1,1,1,1));
    return std::make_shared<Mesh>(std::move(vertices),
                                  std::move(colors),
                                  std::move(faces),
                                  drawAsPolygon);
}

void
MeshFactory::addCube(Scene &scene, bool drawAsPolygon)
{
    scene.addObject(createCube(drawAsPolygon));
}

void
MeshFactory::addCube(Scene &scene)
{
    addCube(scene, false);
}