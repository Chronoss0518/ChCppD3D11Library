
#define __SHADER__
#define _SM5_0_

#include"PolygonBase.hlsli"

#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawPolygon.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/OutLine.hlsli"

//ピクセルシェダ(PixelShader)//
//通常描画//
float4 main(VS_OUT _in) : SV_Target0
{
#if false
    
    float3 camNormal = mul(_in.vertexNormal, (float3x3) drawData.viewMat);
    
    clip(camNormal.z);

#endif

	//カメラの前方にあるかの判定//
    clip(_in.viewPos.z);
    
    FrustumCulling(_in.proPos);
	
    float4 res = GetOutLineColor();
	
    AlphaTest(res.a);
	
    return res;
}
