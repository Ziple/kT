#include <kT/Graphics/D3D11Device/D3D11Shader.hpp>
#include <kT/Core/Exceptions.hpp>
#include <kT/Core/File.hpp>

#include <D3Dcompiler.h>
#include <D3Dcommon.h>

#include <string>

namespace kT
{
    KT_API D3D11Shader* D3D11Shader::LoadFromFile( ID3D11Device* d3dDevice,
                         const std::string& filename,
                         ShaderType shaderType,
                         ShaderProfile shaderProfile,
                         const char* entryPoint,
                         const std::map<std::string,std::string>& macros )
    {
        Uint32 read;
        Uint8* buff = File::RawContent(filename, &read);
        D3D11Shader* shader = new D3D11Shader(d3dDevice, shaderType, shaderProfile, buff, read, entryPoint, macros );
        delete[] buff;

#if defined(KT_DEBUG)
        shader->SetName( filename );
#endif
        return shader; 
    }

	KT_API D3D11Shader* D3D11Shader::LoadBinaryFromFile( ID3D11Device* d3dDevice,
						const std::string& filename,
						ShaderType shaderType )
	{
		Uint32 read;
        Uint8* buff = File::RawContent(filename, &read);
        D3D11Shader* shader = new D3D11Shader(d3dDevice, shaderType, buff, read );
        delete[] buff;
#if defined(KT_DEBUG)
        shader->SetName( filename );
#endif
        return shader;
	}

    KT_API D3D11Shader::D3D11Shader(
        ID3D11Device* d3dDevice,
        ShaderType shaderType,
        ShaderProfile shaderProfile,
        void* shaderSource,
        size_t sourceSize,
        const char* entryPoint,
        const std::map<std::string,std::string>& macros ):
     kT::D3D11Shader::Base( shaderType )
    {
        std::string shaderProfileStr;
        if( shaderType == VertexShader )
            shaderProfileStr += "vs_";
        else if( shaderType == PixelShader )
            shaderProfileStr += "ps_";
        else if( shaderType == GeometryShader )
            shaderProfileStr += "gs_";
        else if( shaderType == ComputeShader )
            shaderProfileStr += "cs_";

        if( shaderProfile == Profile4 )
            shaderProfileStr += "4_0";
        else if( shaderProfile == Profile4_1 )
            shaderProfileStr += "4_1";
        else if( shaderProfile == Profile5 )
            shaderProfileStr += "5_0";
		else
        {
			if( shaderType == ComputeShader )
                kTLaunchException( kT::Exception, "Compute shaders unsupported" );
            else
                shaderProfileStr += "3_0";
        }

        D3D10_SHADER_MACRO* dmacros = new D3D10_SHADER_MACRO[ macros.size() + 1 ];
        dmacros[ macros.size() ].Name = 0;
        dmacros[ macros.size() ].Definition = 0;

        size_t k = 0;
        for( std::map< std::string, std::string >::const_iterator it = macros.begin();
             it != macros.end();
             it++ )
        {
            dmacros[ k ].Name = it->first.c_str();
            dmacros[ k ].Definition = it->second.c_str();
            k++;
        }

        ID3D10Blob* errors = 0;
        HRESULT hr = D3DCompile( shaderSource,
                    sourceSize,
                    NULL,
                    dmacros,
                    NULL,
                    entryPoint,
                    shaderProfileStr.c_str(),
                    D3D10_SHADER_ENABLE_STRICTNESS,
                    0,
                    &myShaderByteCode,
                    &errors );

        delete[] dmacros;

        if( FAILED(hr) )
        {
            std::string errorString =  std::string("Shader compilation failed: ") + reinterpret_cast<char*>(errors->GetBufferPointer());
            errors->Release();
            kTLaunchException( kT::Exception, errorString );
        }

        Create( d3dDevice );

        if( errors )
            errors->Release();
    }

	KT_API D3D11Shader::D3D11Shader(
		ID3D11Device* d3dDevice,
        ShaderType shaderType,
        void* shaderBytecode,
        size_t bytecodeSize ):
	 kT::D3D11Shader::Base( shaderType )
	{
		HRESULT hr = D3DCreateBlob( bytecodeSize, &myShaderByteCode );
		memcpy( myShaderByteCode->GetBufferPointer(), shaderBytecode, bytecodeSize );

        Create( d3dDevice );
	}

    KT_API D3D11Shader::~D3D11Shader()
    {
		myShaderByteCode->Release();
        if( myShaderType == VertexShader )
            reinterpret_cast<ID3D11VertexShader*>(myShaderHandle)->Release();
        else if( myShaderType == PixelShader )
            reinterpret_cast<ID3D11PixelShader*>(myShaderHandle)->Release();
        else if( myShaderType == GeometryShader )
            reinterpret_cast<ID3D11GeometryShader*>(myShaderHandle)->Release();
        else if( myShaderType == ComputeShader )
            reinterpret_cast<ID3D11ComputeShader*>(myShaderHandle)->Release();
    }

    void D3D11Shader::Create( ID3D11Device* d3dDevice )
    {
        HRESULT hr;
        if( myShaderType == VertexShader )
            hr = d3dDevice->CreateVertexShader(
                                        myShaderByteCode->GetBufferPointer(),
                                        myShaderByteCode->GetBufferSize(),
                                        NULL,
                                        reinterpret_cast<ID3D11VertexShader**>(&myShaderHandle) );
        else if( myShaderType == PixelShader )
            hr = d3dDevice->CreatePixelShader(
                                        myShaderByteCode->GetBufferPointer(),
                                        myShaderByteCode->GetBufferSize(),
                                        NULL,
                                        reinterpret_cast<ID3D11PixelShader**>(&myShaderHandle) );
        else if( myShaderType == GeometryShader )
            hr = d3dDevice->CreateGeometryShader(
                                        myShaderByteCode->GetBufferPointer(),
                                        myShaderByteCode->GetBufferSize(),
                                        NULL,
                                        reinterpret_cast<ID3D11GeometryShader**>(&myShaderHandle) );
        else if( myShaderType == ComputeShader )
            hr = d3dDevice->CreateComputeShader(
                                        myShaderByteCode->GetBufferPointer(),
                                        myShaderByteCode->GetBufferSize(),
                                        NULL,
                                        reinterpret_cast<ID3D11ComputeShader**>(&myShaderHandle) );

        if( FAILED(hr) )
            kTLaunchException( kT::Exception, "Unable to create the shader" );
    }

#if defined(KT_DEBUG)
    void KT_API D3D11Shader::SetName( const std::string& name )
    {
        reinterpret_cast<ID3D11DeviceChild*>(myShaderHandle)->SetPrivateData( WKPDID_D3DDebugObjectName, name.length(), name.c_str() );
    }
#endif
}