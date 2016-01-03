//
//  Geometry.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 29/12/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include "base.hpp"

namespace Math {
    class Geometry
    {
    public:
        static std::vector<vec3>
        computeFaceNormals(const std::vector<vec3>& vertices,
                           const std::vector<face>& faces);
        static std::vector<vec3>
        computeVertexNormals(const std::vector<vec3>& vertices,
                             const std::vector<face>& faces);
        static void
        generateCube(std::vector<vec3>& vertices,
                     std::vector<face>& faces);
    };
}

#endif /* Geometry_hpp */
