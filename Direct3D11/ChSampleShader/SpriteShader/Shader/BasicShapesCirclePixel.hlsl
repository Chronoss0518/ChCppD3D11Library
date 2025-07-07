
#define __SHADER__
#define _SM5_0_

#include"BasicShapesCircle.hlsli"

float4 main(VS_OUT _vs) : SV_TARGET
{
	clip(IsInCirclePosition(circleDatas,_vs.uv));
	return color;
}