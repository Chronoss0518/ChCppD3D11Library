#ifndef	Ch_TextureBase_h
#define Ch_TextureBase_h


struct VS_OUT {
	float4 pos	: SV_POSITION;
	float4 color : COLOR0;
	float2 uv	: TEXCOORD0;
};

#endif