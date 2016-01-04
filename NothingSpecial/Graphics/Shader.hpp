/*******************************************************************************
 Copyright (C) 2012 Adrian Blumer (blumer.adrian@gmail.com)
 TerrainErosion Graphics Library
 Copyright (C) 2015 Pascal Spörri (me@pascalspoerri.ch)
 
 All Rights Reserved.
 
 You may use, distribute and modify this code under the terms of the
 MIT license (http://opensource.org/licenses/MIT).
 *******************************************************************************/

#ifndef Shader_hpp
#define Shader_hpp

#include "base.hpp"
#include "GLHelper.hpp"
#include "TextureBuffer.hpp"

namespace Graphics {
    class Shader
    {
        typedef struct UniformInfo
        {
            std::string Name;                   /// name of the uniform variable
            GL::ShaderVariableType Type;        /// type of the uniform variable
            int Length;                         /// length of the uniform array
            uint Location;                      /// location property
        } UniformInfo;
        
        typedef struct AttributeInfo
        {
            std::string Name;
            GL::ShaderVariableType Type;
            int Length;
            int Location;
            bool Present;
        } AttributeInfo;
        
    public:
        Shader(const std::string& vertexShaderPath,
               const std::string& fragmentShaderPath);
        ~Shader();
        
        void reload();
        static void toggleShaderRefresh();
        
        void bind() const;
        void unbind() const;
        static void unbindCurrent();
        
        const std::string& vertexShaderPath();
        const std::string& fragmentShaderPath();
        
        OpenGLShaderProgramID_t programID();
        
        GLuint getVAO() const;
        
        /// Set Uniforms
        bool setUniform(const std::string& name, const vec2& v) const;
        bool setUniform(const std::string& name, const vec3& v) const;
        bool setUniform(const std::string& name, const vec4& v) const;
        bool setUniform(const std::string& name, const mat4& v, bool transpose = false) const;
        bool setUniform(const std::string& name, bool v) const;
        bool setUniform(const std::string& name, int v) const;
        bool setUniform(const std::string& name, const TextureBuffer* tex) const;

        /// Attributes
        bool mapAttribute(const std::string& name, uint location);
        GLuint attributeLocation(const std::string& name);
        
    protected:
        void loadUniformInfo();
        void loadAttributeInfo();
        
        uint32_t getSetTextureUnit(const std::string& name) const;
    private:
        const std::string m_vertexShaderPath;
        const std::string m_fragmentShaderPath;
        
        static std::string loadShader(const std::string& source);
        static bool m_refreshShaders;

        // OpenGL
        bool m_compiled;
        OpenGLShaderProgramID_t m_pId;
        OpenGLShaderID_t m_fId;
        OpenGLShaderID_t m_vId;
        
        GLuint  m_vao;
        // Uniforms
        GLuint m_uniformCount;
        std::unordered_map<std::string, UniformInfo> m_uniformInfo;
        
        GLuint m_attributeCount;
        std::unordered_map<std::string, AttributeInfo> m_attributeInfo;
        
        // Texture units
        mutable std::unordered_map<std::string, uint32_t> m_textureUnitMapping;
        
    private:
        
        static const Shader* ms_boundShader;
    };
}
#endif /* Shader_hpp */
