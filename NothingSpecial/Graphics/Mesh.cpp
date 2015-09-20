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

Mesh::Mesh():
    m_shader(BASE_PATH SHADER_PATH "simple.vert",
             BASE_PATH SHADER_PATH "simple.frag"),
    m_colorsVBO(),
    m_verticesVBO()
{
    m_vertices = {
        -0.8f, -0.8f, 0.0f, 1.0f,
        0.0f,  0.8f, 0.0f, 1.0f,
        0.8f, -0.8f, 0.0f, 1.0f};
    m_colors = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f};
    
    GLWrapper::GLErrorThrow();
    m_shader.bind();
    m_verticesVBO.set(m_vertices);
    m_verticesVBO.map(0, false);

    m_colorsVBO.set(m_colors);
    m_colorsVBO.map(1, false);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}