
#define __SHADER__
#define _SM5_0_

#include"BasicShapes.hlsli"

VS_OUT main(
	float4 _pos : POSITION0,
	float2 _uv : TEXCOORD0
)
{
	VS_OUT res;
	res.pos = mul(_pos, spriteMat);
	res.uv = _uv;
	return res;
}