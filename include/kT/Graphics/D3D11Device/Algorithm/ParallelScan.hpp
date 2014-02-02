#ifndef __KTPARALLELSCAN_HPP__
#define __KTPARALLELSCAN_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>
#include <kT/Core/NonCopyable.hpp>

namespace kT
{
    class D3D11HardwareBuffer;
    class D3D11Shader;
    class D3D11Device;
    class D3D11ImmediateContext;

    class KT_API ParallelScan: public NonCopyable
    {
        public:

            ParallelScan(
                D3D11Device* dev,
                kT::Uint32 numElements
                );


            ~ParallelScan();

            void Scan(
                D3D11ImmediateContext* ctx,
                D3D11Shader* scanShader,
                D3D11Shader* incrShader,
                D3D11HardwareBuffer* inBuffer,
                D3D11HardwareBuffer* outBuffer
                );

            /**
             * \return The buffer wich contains a single uint: the total sum of the array
             */
            D3D11HardwareBuffer* GetTotalCountBuffer() {return myTotalCountBuffer;}

        protected:

            kT::Uint32 CountNecessaryTempBuffers( kT::Uint32 groupsX );

            void DoRecursion(
                D3D11ImmediateContext* ctx,
                D3D11Shader* scanShader,
                D3D11Shader* incrShader,
                kT::Uint32 groupsX,
                kT::Uint32 i
                );

            D3D11Device* myDev;
            kT::Uint32 myNumElements;
            kT::Uint32 myNumTempBuffers;
            D3D11HardwareBuffer** myTempBuffers;
            D3D11HardwareBuffer* myTotalCountBuffer;
            D3D11HardwareBuffer* myConstantBuffer;
    };

}

#endif /* __KTPARALLELSCAN_HPP__ */