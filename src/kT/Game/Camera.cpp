#include <kT/Game/Camera.hpp>
#include <kT/Math/Quaternion.hpp>

namespace kT
{
    KT_API Camera::Camera( const kT::Vector3f32& eyePos,
                    const kT::Vector3f32& eyeTarget,
                    const kT::Vector3f32& up )
    {
        myEyePos = eyePos;
        myFront = (eyeTarget - eyePos);
        myDistance = myFront.Length();
        myUp = up.Normalized();
        myLeft = up.Cross(myFront).Normalize();
        myFront.Normalize();
    }

    void KT_API Camera::RotateLeft( const kT::Float32 angle )
    {
        kT::Quaternionf32 quat;
        quat.BuildFromAxisAndAngle( myUp, angle );
        kT::Matrix4f32 quatMat = quat.GetMatrix4();
        myLeft = quatMat * myLeft;
        myFront = quatMat * myFront;
    }

    void KT_API Camera::RotateUp( const kT::Float32 angle )
    {
        kT::Quaternionf32 quat;
        quat.BuildFromAxisAndAngle( myLeft, angle );
        kT::Matrix4f32 quatMat = quat.GetMatrix4();
        myUp = quatMat * myUp;
        myFront = quatMat * myFront;
    }

    kT::Matrix4f32 KT_API Camera::GetMatrix() const
    {
        return kT::Matrix4f32().BuildLookAtRH(myEyePos, myEyePos + myDistance * myFront, myUp);
    }
}