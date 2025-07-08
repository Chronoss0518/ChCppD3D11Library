
#define __SHADER__
#define _SM5_0_

#include"SpriteBase.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawSprite.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/Texture/BaseTexture.hlsli"

//ピクセルシェダ(PixelShader)//
//共用//
float4 main(VS_OUT _in) : SV_Target0
{
	float4 res = _in.color;
	res *= GetBaseTextureColor(_in.uv);
    res *= baseColor;
	//Out = BaseColor;
    AlphaTest(res.a);
	
	//float4 BackCol = BackBuffers.Sample(BackBufferSmp, In.Pos.xy);

	//Out = Out.a == 1.0f ? Out : float4(float3(Out.rgb * Out.a).rgb + float3(BackCol.rgb * (1.0f - Out.a)).rgb, 1);
	//

	return res;

}