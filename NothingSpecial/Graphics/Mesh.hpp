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
        Mesh(const Mesh&) = default;
        Mesh(Mesh&&) = default;
        Mesh& operator=(const Mesh&)& = default;
        Mesh& operator=(Mesh&&)& = default;
     
        Mesh(const std::vector<vec3>& vertices,
             const std::vector<vec4>& colors,
             const std::vector<face>& faces,
             bool drawAsPolygon);
        
        Mesh(const std::vector<vec3>& vertices,
             const std::vector<vec4>& colors,
             const std::vector<face>& faces);

        Mesh(const std::vector<vec3>& vertices,
             const std::vector<face>& faces);
        
        virtual ~Mesh();
        virtual void render(const Camera& camera) const;
        
    private:
        std::vector<vec3> m_vertices;
        std::vector<vec4> m_colors;
        std::vector<face> m_faces;
        std::vector<vec3> m_normals;

        const bool m_drawPolygons;
        
        Shader m_shader;
        VertexBuffer<vec3> m_verticesVBO;
        VertexBuffer<vec4> m_colorsVBO;
        VertexBuffer<face, true> m_facesVBO;
        VertexBuffer<vec3> m_normalsVBO;
    };
}

#endif /* Mesh_hpp */
