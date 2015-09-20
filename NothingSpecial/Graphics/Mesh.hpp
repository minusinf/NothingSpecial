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
        Mesh();
        virtual ~Mesh();
        virtual void render() const;
        
        std::vector<float> m_vertices;
        std::vector<float> m_colors;
        Shader m_shader;
        VertexBuffer<float> m_verticesVBO;
        VertexBuffer<float> m_colorsVBO;
    };
}

#endif /* Mesh_hpp */
