//
//  Shader.hpp
//  NothingSpecial
//
//  Created by Pascal Spörri on 18/09/15.
//  Copyright © 2015 Pascal Spörri. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include "base.hpp"

namespace Graphics {
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderPath,
               const std::string& fragmentShaderPath);
        ~Shader();
        
        void reload();
        static void toggleShaderRefresh();
        
        void bind() const;
        void unbind() const;
        static void unbindCurrent();
    private:
        const std::string m_vertexShaderPath;
        const std::string m_fragmentShaderPath;
        
        static std::string loadShader(const std::string& source);
        static bool m_refreshShaders;

        // OpenGL
        bool m_compiled;
        GLuint m_pId;
        GLuint m_fId;
        GLuint m_vId;
        
        static const Shader* ms_boundShader;
    };
}
#endif /* Shader_hpp */
