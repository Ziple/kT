#ifndef __KTBLENDSTATE_HPP__
#define __KTBLENDSTATE_HPP__

#include <kT/Core/Build.hpp>
#include <kT/Core/Types.hpp>

namespace kT
{
	struct KT_API BlendModeDesc
	{
		enum ColorBlend
		{
			ColorZero = 1,//The data source is the color black (0, 0, 0, 0). No pre-blend operation.
			ColorOne = 2,//The data source is the color black (1,1,1,1). No pre-blend operation.
			ColorSrcColor = 3,//The data source is color data (RGB) from a pixel shader. No pre-blend operation.
			ColorInvSrcColor = 4,//The data source is color data (RGB) from a pixel shader. The pre-blend operation inverts the data, generating 1 - RGB.
			ColorSrcAlpha = 5,//The data source is alpha data (A) from a pixel shader. No pre-blend operation.
			ColorInvSrcAlpha = 6,//The data source is alpha data (A) from a pixel shader. The pre-blend operation inverts the data, generating 1 - A.
			ColorDestAlpha = 7,//The data source is alpha data (A) from a rendertarget. No pre-blend operation.
			ColorInvDestAlpha = 8,//The data source is alpha data (A) from a rendertarget. The pre-blend operation inverts the data, generating 1 - A.
			ColorDestColor = 9,//The data source is color data from a rendertarget. No pre-blend operation.
			ColorInvDestColor = 10,//The data source is color data from a rendertarget. The pre-blend operation inverts the data, generating 1 - RGB.
			ColorSrcAlphaSat = 11,//The data source is alpha data from a pixel shader. The pre-blend operation clamps the data to 1 or less.
			ColorBlendFactor = 14,//The data source is the blend factor set with Context::OMSetBlendState. No pre-blend operation.
			ColorInvBlendFactor = 15,//The data source is the blend factor set with Context::OMSetBlendState. The pre-blend operation inverts the blend factor, generating 1 - blend_factor.
			ColorSrc1Color = 16,//The data sources are both color data output by a pixel shader. There is no pre-blend operation. This options supports dual-source color blending.
			ColorInvSrc1Color = 17,//The data sources are both color data output by a pixel shader. The pre-blend operation inverts the data, generating 1 - RGB. This options supports dual-source color blending.
			ColorSrc1Alpha = 18,// The data sources are alpha data output by a pixel shader.There is no pre - blend operation.This options supports dual - source color blending.
			ColorInvSrc1Alpha = 19// The data sources are alpha data output by a pixel shader. The pre-blend operation inverts the data, generating 1 - A. This options supports dual-source color blending.
		};

		enum AlphaBlend
		{
			AlphaZero = 1,//The data source is the color black (0, 0, 0, 0). No pre-blend operation.
			AlphaOne = 2,//The data source is the color black (1,1,1,1). No pre-blend operation.
			AlphaSrcAlpha = 5,//The data source is alpha data (A) from a pixel shader. No pre-blend operation.
			AlphaInvSrcAlpha = 6,//The data source is alpha data (A) from a pixel shader. The pre-blend operation inverts the data, generating 1 - A.
			AlphaDestAlpha = 7,//The data source is alpha data (A) from a rendertarget. No pre-blend operation.
			AlphaInvDestAlpha = 8,//The data source is alpha data (A) from a rendertarget. The pre-blend operation inverts the data, generating 1 - A.
			AlphaSrcAlphaSat = 11,//The data source is alpha data from a pixel shader. The pre-blend operation clamps the data to 1 or less.
			AlphaBlendFactor = 14,//The data source is the blend factor set with Context::OMSetBlendState. No pre-blend operation.
			AlphaInvBlendFactor = 15,//The data source is the blend factor set with Context::OMSetBlendState. The pre-blend operation inverts the blend factor, generating 1 - blend_factor.
			AlphaSrc1Alpha = 18,// The data sources are alpha data output by a pixel shader.There is no pre - blend operation.This options supports dual - source color blending.
			AlphaInvSrc1Alpha = 19// The data sources are alpha data output by a pixel shader. The pre-blend operation inverts the data, generating 1 - A. This options supports dual-source color blending.
		};

