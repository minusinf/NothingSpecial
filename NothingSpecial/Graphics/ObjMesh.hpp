//
//  ObjMesh.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 19/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef ObjMesh_hpp
#define ObjMesh_hpp

#include "base.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

#include "tiny_obj_loader.h"
namespace Graphics {
    class ObjMesh:public Mesh
    {
    public:
        ObjMesh(const std::string& path, const Shader& shader);
        ObjMesh(const std::string& path);
        virtual ~ObjMesh();
        virtual void render() const;
        
    private:
        const Shader m_shader;
        std::vector<tinyobj::shape_t> m_shapes;
        std::vector<tinyobj::material_t> m_materials;
    };
}

#endif /* ObjMesh_hpp */
