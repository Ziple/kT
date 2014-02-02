/**
 * \file Graphics/GraphicsDevice/GraphicsContext.hpp
 * \author Damien Hilloulin (ziple)
 * \date 28/02/2009
 * \brief Contains the definition of the kT::GraphicsContext interface.
 */
#ifndef __KTSHADER_HPP__
#define __KTSHADER_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include "ImplementationForwardDeclarations.hpp"

namespace kT
{
    /**
     * \ingroup ktgfxrenderer_module
     * \brief Defines the common interface for shaders across all apis.
     *
     * A shader is a program which can be run on the GPU to modify
     * how the geometry is processed and rendered on the screen.
     * - Vertex shaders performs on vertices at the beginning of the rendering pipeline.
     * - Geometry shaders act on primitives (triangles, lines points) and can modify
     * the primitive stream by adding, removing primitives
     * - Pixel shaders work on fragments wich will be displayed to screen
     * - Compute shaders are not integrated in the rendering pipeline and are more general
     */
	kTGraphicsDeviceTemplateListDef
    class KT_API Shader
    {
        public:

            enum ShaderType
            {
                VertexShader,
                PixelShader,
                GeometryShader,
                ComputeShader
            };

            enum ShaderProfile
            {
                Profile4,
                Profile4_1,
                Profile5
            };

            Shader( ShaderType shaderType ):
             myShaderType( shaderType )
            {}

            ShaderType GetShaderType() const {return myShaderType;}

        protected:

            ShaderType myShaderType;
    };
}

#endif /* __KTSHADER_HPP__ */
