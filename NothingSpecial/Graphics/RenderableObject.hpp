//
//  RenderableObject.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef RenderableObject_hpp
#define RenderableObject_hpp

#include "Camera.hpp"

namespace Graphics {
    class RenderableObject
    {
    public:
        RenderableObject();
        virtual ~RenderableObject();
        virtual void render(const Camera& camera) const = 0;
        virtual const mat4& modelMatrix() const;
    private:
        virtual mat4& modelMatrix();
        mat4 m_ModelMatrix;
    };
}

#endif /* RenderableObject_hpp */
