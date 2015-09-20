//
//  OpenGLWrapper.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef OpenGLWrapper_hpp
#define OpenGLWrapper_hpp

#include <string>

namespace Graphics
{
   class GLWrapper
    {
    public:
        static bool GLError();
        static bool GLError(std::string& errorString);
        static void GLErrorThrow();
    };
}
#endif /* OpenGLWrapper_hpp */
