//
//  Mesh.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Mesh.hpp"
#include "GLWrapper.hpp"
#include "Geometry.hpp"
using namespace::Graphics;

#define SHADER_PATH "Graphics/shaders/"

Mesh::Mesh(const std::vector<vec3>& vertices,
           const std::vector<vec4>& colors,
           const std::vector<face>& faces,
           bool drawAsPolygon):
    RenderableObject(),
    m_vertices(vertices),
    m_colors(colors),
    m_faces(faces),
    m_normals(Math::Geometry::computeVertexNormals(m_vertices, m_faces)),
    m_drawPolygons(drawAsPolygon),
    m_shader(drawAsPolygon? BASE_PATH SHADER_PATH "polygon.vert": BASE_PATH SHADER_PATH "diffuse.vert",
             drawAsPolygon? BASE_PATH SHADER_PATH "polygon.frag": BASE_PATH SHADER_PATH"diffuse.frag")
{
    GLWrapper::GLErrorThrow();
    m_shader.bind();
    m_verticesVBO.set(m_vertices);
    m_verticesVBO.map(m_shader, m_shader.attributeLocation("inPosition"), false);
    
    m_facesVBO.set(m_faces);
    GLWrapper::GLErrorThrow();
    
    if (!drawAsPolygon)
    {
        m_colorsVBO.set(m_colors);
        m_colorsVBO.map(m_shader, m_shader.attributeLocation("inColor"), false);
        GLWrapper::GLErrorThrow();
        
        m_normalsVBO.set(m_normals);
        m_normalsVBO.map(m_shader, m_shader.attributeLocation("inNormal"), true);
        GLWrapper::GLErrorThrow();
    }
    
    m_shader.unbind();
    GLWrapper::GLErrorThrow();
}

Mesh::Mesh(const std::vector<vec3>& vertices,
           const std::vector<vec4>& colors,
           const std::vector<face>& faces):
    Mesh(vertices, colors, faces, false)
{
    
}

Mesh::Mesh(const std::vector<vec3>& vertices,
           const std::vector<face>& faces):
    Mesh(vertices,
         std::vector<vec4>(vertices.size(), vec4(1,1,1,1)),
         faces,
         true)
{
    
}

Mesh::~Mesh()
{
    
}

void
Mesh::render(const Camera& camera) const
{
    if (m_drawPolygons)
    {
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glEnable(GL_CULL_FACE);
    }

    m_shader.bind();
    m_shader.setUniform("uViewMatrix", camera.view());
    m_shader.setUniform("uProjMatrix", camera.proj());
    m_shader.setUniform("uModelMatrix", modelMatrix());
    GLWrapper::GLErrorThrow();
    
    m_facesVBO.bind();
    glDrawElements(GL_TRIANGLES, m_facesVBO.length(), GL_UNSIGNED_INT, (void*) NULL);
    GLWrapper::GLErrorThrow();
    
    glBindVertexArray(0);
    GLWrapper::GLErrorThrow();
    
    glUseProgram(0);
    GLWrapper::GLErrorThrow();

    m_shader.unbind();
    
    if (m_drawPolygons)
    {
        glEnable(GL_POLYGON_OFFSET_FILL);
    }
    glDisable(GL_CULL_FACE);
}