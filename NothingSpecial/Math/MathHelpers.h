//
//  MathHelpers.h
//  NothingSpecial
//
//  Created by Pascal Spörri on 29/12/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef MathHelpers_h
#define MathHelpers_h

#include <cmath>
namespace Math {
    
    template<typename T>
    T toRadians(T degrees)
    {
        return degrees*M_PI/180.0;
    }
    
    template<typename  T>
    T toDegrees(T radians)
    {
        return radians/M_PI*180.0;
    }
}


#endif /* MathHelpers_h */
