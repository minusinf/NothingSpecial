//
//  Volume.cpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 30/12/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#include "Volume.hpp"

using namespace Graphics;

Volume::Volume(std::shared_ptr<matXb> data, const vec3& color):
    m_data(data),
    m_color(color)
{
    
}