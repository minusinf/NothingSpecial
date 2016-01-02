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

namespace Graphics {
    class Volume: public RenderableObject
    {
    public:
        Volume(const Volume&) = default;
        Volume(Volume&&) = default;
        Volume& operator=(const Volume&)& = default;
        Volume& operator=(Volume&&)& = default;
        
        // For the moment we want to restrict ourselves to chars
        Volume(std::shared_ptr<matXb> data, const vec3& color);
    private:
        std::shared_ptr<matXb> m_data;
        vec3 m_color;
    };
}

#endif /* Volume_hpp */
