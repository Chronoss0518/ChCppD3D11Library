
#define __SHADER__
#define _SM5_0_

#include"SpriteBase.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawSprite.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/Highlight.hlsli"

//�s�N�Z���V�F�_(PixelShader)//
//���p//
float4 main(VS_OUT _in) : SV_Target0
{
    float4 res =  HighLightColor(_in.uv) * baseColor * _in.color;
    res.a = 1.0f;
    return res;

}