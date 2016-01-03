//
//  MeshFactory.h
//  NothingSpecial
//
//  Created by Pascal Spörri on 23/09/15.
//  Copyright (c) 2015 Pascal Spörri. All rights reserved.
//

#ifndef __NothingSpecial__MeshFactory__
#define __NothingSpecial__MeshFactory__

#include "base.hpp"
#include "Scene.hpp"
namespace Graphics {
    class MeshFactory
    {
    public:
        static void loadObj(Scene& scene, const std::string& path, bool drawAsPolygon);
        static void loadObj(Scene& scene, const std::string& path);
    };
}
#endif /* defined(__NothingSpecial__MeshFactory__) */
