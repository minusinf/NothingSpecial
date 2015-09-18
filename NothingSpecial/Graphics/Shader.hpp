//
//  Shader.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>

namespace Graphics {
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderSource,
               const std::string& fragmentShaderSource);
        
    private:
        const std::string m_vertexShaderSource;
        const std::string m_fragmentShaderSource;
        
        static std::string loadShader(const std::string& source);
    };
}
#endif /* Shader_hpp */
