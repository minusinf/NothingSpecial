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
        
        Volume(std::shared_ptr<Math::Grid3D<float>> data);
        
        virtual void render(const Camera& camera) const;
    private:
        void renderBackFace(const Camera& camera) const;
        void renderVolume(const Camera& camera) const;
        
        std::shared_ptr<Math::Grid3D<float>> m_data;
        
        Shader m_shaderBackface;
        Shader m_shaderVolume;
        
        mutable TextureBuffer2D<vec3, TextureFormat::Float> m_textureBackface;
        mutable TextureBuffer3D<float, TextureFormat::Float> m_textureBuffer;
        
        void initCube();
        VertexBuffer<vec3> m_cubeVerticesVBO;
        VertexBuffer<face, true> m_cubeFacesVBO;
        
        GLuint m_frameBufferIdx;
    };
}

#endif /* Volume_hpp */
