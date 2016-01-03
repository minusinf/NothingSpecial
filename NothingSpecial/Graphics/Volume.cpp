//
//  Volume.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 30/12/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Volume.hpp"
#include "Geometry.hpp"

using namespace Graphics;

#define SHADER_PATH "Graphics/shaders/"

Volume::Volume(std::shared_ptr<Math::Grid3D<float>> data, const vec3& color):
    m_data(data),
    m_color(color),
    m_shader(BASE_PATH SHADER_PATH "volume.vert",
             BASE_PATH SHADER_PATH "volume.frag")
{
    GLWrapper::GLErrorThrow();
    m_textureBuffer.set((*m_data).raw(), (*m_data).dimX(), (*m_data).dimY(), (*m_data).dimZ());
    GLWrapper::GLErrorThrow();

    initCube();
}

void
Volume::render(const Camera &camera) const
{
    glEnable(GL_CULL_FACE);

    m_shader.bind();
    m_shader.setUniform("uViewMatrix", camera.view());
    m_shader.setUniform("uProjMatrix", camera.proj());
    m_shader.setUniform("uModelMatrix", modelMatrix());
    
    glUseProgram(0);
    GLWrapper::GLErrorThrow();
    
    m_shader.unbind();
    
    glDisable(GL_CULL_FACE);
}

void
Volume::initCube()
{
    std::vector<vec3> vertices;
    std::vector<face> faces;
    Math::Geometry::generateCube(vertices, faces);
    
    m_cubeVerticesVBO.set(vertices);
    m_cubeVerticesVBO.map(m_shader, m_shader.attributeLocation("inPosition"), false);
    
    m_cubeFacesVBO.set(faces);
}