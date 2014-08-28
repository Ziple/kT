#include <kT/Graphics/OGL3Device/OGL3Shader.hpp>
#include <kT/Graphics/OGL3Device/OGL3Check.hpp>

#include <kT/Core/File.hpp>

#include <cstring>

namespace kT
{
    KT_API OGL3Shader* OGL3Shader::LoadFromFile(
        const std::string& filename,
        ShaderType shaderType,
        ShaderProfile shaderProfile )
    {
        Uint32 read;
        Uint8* buff = File::RawContent(filename, &read);

        std::string str;
        str.resize(read+1);
        str[str.length()-1] = '\0';

        memcpy( &str[0], buff, read );

        size_t len = str.length();
        OGL3Shader* shader = new OGL3Shader(shaderType, shaderProfile, &str[0], len );
        delete[] buff;

        return shader; 
    }



    KT_API OGL3Shader::OGL3Shader(
        OGL3Shader::ShaderType type,
        OGL3Shader::ShaderProfile profile,
        const void* src,
        size_t length ):
        Base(type),
        myShaderGLID( 0 )
    {
        GLenum stype = 0;
        if( type == VertexShader )
            stype = GL_VERTEX_SHADER;
        else if( type == PixelShader )
            stype = GL_FRAGMENT_SHADER;
        else if( type == GeometryShader )
            stype = GL_GEOMETRY_SHADER; 
        else if( type == ComputeShader )
            stype = GL_COMPUTE_SHADER;

        GLchar* profileLookupTable[] =
        {
            "#version 150 core\n",
            "#version 330 core\n",
            "#version 420 core\n"
        };

		myShaderGLID = ktOGL3Check( glCreateShader(stype) );

        const GLchar* srcs[] = { profileLookupTable[ profile ], reinterpret_cast<const GLchar*>(src)};

		ktOGL3Check( glShaderSource(myShaderGLID, 2, &srcs[0], 0) );

		ktOGL3Check( glCompileShader(myShaderGLID) );
    }

    KT_API OGL3Shader::~OGL3Shader()
    {
		ktOGL3Check(glDeleteShader(myShaderGLID) );
    }

    bool KT_API OGL3Shader::CompilationPassed()
    {
        GLint val;
		ktOGL3Check( glGetShaderiv(myShaderGLID, GL_COMPILE_STATUS, &val) );
        return val == GL_TRUE;
    }

    std::string KT_API OGL3Shader::GetErrorLog()
    {
        GLint val;
		ktOGL3Check( glGetShaderiv(myShaderGLID, GL_INFO_LOG_LENGTH, &val) );


        GLchar *s = new GLchar[val+1];
		ktOGL3Check( glGetShaderInfoLog(myShaderGLID, val, 0, s) );
        s[val] = 0;

        std::string str = s;
        delete[] s;

        return str;
    }

    KT_API OGL3Program::OGL3Program( const OGL3Shader* vs, const OGL3Shader* ps ):
        myProgramID( 0 )
    {
		myProgramID = ktOGL3Check( glCreateProgram() );
		ktOGL3Check( glAttachShader(myProgramID, vs->GetHandle()) );
		ktOGL3Check( glAttachShader(myProgramID, ps->GetHandle()) );
		ktOGL3Check( glLinkProgram(myProgramID) );

        BuildUniformCache();
        BuildVertexAttribCache();
    }

    KT_API OGL3Program::~OGL3Program()
    {
		ktOGL3Check( glDeleteProgram(myProgramID) );
    }

    bool KT_API OGL3Program::LinkPassed()
    {
        GLint val;
		ktOGL3Check( glGetProgramiv(myProgramID, GL_LINK_STATUS, &val) );
        return val == GL_TRUE;
    }

    std::string KT_API OGL3Program::GetErrorLog()
    {
        GLint val;
		ktOGL3Check( glGetProgramiv(myProgramID, GL_INFO_LOG_LENGTH, &val) );

        GLchar *s = new GLchar[val+1];
		ktOGL3Check( glGetProgramInfoLog(myProgramID, val, 0, s) );
        s[val] = 0;

        std::string str = s;
        delete[] s;

        return str;
    }

    bool KT_API OGL3Program::HasUniform( const std::string& name )
    {
        return myUniformCache.find(name) != myUniformCache.end();
    }

    GLuint KT_API OGL3Program::GetUniformIndexByName( const std::string& name )
    {
        std::map<std::string, GLuint>::iterator it = myUniformCache.find(name);

        if( it != myUniformCache.end() )
            return it->second;
        return -1;
    }

    bool KT_API OGL3Program::HasVertexAttrib( const std::string& name )
    {
        return myVertexAttribCache.find(name) != myVertexAttribCache.end();
    }

    GLuint KT_API OGL3Program::GetVertexAttribIndexByName( const std::string& name )
    {
        std::map<std::string, GLuint>::iterator it = myVertexAttribCache.find(name);

        if( it != myVertexAttribCache.end() )
            return it->second;
        return -1;
    }

    void KT_API OGL3Program::BuildUniformCache()
    {
        GLint activeUniforms = 0;
		ktOGL3Check( glGetProgramiv(myProgramID, GL_ACTIVE_UNIFORMS, &activeUniforms) );

        GLint maxNameLength  = 0;
		ktOGL3Check( glGetProgramiv(myProgramID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength));
        GLchar* s = new GLchar[maxNameLength];

        for( size_t i = 0; i < (size_t)activeUniforms; i++ )
        {
            GLsizei length;
 	        GLint size;
 	        GLenum type;
			ktOGL3Check( glGetActiveUniform(myProgramID, i, maxNameLength, &length, &size, &type, s) );
            myUniformCache[ std::string(s) ] = i;
        }

        delete[] s;
    }
    void KT_API OGL3Program::BuildVertexAttribCache()
    {
        GLint activeAttributes = 0;
		ktOGL3Check( glGetProgramiv(myProgramID, GL_ACTIVE_ATTRIBUTES, &activeAttributes) );

        GLint maxNameLength  = 0;
		ktOGL3Check( glGetProgramiv(myProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxNameLength) );
        GLchar* s = new GLchar[maxNameLength];

        for( size_t i = 0; i < (size_t)activeAttributes; i++ )
        {
            GLsizei length;
 	        GLint size;
 	        GLenum type;
			ktOGL3Check( glGetActiveAttrib(myProgramID, i, maxNameLength, &length, &size, &type, s) );
            myVertexAttribCache[ std::string(s) ] = i;
        }

        delete[] s;
    }
}