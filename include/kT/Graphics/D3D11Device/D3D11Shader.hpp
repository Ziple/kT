#ifndef __KTD3D11SHADER_HPP__
#define __KTD3D11SHADER_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/GraphicsDevice/Shader.hpp>
#include "D3D11DeviceTypes.hpp"

#include <string>
#include <map>
#include <D3D11.h>

namespace kT
{
    class KT_API D3D11Shader: public kT::Shader< kTD3D11DeviceTemplateListLineTypes >,
                              public NonCopyable
    {
        public:

            typedef kT::Shader< kTD3D11DeviceTemplateListLineTypes > Base;

            /**
             * \brief Loads the shader from the specified file.
             */
            static D3D11Shader* LoadFromFile( ID3D11Device* d3dDevice,
                         const std::string& filename,
                         ShaderType shaderType,
                         ShaderProfile shaderProfile,
                         const char* entryPoint,
                         const std::map<std::string,std::string>& macros = std::map<std::string,std::string>() );

			/**
			 * \brief Loads a precompiled shader from file.
			 */
			static D3D11Shader* LoadBinaryFromFile( ID3D11Device* d3dDevice,
						const std::string& filename,
						ShaderType shaderType );

            /**
             * RAII: Try to compile the shader. If fail, launch an exception with the compilation status.
             */
            D3D11Shader( ID3D11Device* d3dDevice,
                         ShaderType shaderType,
                         ShaderProfile shaderProfile,
                         void* shaderSource,
                         size_t sourceSize,
                         const char* entryPoint,
                         const std::map<std::string,std::string>& macros = std::map<std::string,std::string>() );

			D3D11Shader( ID3D11Device* d3dDevice,
                         ShaderType shaderType,
                         void* shaderBytecode,
                         size_t bytecodeSize );

            ~D3D11Shader();

            void* GetHandle() const {return myShaderHandle;}

            ID3D10Blob* GetShaderByteCode() const {return myShaderByteCode;}

#if defined(KT_DEBUG)
            void SetName( const std::string& name );
#endif

        protected:

            void Create( ID3D11Device* dev );

            void* myShaderHandle;
            ID3D10Blob* myShaderByteCode;
    };
}


#endif /* __KTD3D11SHADER_HPP__ */