//
//  ShaderException.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef ShaderException_hpp
#define ShaderException_hpp

#include <exception>
#include <string>
namespace Graphics {
    class ShaderException: std::exception
    {
    public:
        ShaderException(const std::string& msg);
        ShaderException(const ShaderException& other);
        virtual const char* what() const _NOEXCEPT;
    private:
        const std::string m_msg;
    };
}

#endif /* ShaderException_hpp */
