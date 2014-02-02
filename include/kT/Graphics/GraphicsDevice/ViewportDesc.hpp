#ifndef __KTVIEWPORTDESC_HPP__
#define __KTVIEWPORTDESC_HPP__

namespace kT
{
    struct KT_API ViewportDesc
    {
        float TopLeftX;
        float TopLeftY;
        float Width;
        float Height;
        float MinDepth;
        float MaxDepth;

        ViewportDesc(
            float topLeftX = 0.0f,
            float topLeftY = 0.0f,
            float width = 0.0f,
            float height = 0.0f,
            float minDepth = 0.0f,
            float maxDepth = 1.0f):
         TopLeftX( topLeftX ),
         TopLeftY( topLeftY ),
         Width( width ),
         Height( height ),
         MinDepth( minDepth ),
         MaxDepth( maxDepth )
        {}
    };
}

#endif /* __KTVIEWPORTDESC_HPP__ */