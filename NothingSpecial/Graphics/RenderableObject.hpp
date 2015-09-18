//
//  RenderableObject.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef RenderableObject_hpp
#define RenderableObject_hpp

namespace Graphics {
    class RenderableObject
    {
    public:
        RenderableObject();
        virtual ~RenderableObject();
        virtual void render() const;
    };
}

#endif /* RenderableObject_hpp */
