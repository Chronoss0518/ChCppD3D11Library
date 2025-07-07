
#define __SHADER__
#define _SM5_0_

#include"BasicShapesPosition.hlsli"

float4 main(VS_OUT _vs) : SV_TARGET
{
	clip(IsInPosition(positions,_vs.uv));
	return color;
}