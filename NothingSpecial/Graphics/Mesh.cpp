//
//  Mesh.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Mesh.hpp"
#include "GLWrapper.hpp"

using namespace::Graphics;

#define SHADER_PATH "Graphics/shaders/"

Mesh::Mesh(std::vector<vec4>&& vertices,
           std::vector<vec4>&& colors,
           std::vector<face>&& faces):
    m_vertices(vertices),
    m_colors(colors),
    m_faces(faces),
    m_shader(BASE_PATH SHADER_PATH "simple.vert",
             BASE_PATH SHADER_PATH "simple.frag")
{
    GLWrapper::GLErrorThrow();
    m_shader.bind();
    m_verticesVBO.set(m_vertices);
    m_verticesVBO.map(m_shader, m_shader.attributeLocation("in_Position"), false);
    
    m_colorsVBO.set(m_colors);
    m_colorsVBO.map(m_shader, m_shader.attributeLocation("in_Color"), false);
    GLWrapper::GLErrorThrow();

    m_facesVBO.set(m_faces);
    GLWrapper::GLErrorThrow();
    
    m_shader.unbind();
    GLWrapper::GLErrorThrow();
    

}

Mesh::Mesh():
    m_shader(BASE_PATH SHADER_PATH "simple.vert",
             BASE_PATH SHADER_PATH "simple.frag")
{
    m_vertices = {
        vec4(0.0f,  0.5f,  0.0f, 1.0f),
        vec4(0.5f, -0.5f,  0.0f, 1.0f),
        vec4(-0.5f, -0.5f,  0.0f, 1.0f)};
    m_colors = {
        vec4(1.0f, 0.0f, 0.0f, 1.0f),
        vec4(0.0f, 1.0f, 0.0f, 1.0f),
        vec4(0.0f, 0.0f, 1.0f, 1.0f)};
    
    
    GLWrapper::GLErrorThrow();
    m_shader.bind();
    m_verticesVBO.set(m_vertices);
    m_verticesVBO.map(m_shader, m_shader.attributeLocation("in_Position"), false);

    m_colorsVBO.set(m_colors);
    m_colorsVBO.map(m_shader, m_shader.attributeLocation("in_Color"), false);
    m_shader.unbind();
    
    GLWrapper::GLErrorThrow();
}

Mesh::~Mesh()
{
    
}

void
Mesh::render() const
{
    std::cout << "Rendering" << std::endl;
    m_shader.bind();
//    m_verticesVBO.bind();
//    m_colorsVBO.bind();
    GLWrapper::GLErrorThrow();
    
    m_facesVBO.bind();
    glDrawElements(GL_TRIANGLES, m_facesVBO.length()/3, GL_UNSIGNED_INT, (void*) NULL);
//    glDrawArrays(GL_TRIANGLES, m_faces.size()*3, GL_UNSIGNED_INT, 0);
//    m_facesVBO.
////    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, NULL);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    GLWrapper::GLErrorThrow();
    
    glBindVertexArray(0);
    GLWrapper::GLErrorThrow();
    
    glUseProgram(0);
    GLWrapper::GLErrorThrow();

}