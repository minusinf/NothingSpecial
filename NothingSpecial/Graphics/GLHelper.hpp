/*******************************************************************************
 Copyright (C) 2012 Adrian Blumer (blumer.adrian@gmail.com)
    TerrainErosion Graphics Library
 Copyright (C) 2016 Pascal Spörri (me@pascalspoerri.ch)

 All Rights Reserved.
 
 You may use, distribute and modify this code under the terms of the
 MIT license (http://opensource.org/licenses/MIT).
 *******************************************************************************/

#ifndef GLHelper_H
#define GLHelper_H

#include "base.hpp"

typedef GLint OpenGLShaderProgramID_t;
typedef GLint OpenGLShaderID_t;
typedef GLuint OpenGLVertexBufferID_t;
typedef GLuint OpenGLTextureBufferID_t;

namespace Graphics
{
    enum class TextureFormat : uint
    {
        Integer,                /// integer values
        UnsignedInteger,        /// unsigned integer values
        Float,                  /// floating point values
        FloatNormalized,        /// floating point values in [0.0 1.0]
        FloatSignedNormalized   /// floating point values in [-1.0 1.0]
    };
    
    namespace GL
    {
        bool GetCompileStatus(OpenGLShaderID_t id);
        bool GetLinkStatus(OpenGLShaderProgramID_t id);
        std::string GetShaderInfoLog(OpenGLShaderProgramID_t id);
        std::string GetProgramInfoLog(OpenGLShaderProgramID_t id);
        
        /// Sets the source code of a shader.
        void ShaderSource(OpenGLShaderID_t id, const std::string& source);
        
        /// Properties of a shader program.
        
        enum class ProgramProperty : uint
        {
            UniformCount = GL_ACTIVE_UNIFORMS, 					 		/// number of uniforms present in the shader program
            MaxUniformNameLength = GL_ACTIVE_UNIFORM_MAX_LENGTH, 		/// length of the longest uniform name in the program
            AttributeCount = GL_ACTIVE_ATTRIBUTES,						/// number of attributes present in the shader program
            MaxAttributeNameLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,	/// length of the longest attribute name in the program
        };
        
        /// Access to different properties of a shader program.
        int GetProgramProperty(OpenGLShaderProgramID_t id, ProgramProperty p);
        
        /// Types of a shader variable.
        enum class ShaderVariableType : GLenum
        {
            float_t = GL_FLOAT,
            vec2_t = GL_FLOAT_VEC2,
            vec3_t = GL_FLOAT_VEC3,
            vec4_t = GL_FLOAT_VEC4,
            int_t = GL_INT,
            ivec2_t = GL_INT_VEC2,
            ivec3_t = GL_INT_VEC3,
            ivec4_t = GL_INT_VEC4,
            uint_t = GL_UNSIGNED_INT,
            uvec2_t = GL_UNSIGNED_INT_VEC2,
            uvec3_t = GL_UNSIGNED_INT_VEC3,
            uvec4_t = GL_UNSIGNED_INT_VEC4,
            bool_t = GL_BOOL,
            bvec2_t = GL_BOOL_VEC2,
            bvec3_t = GL_BOOL_VEC3,
            bvec4_t = GL_BOOL_VEC4,
            mat2_t = GL_FLOAT_MAT2,
            mat3_t = GL_FLOAT_MAT3,
            mat4_t = GL_FLOAT_MAT4,
            mat2x3_t = GL_FLOAT_MAT2x3,
            mat2x4_t = GL_FLOAT_MAT2x4,
            mat3x2_t = GL_FLOAT_MAT3x2,
            mat3x4_t = GL_FLOAT_MAT3x4,
            mat4x2_t = GL_FLOAT_MAT4x2,
            mat4x3_t = GL_FLOAT_MAT4x3,
            sampler1D_t = GL_SAMPLER_1D,
            sampler2D_t = GL_SAMPLER_2D,
            sampler3D_t = GL_SAMPLER_3D,
            samplerCube_t = GL_SAMPLER_CUBE,
            sampler1DShadow_t = GL_SAMPLER_1D_SHADOW,
            sampler2DShadow_t = GL_SAMPLER_2D_SHADOW,
            sampler1DArray_t = GL_SAMPLER_1D_ARRAY,
            sampler2DArray_t = GL_SAMPLER_2D_ARRAY,
            sampler1DArrayShadow_t = GL_SAMPLER_1D_ARRAY_SHADOW,
            sampler2DArrayShadow_t = GL_SAMPLER_2D_ARRAY_SHADOW,
            sampler2DMS_t = GL_SAMPLER_2D_MULTISAMPLE,
            sampler2DMSArray_t = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
            samplerCubeShadow_t = GL_SAMPLER_CUBE_SHADOW,
            samplerBuffer_t = GL_SAMPLER_BUFFER,
            sampler2DRect_t = GL_SAMPLER_2D_RECT,
            sampler2DRectShadow_t = GL_SAMPLER_2D_RECT_SHADOW,
            isampler1D_t = GL_INT_SAMPLER_1D,
            isampler2D_t = GL_INT_SAMPLER_2D,
            isampler3D_t = GL_INT_SAMPLER_3D,
            isamplerCube_t = GL_INT_SAMPLER_CUBE,
            isampler1DArray_t = GL_INT_SAMPLER_1D_ARRAY,
            isampler2DArray_t = GL_INT_SAMPLER_2D_ARRAY,
            isampler2DMS_t = GL_INT_SAMPLER_2D_MULTISAMPLE,
            isampler2DMSArray_t = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
            isamplerBuffer_t = GL_INT_SAMPLER_BUFFER,
            isampler2DRect_t = GL_INT_SAMPLER_2D_RECT,
            usampler1D_t = GL_UNSIGNED_INT_SAMPLER_1D,
            usampler2D_t = GL_UNSIGNED_INT_SAMPLER_2D,
            usampler3D_t = GL_UNSIGNED_INT_SAMPLER_3D,
            usamplerCube_t = GL_UNSIGNED_INT_SAMPLER_CUBE,
            usampler1DArray_t = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,
            usampler2DArray_t = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
            usampler2DMS_t = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,
            usampler2DMSArray_t = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
            usamplerBuffer_t = GL_UNSIGNED_INT_SAMPLER_BUFFER,
            usampler2DRect_t = GL_UNSIGNED_INT_SAMPLER_2D_RECT,
        };
        
