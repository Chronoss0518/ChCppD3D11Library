
#define __SHADER__
#define _SM5_0_

#include"MultiplePolygonBase.hlsli"

#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawMultiplePolygon.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/Light.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/Texture/BaseTexture.hlsli"

float4 LightCol(VS_OUT _base, float4 _color);

float4 PLightCol(ChPointLight _plight, VS_OUT _base, float4 _color);

#define DebugFlgs 0

struct OutColor
{
    float4 color : SV_Target0;
    float4 highLight : SV_Target1;
	
#if DebugFlgs
	float depth : SV_DepthGreaterEqual;
#endif
};


float3 GetLightColor(float4 _baseColor, VS_OUT _inVertex, ChMaterialData _mate);

//ピクセルシェダ(PixelShader)//
//通常描画//
OutColor main(VS_OUT _in)
{
	//カメラの前方にあるかの判定//
    clip(_in.viewPos.z);
	
    FrustumCulling(_in.proPos);
	
    OutColor outColor;

#if DebugFlgs

	outColor.color = float4(1.0f, 0.0f, 0.0f, 1.0f);
	//outColor.color = _in.proPos;
	//outColor.color.z = 0.0f;
	//outColor.color.r = _in.pos.x / _in.pos.w * 2.0f;
	//outColor.color.g = _in.pos.y / _in.pos.w * 2.0f;
	//outColor.color.b = _in.pos.z / _in.pos.w * 2.0f;
	outColor.color.r = _in.proPos.x / _in.proPos.w;
	outColor.color.g = _in.proPos.y / _in.proPos.w;
	outColor.color.b = _in.proPos.z / _in.proPos.w;
	//outColor.color.r = outColor.depth;

#elif 0

	outColor.color = _in.color;

	float3 lightBloomColor = outColor.color.rgb;

	float4 baseTexCol = baseTex.Sample(baseSmp, _in.uv);

	clip(baseTexCol.a - 0.1f);

	float a = mate.dif.a * baseTexCol.a * outColor.color.a;

	outColor.color = float4(a, a, a, 1);

	//outColor.depth = outColor.color.a > 0.99f ? 0.0f : 0.99f;

#else

    outColor.color = _in.color;

    float4 baseTexCol = GetBaseTextureColorFromNo(_in.uv,_in.frameNo);
	
    outColor.highLight = outColor.color = mateDatas.datas[_in.frameNo].dif * baseTexCol * outColor.color;
	
    AlphaTest(outColor.color.a);
	
    outColor.color.rgb = GetLightColor(outColor.color, _in, mateDatas.datas[_in.frameNo]);
	
    outColor.highLight.r = max(max(outColor.highLight.r, outColor.color.r) - 1.0f, 0.0f);
    outColor.highLight.g = max(max(outColor.highLight.g, outColor.color.g) - 1.0f, 0.0f);
    outColor.highLight.b = max(max(outColor.highLight.b, outColor.color.b) - 1.0f, 0.0f);
	
    outColor.highLight.a = 1.0f;
	
#endif

    return outColor;

}

float3 GetLightColor(float4 _baseColor, VS_OUT _inVertex, ChMaterialData _mate)
{

    L_BaseColor lightCol;
    lightCol.color = _baseColor.rgb;
    lightCol.wPos = _inVertex.worldPos.xyz;
    lightCol.wfNormal = _inVertex.faceNormal;
    lightCol.specular.rgb = _mate.speCol;
    lightCol.specular.a = _mate.spePow;

    return GetLightColor(lightCol);

}
