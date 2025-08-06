
#define __SHADER__
#define _SM5_0_

#include"PolygonBase2.hlsli"

#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawPolygon.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/Light.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/Texture/BaseTexture2.hlsli"

float4 LightCol(VS_OUT _base, float4 _color);

float4 PLightCol(ChPointLight _plight, VS_OUT _base, float4 _color);

#define DebugFlgs 0

struct OutColor
{
	float4 color :SV_Target0;
    float4 highLight : SV_Target1;
	
#if DebugFlgs
	float depth : SV_DepthGreaterEqual;
#endif
};


float3 GetLightColor(float4 _baseColor, VS_OUT _inVertex, ChP_Material _mate);

//ピクセルシェダ(PixelShader)//
//通常描画//
OutColor main(VS_OUT _in)
{
	//カメラの前方にあるかの判定//
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

    float4 baseTexCol = GetBaseTextureColorFromNo(_in.uv, _in.instanceID);
	
    outColor.highLight = outColor.color = mate.dif * baseTexCol * outColor.color;
	
    AlphaTest(outColor.color.a);
	
    outColor.color.rgb = GetLightColor(outColor.color, _in, mate);
	
    outColor.highLight.r = max(outColor.highLight.r - 1.0f, 0.0f);
    outColor.highLight.g = max(outColor.highLight.g - 1.0f, 0.0f);
    outColor.highLight.b = max(outColor.highLight.b - 1.0f, 0.0f);
	
    outColor.highLight.a = 1.0f;
	
#endif

	return outColor;

}


float3 GetLightColor(float4 _baseColor, VS_OUT _inVertex, ChP_Material _mate)
{

	L_BaseColor lightCol;
	lightCol.color = _baseColor.rgb;
	lightCol.wPos = _inVertex.worldPos.xyz;
	lightCol.wfNormal = _inVertex.faceNormal;
	lightCol.specular.rgb = _mate.speCol;
	lightCol.specular.a = _mate.spePow;

	return GetDirectionalLightColor(lightCol);

}

/*
float4 LightCol(VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	if(!light.LightUseFlg)return Col;

	float Dot;

	float3 BNormal = normalize(_Base.FaceNormal);
	float3 LNormal = normalize(-light.Dir);

	Dot = dot(BNormal, LNormal);

	Dot = (Dot + 1) * 0.5f;
	//Dot = saturate(Dot);

	float TmpPow = LightPowMap.Sample(LightSmp, float2(Dot, 0.0f)).r;
	
	//float TmpPow = Dot;

	Col.rgb *= LamLightCol(light.Dif, TmpPow) + AmbLightCol();

	Col.rgb += SpeLightCol(-light.Dir, _Base.UsePos.xyz, _Base.FaceNormal,SpeCol);

	//Col.rgb += AmbLightCol();

	return Col;
}

float4 PLightCol(ChPointLight plight, VS_OUT _Base, float4 _Color)
{

	float4 Col = _Color;

	if (!light.LightUseFlg)return Col;
	if (!plight.Flg)return Col;

	bool TmpFlg = false;

	float3 TmpVec = _Base.UsePos.xyz;

	TmpVec = TmpVec - plight.Pos;

	float Len;

	Len = length(TmpVec);

	TmpFlg = Len > plight.Len ? true : false;

	if (TmpFlg)return Col;

	TmpVec = normalize(TmpVec);

	float Par = Len / plight.Len;

	float Dot;

	Dot = dot(_Base.Normal, -TmpVec);

	Dot = saturate(Dot);

	Col.rgb *= LamLightCol(plight.Dif.rgb, Dot) * Par;

	Col.rgb += SpeLightCol(TmpVec, _Base.UsePos.xyz, _Base.Normal,SpeCol) * Par;

	return Col;
}

*/