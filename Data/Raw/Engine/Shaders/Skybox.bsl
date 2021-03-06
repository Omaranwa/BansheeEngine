#include "$ENGINE$\PerCameraData.bslinc"

technique Skybox
{
	mixin PerCameraData;

	raster
	{
		cull = cw;
	};

	depth
	{
		compare = lte;
		write = false;
	};
		
	code
	{
		void vsmain(
			in float3 inPos : POSITION,
			out float4 oPosition : SV_Position,
			out float3 oDir : TEXCOORD0)
		{
			float4 pos = mul(gMatViewProj, float4(inPos.xyz + gViewOrigin, 1));
		
			// Set Z = W so that final depth is 1.0f and it renders behind everything else
			oPosition = pos.xyww;
			oDir = inPos;
		}

		TextureCube gSkyTex;
		SamplerState gSkySamp;
	
		[internal]
		cbuffer Params
		{
			float4 gClearColor;
		}
	
		float4 fsmain(
			in float4 inPos : SV_Position, 
			in float3 dir : TEXCOORD0) : SV_Target
		{
			#ifdef SOLID_COLOR
				return gClearColor;
			#else
				return gSkyTex.SampleLevel(gSkySamp, dir, 0);
			#endif
			}
	};	
};