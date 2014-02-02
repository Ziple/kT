#ifndef __KTOGL3SHADER_HPP__
#define __KTOGL3SHADER_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/NonCopyable.hpp>
#include <kT/Graphics/GraphicsDevice/Shader.hpp>
#include "OGL3DeviceTypes.hpp"

#include <GL/glew.h>

#include <string>
#include <map>

namespace kT
{

    class KT_API OGL3Shader: public kT::Shader< kTOGL3DeviceTemplateListLineTypes >,
        public NonCopyable
    {
    public:

        typedef kT::Shader< kTOGL3DeviceTemplateListLineTypes > Base;

        /**
             * \brief Loads the shader from the specified file.
             */
            static OGL3Shader* LoadFromFile(
                         const std::string& filename,
                         ShaderType shaderType,
                         ShaderProfile shaderProfile );

            /**
             * RAII: Try to compile the shader. If fail, launch an exception with the compilation status.
             */
            OGL3Shader( ShaderType shaderType,
                         ShaderProfile shaderProfile,
                         void* shaderSource,
                         size_t sourceSize );

        ~OGL3Shader();

        GLuint GetHandle() const { return myShaderGLID; }

        bool CompilationPassed();

        std::string GetErrorLog();

    protected:

        GLuint myShaderGLID;
    };

    class KT_API OGL3Program
    {
    public:

        OGL3Program( const OGL3Shader* vs, const OGL3Shader* ps );

        ~OGL3Program();

        GLuint GetProgramID() const { return myProgramID; }

        bool LinkPassed();

        std::string GetErrorLog();

        bool HasUniform( const std::string& name );

        GLuint GetUniformIndexByName( const std::string& name );

        bool HasVertexAttrib( const std::string& name );

        GLuint GetVertexAttribIndexByName( const std::string& name );

    protected:

        void BuildUniformCache();
        void BuildVertexAttribCache();

        std::map<std::string, GLuint> myUniformCache;
        std::map<std::string, GLuint> myVertexAttribCache;

        GLuint myProgramID;
    };

}

#endif // __KTOGL3SHADER_HPP__