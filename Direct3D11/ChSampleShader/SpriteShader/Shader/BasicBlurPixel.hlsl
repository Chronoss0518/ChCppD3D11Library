
#define __SHADER__
#define _SM5_0_

#include"SpriteBase.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/5.0/DrawSprite.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/5.0/Blur.hlsli"

//ピクセルシェダ(PixelShader)//
//共用//
float4 main(VS_OUT _in) : SV_Target0
{
    float4 res = _in.color;
    res *= Blur(_in.uv) * baseColor;

    AlphaTest(res.a);
    
    return res;

}