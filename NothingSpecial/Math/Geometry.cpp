//
//  Geometry.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 29/12/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Geometry.hpp"

using namespace Math;

std::vector<vec3>
Geometry::computeFaceNormals(const std::vector<vec3> &vertices,
                             const std::vector<face> &faces)
{
    std::vector<vec3> normals;
    normals.reserve(faces.size());
    for (const face& face: faces)
    {
        const vec3& a = vertices[face.x()];
        const vec3& b = vertices[face.y()];
        const vec3& c = vertices[face.z()];
        
        vec3 v1 = b-a;
        vec3 v2 = c-a;
        normals.push_back(v1.cross(v2).normalized());
    }
    return normals;
}

std::vector<vec3>
Geometry::computeVertexNormals(const std::vector<vec3> &vertices,
                               const std::vector<face> &faces)
{
    std::vector<vec3> normals(vertices.size(), vec3(0,0,0));
    
    std::vector<vec3> face_normals = computeFaceNormals(vertices, faces);
    
    for (auto i=0; i<faces.size(); ++i)
    {
        const face& face = faces[i];
        const vec3& face_normal = face_normals[i];
        
        for (size_t j=0; j<3; ++j)
        {
            auto idx=face(j);
            // TODO weight the face normals by angle
            normals[idx] += face_normal;
        }
    }
    
    for (vec3& v: normals)
    {
        v.normalize();
    }
    return normals;
}