//
//  Volume.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 30/12/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Volume.hpp"

using namespace Graphics;

#define SHADER_PATH "Graphics/shaders/"

Volume::Volume(std::shared_ptr<matX> data, const vec3& color):
    m_data(data),
    m_color(color),
    m_shader(BASE_PATH SHADER_PATH "volume.vert",
             BASE_PATH SHADER_PATH "volume.frag")
{
    GLWrapper::GLErrorThrow();
    m_textureBuffer.set(data->data(), data->rows(), data->cols(), 1);
    GLWrapper::GLErrorThrow();

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