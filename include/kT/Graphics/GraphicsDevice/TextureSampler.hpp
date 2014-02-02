#ifndef __KTTEXTURESAMPLER_HPP__
#define __KTTEXTURESAMPLER_HPP__

#include <kT/Core/Types.hpp>
#include <kT/Math/Vector4.hpp>
#include <cstring>

namespace kT
{
	struct KT_API TextureSamplerDesc
	{
		enum SamplingFilter
		{
			FilterMinMagMipPoint                            = 0,
			FilterMinMagPointMipLinear                     = 0x1,
			FilterMinPointMagLinearMipPoint               = 0x4,
			FilterMinPointMagMipLinear                     = 0x5,
			FilterMinLinearMagMipPoint                     = 0x10,
			FilterMinLinearMagPointMipLinear              = 0x11,
			FilterMinMagLinearMipPoint                     = 0x14,
			FilterMinMagMipLinear                           = 0x15,
			FilterAnisotropic                                  = 0x55,
			FilterComparisonMinMagMipPoint                 = 0x80,
			FilterComparisonMinMagPointMipLinear          = 0x81,
			FilterComparisonMinPointMagLinearMipPoint    = 0x84,
			FilterComparisonMinPointMagMipLinear          = 0x85,
			FilterComparisonMinLinearMagMipPoint          = 0x90,
			FilterComparisonMinLinearMagPointMipLinear   = 0x91,
			FilterComparisonMinMagLinearMipPoint          = 0x94,
			FilterComparisonMinMagMipLinear                = 0x95,
			FilterComparisonAnisotropic                       = 0xd5,
			FilterText1Bit
		};

		enum TextureAddressMode
		{
			TextureAddressWrap          = 1,
			TextureAddressMirror        = 2,
			TextureAddressClamp         = 3,
			TextureAddressBorder        = 4,
			TextureAddressMirrorOnce   = 5 
		};

		enum ComparisonFonction
		{
			ComparisonNever           = 1,
			ComparisonLess            = 2,
			ComparisonEqual           = 3,
			ComparisonLessEqual      = 4,
			ComparisonGreater         = 5,
			ComparisonNotEqual       = 6,
			ComparisonGreaterEqual   = 7,
			ComparisonAlways          = 8 
		};

		SamplingFilter               Filter;
		TextureAddressMode AddressU;
		TextureAddressMode AddressV;
		TextureAddressMode AddressW;
		float                      MipLODBias;
		Uint32                     MaxAnisotropy;
		ComparisonFonction         ComparisonFunc;
		kT::Vector4f32             BorderColor;
		float                      MinLOD;
		float                      MaxLOD;

		TextureSamplerDesc(
			kT::TextureSamplerDesc::SamplingFilter Filter_ = FilterMinMagMipLinear,
			kT::TextureSamplerDesc::TextureAddressMode AddressU_ = TextureAddressClamp,
			TextureAddressMode AddressV_ = TextureAddressClamp,
			TextureAddressMode AddressW_ = TextureAddressClamp,
			float MipLODBias_ = 0.f,
			Uint32 MaxAnisotropy_ = 16,
			ComparisonFonction ComparisonFunc_ = kT::TextureSamplerDesc::ComparisonNever,
			const kT::Vector4f32& BorderColor_ = kT::Vector4f32(0.f,0.f,0.f,0.f),
			float MinLOD_ = 0.f,
			float MaxLOD_ = 3.402823466e+38F
		):
		 Filter(Filter_),
		 AddressU(AddressU_),
		 AddressV(AddressV_),
		 AddressW(AddressW_),
		 MipLODBias(MipLODBias_),
		 MaxAnisotropy(MaxAnisotropy_),
		 ComparisonFunc( ComparisonFunc_ ),
		 MinLOD( MinLOD_ ),
		 MaxLOD( MaxLOD_ ),
		 BorderColor( BorderColor_)
		{}
	};
}

#endif /* __KTTEXTURESAMPLER_HPP__ */