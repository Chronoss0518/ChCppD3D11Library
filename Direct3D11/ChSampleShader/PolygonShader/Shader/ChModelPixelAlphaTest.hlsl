#define __SHADER__
#define _SM5_0_

#include"PolygonBase.hlsli"

#include"../../../../ShaderHeaderFiles/HLSL/5.0/DrawPolygon.hlsli"
#include"../../../../ShaderHeaderFiles/HLSL/5.0/Light.hlsli"
#include"../../../../ShaderHeaderFiles/HLSL/5.0/Texture/BaseTexture.hlsli"

float4 LightCol(VS_OUT _Base, float4 _Color);

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color);

struct RenderDatas
{
    float4 Main : SV_Target0;
    float4 Temperature : SV_Target1;
    float4 NightVision : SV_Target2;
};


//ピクセルシェダ(PixelShader)//
//通常描画//
float4 main(VS_OUT _in) : SV_Target0
{
	//カメラの前方にあるかの判定//

    float x = _in.proPos.x / _in.proPos.w;
    float y = _in.proPos.y / _in.proPos.w;
    float z = _in.proPos.z / _in.proPos.w;
	//float X = In.Pos.x;
	//float Y = In.Pos.y;
	//float Z = In.Pos.z;

    clip(x >= -1.0f && x <= 1.0f ? 1.0f : -1.0f);
    clip(y >= -1.0f && y <= 1.0f ? 1.0f : -1.0f);
    clip(z >= 0.0f && z <= 1.0f ? 1.0f : -1.0f);

	//RenderDatas RDColor;

    float4 color = _in.color;

    color = mate.dif * GetBaseTextureColor(_in.uv) * color;

		//Color = Dif;
		//Color = ModelTex.Sample(ModelSmp, In.UV);

    clip(color.a > 0.999f ? -1 : 1);

		//Color = LightCol(In, Color);

    L_BaseColor lightCol;
    lightCol.color = color.rgb;
    lightCol.wPos = _in.usePos.xyz;
    lightCol.wfNormal = _in.normal;
    lightCol.specular = speCol;

    color.rgb = GetDirectionalLightColor(lightCol);

		//Color.rgb = BackBuffers.Sample(BackBufferSmp, In.Pos.xy).rgb * (1.0f - Color.a)
		//	+ Color.rgb * Color.a;

		//Color.a = 1.0f;

		//for (int i = 0; i < 10; i++)
		//{
		//	if (!LightUseFlg)break;

		//	Color = PLightCol(pLight[i], In , Color);

		//}

		//float4 Temperature = float4(0.0f, 0.0f, 0.0f, 0.0f);
		//
		//RDColor.Main = Color;
		//RDColor.Temperature = Temperature;

		//float4 NightVision = float4(0.5f, 0.5f, 1.0f, 1.0f) * (length(Color) * 1.5f);

		//NightVision.a = 1.0f;

		//RDColor.NightVision = NightVision;


    return color;

}


float4 LightCol(VS_OUT _Base, float4 _color)
{

    float4 col = _color;

    if (!light.lightUseFlg)
        return col;

    float Dot;

    float3 BNormal = normalize(_Base.faceNormal);
    float3 LNormal = normalize(-light.dir);

    Dot = dot(BNormal, LNormal);

    Dot = (Dot + 1) * 0.5f;
	//Dot = saturate(Dot);

    float TmpPow = lightPowMap.Sample(lightSmp, float2(Dot, 0.0f)).r;

	//float TmpPow = Dot;

    col.rgb *= LamLightCol(light.dif, TmpPow) + AmbLightCol();

    col.rgb += SpeLightCol(-light.dir, _Base.usePos.xyz, _Base.faceNormal, speCol);

	//Col.rgb += AmbLightCol();

    return col;
}

float4 PLightCol(PLight plight, VS_OUT _Base, float4 _Color)
{

    float4 col = _Color;

    if (!light.lightUseFlg)
        return col;
    if (!plight.flg)
        return col;

    bool TmpFlg = false;

    float3 TmpVec = _Base.usePos.xyz;

    TmpVec = TmpVec - plight.pos;

    float Len;

    Len = length(TmpVec);

    TmpFlg = Len > plight.len ? true : false;

    if (TmpFlg)
        return col;

    TmpVec = normalize(TmpVec);

    float Par = Len / plight.len;

    float Dot;

    Dot = dot(_Base.normal, -TmpVec);

    Dot = saturate(Dot);

    col.rgb *= LamLightCol(plight.dif.rgb, Dot) * Par;

    col.rgb += SpeLightCol(TmpVec, _Base.usePos.xyz, _Base.normal, speCol) * Par;

    return col;
}
