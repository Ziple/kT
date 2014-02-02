#ifndef __KTCAMERAHANDLER_HPP__
#define __KTCAMERAHANDLER_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Event.hpp>
#include <kT/Window.hpp>
#include <kT/Game/Camera.hpp>

namespace kT
{
    class KT_API CameraHandler
    {
        public:

            CameraHandler( kT::Camera* cam ):
             myTrackedCam( cam )
            {
            }

            void Update( float dt );

        protected:

            kT::Camera* myTrackedCam;
    };
}

#endif /* __KTCAMERAHANDLER_HPP__ */