        std::string StringOf(ShaderVariableType e);
        
        
        /** Returns information about a shader uniform.
         *
         *  Params:
         * 		programId =		ID of the shader program.
         *  	index =      	Index of the uniform that should be checked.
         *  	outSize =		Returns the number of entries in case the uniform is an array variable (e.g. vec3[]).
         * 		outType =		Returns the tye of the shader uniform.
         *      outName =		Returns the name of the shader uniform.
         */
        void GetUniformInfo(OpenGLShaderProgramID_t programId,
                            GLuint index,
                            int& outSize,
                            ShaderVariableType& outType,
                            std::string& outName);
        
        GLint GetUniformLocation(OpenGLShaderProgramID_t programId,
                                 std::string& name);
        
        /** Returns information about a shader attribute.
         *
         *  Params:
         * 		programId =		ID of the shader program.
         *  	attributeIdx = 	Index of the attribute that should be checked.
         *  	size =			Returns the number of entries in case the uniform is an array variable (e.g. vec3[]).
         * 		type = 			Returns the tye of the shader uniform.
         * 		name = 			Returns the name of the shader uniform.
         */
        void GetAttributeInfo(OpenGLShaderProgramID_t programId,
                              uint index,
                              int& outSize,
                              ShaderVariableType& outType,
                              std::string& outName);
        
        // TypeInfo
        ///////////////////////////////////////////////////////////////////////////////////
        
        template<typename T>
        struct TypeInfo;
        
        template<>
        struct TypeInfo<vec4>
        {
            static constexpr GLuint ElementType      = GL_FLOAT;
            static constexpr uint32_t ElementCount   = 4;
            // one of GL_RED, GL_RG, GL_RGB, GL_RGBA
            static constexpr GLuint TexFormat        = GL_RGBA;
            static constexpr uint32_t BitsPerChannel = 32;
        };

        template<>
        struct TypeInfo<vec3>
        {
            static constexpr GLuint ElementType      = GL_FLOAT;
            static constexpr uint32_t ElementCount   = 3;
            // one of GL_RED, GL_RG, GL_RGB, GL_RGBA
            static constexpr GLuint TexFormat        = GL_RGB;
            static constexpr uint32_t BitsPerChannel = 32;
        };

        template<>
        struct TypeInfo<vec2>
        {
            static constexpr GLuint ElementType      = GL_FLOAT;
            static constexpr uint32_t ElementCount   = 2;
            // one of GL_RED, GL_RG, GL_RGB, GL_RGBA
            static constexpr GLuint TexFormat        = GL_RG;
            static constexpr uint32_t BitsPerChannel = 32;
        };
        
        template<>
        struct TypeInfo<float>
        {
            static constexpr GLuint ElementType      = GL_FLOAT;
            static constexpr uint32_t ElementCount   = 1;
            // one of GL_RED, GL_RG, GL_RGB, GL_RGBA
            static constexpr GLuint TexFormat        = GL_RED;
            static constexpr uint32_t BitsPerChannel = 32;
        };

        template<>
        struct TypeInfo<int32_t>
        {
            static constexpr GLuint ElementType      = GL_INT;
            static constexpr uint32_t ElementCount   = 1;
            // one of GL_RED, GL_RG, GL_RGB, GL_RGBA
            static constexpr GLuint TexFormat        = GL_RED_INTEGER;
            static constexpr uint32_t BitsPerChannel = 32;
        };

        template<>
        struct TypeInfo<uint32_t>
        {
            static constexpr GLuint ElementType      = GL_UNSIGNED_INT;
            static constexpr uint32_t ElementCount   = 1;
            // one of GL_RED, GL_RG, GL_RGB, GL_RGBA
            static constexpr GLuint TexFormat        = GL_RED_INTEGER;
            static constexpr uint32_t BitsPerChannel = 32;
        };
        
        template<>
        struct TypeInfo<int8_t>
        {
            static constexpr GLuint ElementType      = GL_BYTE;
            static constexpr uint32_t ElementCount   = 1;
            // one of GL_RED, GL_RG, GL_RGB, GL_RGBA
            static constexpr GLuint TexFormat        = GL_RED_INTEGER;
            static constexpr uint32_t BitsPerChannel = 8;
        };

        template<>
        struct TypeInfo<uint8_t>
        {
            static constexpr GLuint ElementType      = GL_UNSIGNED_BYTE;
            static constexpr uint32_t ElementCount   = 1;
            // one of GL_RED, GL_RG, GL_RGB, GL_RGBA
            static constexpr GLuint TexFormat        = GL_RED_INTEGER;
            static constexpr uint32_t BitsPerChannel = 8;
        };
        
        // Internal Texture Format: BPC=BitsPerComponent (8,16,32), COMPONENTS=VectorComponents (1,2,3,4)
        template<TextureFormat FORMAT, uint32_t BPC, uint32_t COMPONENTS> GLuint
        InternalTextureFormat();
        
    }
}
#endif // GLHelper_H