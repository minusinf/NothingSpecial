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
#include <stdint.h>

#include <iostream>
#include <fstream>
#include <exception>
#include <limits>
template<typename T = uint8_t>
class VolumeReader
{
public:
    static std::shared_ptr<Math::Grid3D<float>> readRaw(const std::string& filename, const vec3& extents);
    static std::shared_ptr<Math::Grid3D<float>> createBox(const vec3& extents);
};

template<typename T> std::shared_ptr<Math::Grid3D<float>>
VolumeReader<T>::readRaw(const std::string& filename, const vec3& extents)
{
    auto grid = Math::Grid3D<T>(extents.x(), extents.y(), extents.z());
    
    using namespace std;
    ifstream file(filename, ios::in|ios::binary|ios::ate);
    if (!file.is_open())
    {
        throw invalid_argument("Can't open the provided file "+filename);
    }
    auto filesize = file.tellg();
    if (filesize != grid.count()*sizeof(T))
    {
        throw runtime_error("Invalid size: Exepecting "+to_string(grid.count())+
                            "bytes and got "+to_string(filesize)+" instead.");
    }
    file.seekg(0, ios::beg);
    file.read((char*) grid.raw(), filesize);
    file.close();
    
    auto val = std::make_shared<Math::Grid3D<float>>(&grid);
    // Normalize raw files to a range between 0.0 and 1.0
    const float scale = 1.0/(float) std::numeric_limits<T>::max();
    for (size_t i=0; i<val->count(); ++i)
    {
        (*val)[i] = (*val)[i]*scale;
    }
    return val;
}

template<typename T>
std::shared_ptr<Math::Grid3D<float>>
VolumeReader<T>::createBox(const vec3 &extents)
{
    auto grid = std::make_shared<Math::Grid3D<float>>(extents.x(), extents.y(), extents.z());
    for (size_t i=0; i<grid->count(); i++)
    {
        (*grid)[i] = 1.0;
    }
    return grid;
}

#endif /* VolumeReader_hpp */
