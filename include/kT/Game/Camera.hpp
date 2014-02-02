#ifndef __KTCAMERA_HPP__
#define __KTCAMERA_HPP__

#include <kT/Core/Types.hpp>
#include <kT/Math/Vector3.hpp>
#include <kT/Math/Matrix4.hpp>

namespace kT
{
    class KT_API Camera
    {
        public:

            Camera( const kT::Vector3f32& eyePos,
                    const kT::Vector3f32& eyeTarget,
                    const kT::Vector3f32& up );

            kT::Matrix4f32 GetMatrix() const;

            void MoveForward( float dx ) { myEyePos += dx * myFront;}
            void MoveLeft( float dx ) {myEyePos += dx * myLeft;}
            void MoveUp( float dx ) {myEyePos += dx * myUp;}

            void SetEyePos( const kT::Vector3f32& eyePos ){myEyePos = eyePos;}
            void SetUp( const kT::Vector3f32& up ){myUp = up; myLeft = up.Cross(myFront).Normalize();}
            void SetFront( const kT::Vector3f32& front ){myFront = front; myLeft = myUp.Cross(front).Normalize();}
            void SetLeft( const kT::Vector3f32& left ) {myLeft = left; myUp = myFront.Cross(left).Normalize();}

            void RotateLeft( const kT::Float32 angle );
            void RotateUp( const kT::Float32 angle );

            kT::Vector3f32 GetEyePos() const {return myEyePos;}
            kT::Vector3f32 GetUp() const {return myUp;}
            kT::Vector3f32 GetFront() const {return myFront;}
            kT::Vector3f32 GetLeft() const {return myLeft;}

        protected:

            kT::Vector3f32 myEyePos;
            kT::Vector3f32 myUp;
            kT::Vector3f32 myFront;
            kT::Float32 myDistance;
            kT::Vector3f32 myLeft;
    };
}

#endif /* __KTCAMERA_HPP__ */