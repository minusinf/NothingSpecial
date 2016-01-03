//
//  Volume.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 30/12/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef Volume_hpp
#define Volume_hpp

#include "base.hpp"
#include "RenderableObject.hpp"
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "TextureBuffer3D.hpp"
#include "TextureBuffer2D.hpp"
#include "Grid3D.hpp"

namespace Graphics {
    class Volume: public RenderableObject
    {
    public:
        Volume(const Volume&) = delete;
        Volume(Volume&&) = default;
        Volume& operator=(const Volume&)& = delete;
        Volume& operator=(Volume&&)& = delete;
        
        // For the moment we want to restrict ourselves to chars
        Volume(std::shared_ptr<matX> data, const vec3& color);
        
        virtual void render(const Camera& camera) const;
    private:
        std::shared_ptr<matX> m_data;
        vec3 m_color;
        
        Shader m_shader;
        TextureBuffer3D<float, TextureFormat::Float> m_textureBuffer;
        
        void initCube();
        VertexBuffer<vec3> m_cubeVerticesVBO;
        VertexBuffer<face, true> m_cubeFacesVBO;
    };
}

#endif /* Volume_hpp */