		enum BlendOperation
		{
			Add = 1,//Add source 1 and source 2.
			Substract = 2,//Substract source 1 and source 2
			RevSubstract = 3,//Substract source 2 and source 1
			Min = 4,//Use the min of source 1 and source 2
			Max = 5// use the max of source 1 and source 2
		};

		enum ColorWriteMask
		{
			WriteRed = 1,
			WriteGreen = 2,
			WriteBlue = 4,
			WriteAlpha = 8,
			WriteAll = ( ( (WriteRed | WriteGreen) | WriteBlue) | WriteAlpha)
		};

		bool BlendEnable;
		ColorBlend SrcBlend;
		ColorBlend DestBlend;
		BlendOperation BlendOp;//defines how to combine the RGB data sources.
		AlphaBlend SrcBlendAlpha;
		AlphaBlend DestBlendAlpha;
		BlendOperation BlendOpAlpha;//defines how to combine the alpha data sources.
		Uint8 RenderTargetWriteMask;//indicate which component to write to the output (R,G,B,A)

		BlendModeDesc(
			bool blendEnable = false,
			ColorBlend srcBlend = ColorOne,
			ColorBlend dstBlend = ColorZero,
			BlendOperation colorOp = Add,
			AlphaBlend srcBlendAlpha = AlphaOne,
			AlphaBlend dstAlphaBlend = AlphaZero,
			BlendOperation alphaOp = Add,
			Uint8 writeMask = WriteAll ):
			BlendEnable( blendEnable ),
			SrcBlend( srcBlend ),
			DestBlend( dstBlend ),
			BlendOp(colorOp),
			SrcBlendAlpha(srcBlendAlpha),
			DestBlendAlpha(dstAlphaBlend),
			BlendOpAlpha(alphaOp),
			RenderTargetWriteMask(writeMask)
		{}

		static BlendModeDesc NoBlending() { return BlendModeDesc(); }

		static BlendModeDesc AlphaBlending() { return BlendModeDesc(true, ColorSrcAlpha, ColorInvSrcAlpha, Add, AlphaOne, AlphaInvSrcAlpha, Add); }

		static BlendModeDesc AdditiveBlending() { return BlendModeDesc(true, ColorOne, ColorOne, Add, AlphaOne, AlphaOne, Add); }
	};

	struct KT_API BlendStateDesc
	{
		bool AlphaToCoverageEnable;
		bool IndependentBlendEnable;
		BlendModeDesc RenderTarget[8];

		BlendStateDesc(
			bool alphaToCoverageEnable = false,
			bool independentBlendEnable = false,
			const BlendModeDesc renderTarget[8] = 0
		):
		AlphaToCoverageEnable( alphaToCoverageEnable ),
		IndependentBlendEnable( independentBlendEnable )
		{
			if ( renderTarget != 0 )
				for (size_t i = 0; i < 8; i++)
					RenderTarget[i] = renderTarget[i];
		}

		static BlendStateDesc NoBlendingState() 
		{
			BlendModeDesc mdesc = BlendModeDesc::NoBlending();
			
			BlendModeDesc renderTargets[8];
			renderTargets[0] = mdesc;

			return BlendStateDesc(false, false, renderTargets);
		}

		static BlendStateDesc AlphaBlendingState()
		{
			BlendModeDesc mdesc = BlendModeDesc::AlphaBlending();

			BlendModeDesc renderTargets[8];
			renderTargets[0] = mdesc;

			return BlendStateDesc(false, false, renderTargets);
		}

		static BlendStateDesc AdditiveBlendingState()
		{
			BlendModeDesc mdesc = BlendModeDesc::AdditiveBlending();

			BlendModeDesc renderTargets[8];
			renderTargets[0] = mdesc;

			return BlendStateDesc(false, false, renderTargets);
		}
	};
}

#endif /* __KTBLENDSTATE_HPP__ */