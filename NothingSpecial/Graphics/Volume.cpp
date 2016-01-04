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

Volume::Volume(std::shared_ptr<Math::Grid3D<uint8_t>> data):
    m_data(data),
    m_shader(BASE_PATH SHADER_PATH "volume.vert",
             BASE_PATH SHADER_PATH "volume.frag"),
    m_textureBackFace({{GL_TEXTURE_WRAP_S, GL_REPEAT},
                      {GL_TEXTURE_WRAP_T, GL_REPEAT},
                      {GL_TEXTURE_MIN_FILTER, GL_NEAREST},
                      {GL_TEXTURE_MAG_FILTER, GL_NEAREST}}),
    m_textureBuffer({{GL_TEXTURE_MAG_FILTER, GL_LINEAR},
                     {GL_TEXTURE_MIN_FILTER, GL_LINEAR},
                     {GL_TEXTURE_WRAP_S, GL_REPEAT},
                     {GL_TEXTURE_WRAP_T, GL_REPEAT},
                     {GL_TEXTURE_WRAP_R, GL_REPEAT}})
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
    m_shader.setUniform("uVolumeTex", &m_textureBuffer);
    
    m_cubeFacesVBO.bind();
    glDrawElements(GL_TRIANGLES, m_cubeFacesVBO.length(), GL_UNSIGNED_INT, (void*) NULL);
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