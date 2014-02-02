#ifndef __KTRASTERIZERSTATE_HPP__
#define __KTRASTERIZERSTATE_HPP__

#include <kT/Core/Types.hpp>

namespace kT
{
	struct KT_API RasterizerDesc {

		enum FillMode{
			FillWireFrame = 2,
			FillSolid = 3
		};

		enum CullMode{
			CullNone = 1,
			CullFront = 2,
			CullBack = 3
		};

		FillMode fillMode;
		CullMode cullMode;
		bool            frontCounterClockwise;
		Int32             depthBias;
		Float32           depthBiasClamp;
		Float32           slopeScaledDepthBias;
		bool            depthClipEnable;
		bool            scissorEnable;
		bool            multisampleEnable;
		bool            antialiasedLineEnable;

		RasterizerDesc(
			FillMode fillMode_ = FillSolid,
			CullMode cullMode_ = CullBack,
			bool frontCounterClockwise_ = false,
			Int32 depthBias_ = 0,
			Float32 slopeScaledDepthBias_ = 0.0f,
			bool depthClipEnable_ = true,
			bool scissorEnable_ = false,
			bool multisampleEnable_ = false,
			bool antialiasedLineEnable_ = false )
		{
			fillMode = fillMode_;
			cullMode = cullMode_;
			frontCounterClockwise = frontCounterClockwise_;
			depthBias = depthBias_;
			slopeScaledDepthBias = slopeScaledDepthBias_;
			depthClipEnable = depthClipEnable_;
			scissorEnable = scissorEnable_;
			multisampleEnable = multisampleEnable_;
			antialiasedLineEnable = antialiasedLineEnable_;
		}

	};
}

#endif /* __KTRASTERIZERSTATE_HPP__ */
