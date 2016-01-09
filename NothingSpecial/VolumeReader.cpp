//
//  VolumeReader.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 03/01/16.
//  Copyright © 2016 Pascal Spörri. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <exception>

#include "VolumeReader.hpp"

std::shared_ptr<Math::Grid3D<float>>
VolumeReader::readRaw(const std::string& filename, const vec3& extents)
{
    auto grid = Math::Grid3D<uint8_t>(extents.x(), extents.y(), extents.z());
    
    using namespace std;
    ifstream file(filename, ios::in|ios::binary|ios::ate);
    if (!file.is_open())
    {
        throw invalid_argument("Can't open the provided file "+filename);
    }
    auto filesize = file.tellg();
    if (filesize != grid.count())
    {
        throw runtime_error("Invalid size: Exepecting "+to_string(grid.count())+
                            "bytes and got "+to_string(filesize)+" instead.");
    }
    file.seekg(0, ios::beg);
    file.read((char*) grid.raw(), filesize);
    file.close();
    
    auto val = std::make_shared<Math::Grid3D<float>>(&grid);
    return val;
}

std::shared_ptr<Math::Grid3D<float>>
VolumeReader::createBox(const vec3 &extents)
{
    auto grid = std::make_shared<Math::Grid3D<float>>(extents.x(), extents.y(), extents.z());
    for (size_t i=0; i<grid->count(); i++)
    {
        (*grid)[i] = 1.0;
    }
    return grid;
}