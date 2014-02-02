#include <kT/Window/Base/WindowBase.hpp>

namespace kT
{
    WindowBase::WindowBase( WindowHandle windowHandle ):
     myWindowHandle( windowHandle ),
     myKeyRepeatEnabled( false )
    {
        Listen( this );
    }

    bool KT_API WindowBase::GetEvent( GUIEvent& fillMe )
    {
        if ( !myEvents.empty() )
        {
            fillMe = myEvents.front();
            myEvents.pop_front();
            return true;
        }

        return false;
    }

    void WindowBase::OnEvent( const EventEmitter<GUIEvent>* emitter, const GUIEvent* event )
    {
        if ( emitter == this )
            myEvents.push_back( *reinterpret_cast<const GUIEvent*>( event ) );
    }

    Uint16 WindowBase::UTF8toUTF16(const Uint8* Source)
    {
        // http://www.unicode.org/Public/PROGRAMS/CVTUTF/ConvertUTF.h
        // http://www.unicode.org/Public/PROGRAMS/CVTUTF/ConvertUTF.c

        Uint8 Byte = *Source;

        int    NbBytes = 0;
        Uint32 Offset  = 0;
        if      (Byte < 0xC0) {NbBytes = 0; Offset = 0x00000000;}
        else if (Byte < 0xE0) {NbBytes = 1; Offset = 0x00003080;}
        else if (Byte < 0xF0) {NbBytes = 2; Offset = 0x000E2080;}
        else if (Byte < 0xF8) {NbBytes = 3; Offset = 0x03C82080;}
        else if (Byte < 0xFC) {NbBytes = 4; Offset = 0xFA082080;}
        else                  {NbBytes = 5; Offset = 0x82082080;}

        Uint16 Result = 0;
        for (int i = 0; i < NbBytes; ++i)
        {
            Result = static_cast<Uint16>(Result + *Source++);
            Result <<= 6;
        }

        return static_cast<Uint16>(Result + *Source - Offset);
    }
}