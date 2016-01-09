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
        RenderableObject() = default;
        RenderableObject(const RenderableObject&) = default;
        RenderableObject(RenderableObject&&) = default;
        RenderableObject& operator=(const RenderableObject&)& = default;
        RenderableObject& operator=(RenderableObject&&)& = default;
        virtual ~RenderableObject();
        virtual void render(const Camera& camera) const = 0;
        virtual const mat4& modelMatrix() const;
    protected:
        virtual mat4& modelMatrix();
        mat4 m_ModelMatrix = mat4::Identity();
    };
}

#endif /* RenderableObject_hpp */
