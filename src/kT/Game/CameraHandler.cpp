#include <kT/Game/CameraHandler.hpp>

#include <kT/Window/Keyboard.hpp>

namespace kT
{
    void KT_API CameraHandler::Update( float dt )
    {
        if( Keyboard::IsKeyPressed( kT::Keyboard::O ) )
            myTrackedCam->MoveForward( dt * 100.f );
        if( Keyboard::IsKeyPressed( kT::Keyboard::L ) )
            myTrackedCam->MoveForward( dt * -100.f );
        if( Keyboard::IsKeyPressed( kT::Keyboard::K ) )
            myTrackedCam->MoveLeft( dt * 100.f );
        if( Keyboard::IsKeyPressed( kT::Keyboard::M ) )
            myTrackedCam->MoveLeft( dt * -100.f );
        if( Keyboard::IsKeyPressed( kT::Keyboard::Up ) )
            myTrackedCam->RotateUp( dt * 10.f );
        if( Keyboard::IsKeyPressed( kT::Keyboard::Down ) )
            myTrackedCam->RotateUp( dt * -10.f );
        if( Keyboard::IsKeyPressed( kT::Keyboard::Left ) )
            myTrackedCam->RotateLeft( dt * -10.f );
        if( Keyboard::IsKeyPressed( kT::Keyboard::Right ) )
            myTrackedCam->RotateLeft( dt * 10.f );
    }
}