#include <kT/Graphics/OGL3Device/OGL3Check.hpp>
#include <kT/Graphics/OGL3Device/OGL.hpp>

#include <iostream>
#include <string>

namespace kT
{
    void KT_API _OGL3CheckError( const Int8* fonction, const Int8* file, Uint32 Line )
    {
        GLenum errorCode = glGetError();

        if ( errorCode != GL_NO_ERROR )
        {
            std::string Error = "unknown error";
            std::string Desc  = "no description";
            std::string File(file);

            // Decode the error code
            switch (errorCode)
            {
                case GL_INVALID_ENUM :
                {
                    Error = "GL_INVALID_ENUM";
                    Desc  = "an unacceptable value has been specified for an enumerated argument";
                    break;
                }

                case GL_INVALID_VALUE :
                {
                    Error = "GL_INVALID_VALUE";
                    Desc  = "a numeric argument is out of range";
                    break;
                }

                case GL_INVALID_OPERATION :
                {
                    Error = "GL_INVALID_OPERATION";
                    Desc  = "the specified operation is not allowed in the current state";
                    break;
                }

                case GL_STACK_OVERFLOW :
                {
                    Error = "GL_STACK_OVERFLOW";
                    Desc  = "this command would cause a stack overflow";
                    break;
                }

                case GL_STACK_UNDERFLOW :
                {
                    Error = "GL_STACK_UNDERFLOW";
                    Desc  = "this command would cause a stack underflow";
                    break;
                }

                case GL_OUT_OF_MEMORY :
                {
                    Error = "GL_OUT_OF_MEMORY";
                    Desc  = "there is not enough memory left to execute the command";
                    break;
                }
            }

            // Log the error
            std::cerr<<"An internal OpenGL call caused by "<<fonction<<" failed in "<<File.substr(File.find_last_of("\\/") + 1).c_str()
                <<" (line "<<Line<<" ) : "<<Error.c_str()<<" , "<<Desc.c_str()<<std::endl;
        }
    }
}
