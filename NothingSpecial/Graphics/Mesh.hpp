//
//  Mesh.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include "RenderableObject.hpp"
namespace Graphics {
    class Mesh: public RenderableObject
    {
    public:
        Mesh();
        virtual ~Mesh();
        virtual void render() const;
    };
}

#endif /* Mesh_hpp */
