#ifndef	Ch_BasicShapes_h
#define Ch_BasicShapes_h

#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/5.0/BasicShapes.hlsli"

#ifndef BASIC_SHAPES_DATA_REGISTERNO
#define BASIC_SHAPES_DATA_REGISTERNO 0
#endif

#ifdef __SHADER__
cbuffer BasicShapesData : register(CHANGE_CBUFFER(BASIC_SHAPES_DATA_REGISTERNO))
#else
struct BasicShapesData
#endif
{
	row_major float4x4 spriteMat;
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
};


#ifdef __SHADER__
struct VS_OUT {
	float4 pos	: SV_POSITION;
	float2 uv	: TEXCOORD0;
};
#endif

#endif