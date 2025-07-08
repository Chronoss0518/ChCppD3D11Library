
#define __SHADER__
#define _SM5_0_

#include"SpriteBase.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/5.0/CircleCulling.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/5.0/DrawSprite.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/5.0/Texture/BaseTexture.hlsli"

//ピクセルシェダ(PixelShader)//
//共用//
float4 main(VS_OUT _in) : SV_Target0
{
	CircleCullingTest(_in.uv);

	float4 res = _in.color;
    res *= GetBaseTextureColor(_in.uv);

	//Out = BaseColor;

	AlphaTest(res.a);

	//float4 BackCol = BackBuffers.Sample(BackBufferSmp, In.Pos.xy);

	//Out = Out.a == 1.0f ? Out : float4(float3(Out.rgb * Out.a).rgb + float3(BackCol.rgb * (1.0f - Out.a)).rgb, 1);
	//

	return res;

}