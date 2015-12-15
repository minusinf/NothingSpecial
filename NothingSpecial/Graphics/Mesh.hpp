//
//  Mesh.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp
#include "base.hpp"
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "RenderableObject.hpp"

namespace Graphics {
    class Mesh: public RenderableObject
    {
    public:
        Mesh(std::vector<vec4>&& vertices,
             std::vector<vec4>&& colors,
             std::vector<face>&& faces);
        Mesh();
        virtual ~Mesh();
        virtual void render() const;
        
        std::vector<vec4> m_vertices;
        std::vector<vec4> m_colors;
        std::vector<face> m_faces;
        Shader m_shader;
        VertexBuffer<vec4> m_verticesVBO;
        VertexBuffer<vec4> m_colorsVBO;
        VertexBuffer<face> m_facesVBO;
    };
}

#endif /* Mesh_hpp */
