//
//  VolumeReader.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 03/01/16.
//  Copyright © 2016 Pascal Spörri. All rights reserved.
//

#ifndef VolumeReader_hpp
#define VolumeReader_hpp

#include "base.hpp"
#include "Grid3D.hpp"

class VolumeReader
{
public:
    static std::shared_ptr<Math::Grid3D<float>> readRaw(const std::string& filename, const vec3& extents);
    static std::shared_ptr<Math::Grid3D<float>> createBox(const vec3& extents);
};

#endif /* VolumeReader_hpp */
