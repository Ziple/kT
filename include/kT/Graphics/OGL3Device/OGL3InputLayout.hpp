#ifndef __KTOGL3INPUTLAYOUT_HPP__
#define __KTOGL3INPUTLAYOUT_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Graphics/GraphicsDevice/InputLayout.hpp>

namespace kT
{
    class OGL3Program;

    /**
     * \ingroup ktogl3device_module
     */
    struct OGL3InputElementDesc
    {
        Uint32 inputSlot;            ///< Buffer fournissant les données
        Uint32 index;                ///< Sous index pour l'attrib
        Uint32 size;                 ///< Nombre de composants
        Uint32 type;                 ///< Type des composants
        InputElementClass inputClass;///< Instanced or not.
        Uint32 stepRate;
        Uint32 attribIndex;          ///< Index of the vertex attribute
        Uint32 offset;
    };

    /**
     * \ingroup ktogl3device_module
     */
    class KT_API OGL3InputLayout: public InputLayout
    {
        public:

            OGL3InputLayout( OGL3Program* prog, const InputLayoutDesc& inputLayoutDesc );

            ~OGL3InputLayout();

            OGL3InputElementDesc* GetElements() const;

            Uint32 GetNumberOfElements() const;

        private:

            OGL3InputElementDesc* myElements;
            Uint32 myNumberOfElements;
    };
}

#endif /* __KTOGL3INPUTLAYOUT_HPP__ */
