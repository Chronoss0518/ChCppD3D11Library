
#define __SHADER__
#define _SM5_0_

#include"SpriteBase.hlsli"
#include"../../../../ShaderHeaderFiles/HLSL/5.0/DrawSprite.hlsli"
#include"../../../../ShaderHeaderFiles/HLSL/5.0/Highlight.hlsli"

//ピクセルシェダ(PixelShader)//
//共用//
float4 main(VS_OUT _in) : SV_Target0
{
    float4 res =  HighLightColor(_in.uv) * baseColor * _in.color;
    res.a = 1.0f;
    return res;

}