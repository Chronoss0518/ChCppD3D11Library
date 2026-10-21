
#define __SHADER__
#define _SM5_0_

#include"PostProcessOutLine.hlsli"

#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawSprite.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/PostProcessOutLine.hlsli"

//頂点シェーダ(VertexShader)//
//通常描画//
VS_OUT main
(
	float4 _pos : POSITION0,
	float2 _uv : TEXCOORD0,
	float4 _color : COLOR0,
	float3 _normal : NORMAL0,
	float3 _faceNormal : NORMAL1,
	uint _blendNum : BLENDINDEX0,
	row_major float4x4 _blendPow : BLENDWEIGHT0,
	uint _instanceId : SV_InstanceID
)
{
    VS_OUT res;
    
    float4x4 tmpMat = _blendNum > 0 ?
		mul(frameData.frameMatrix, BlendMatrix(_blendPow, _blendNum)) :
		frameData.frameMatrix;

#if 0
    float4x4 scaleMat = float4x4(
		1.0f + width, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f + width, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f + width, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
    
    tmpMat = mul(scaleMat, tmpMat);
	
    MTWStruct tmp = ModelToWorld(_pos, _uv, _normal, _faceNormal, tmpMat);

#else
    
    MTWStruct tmp = ModelToWorld(GetOutLinePos(_pos, _normal), _uv, _normal, _faceNormal, tmpMat);

#endif
    
    res.vertexNormal = tmp.vertexNormal;
    res.faceNormal = tmp.faceNormal;
    
    res.worldPos = tmp.worldPos;
    res.viewPos = tmp.viewPos;
    res.proPos = tmp.proPos;
    res.pos = tmp.proPos;
    res.uv = tmp.uv;

    res.color = _color;

    res.temperature = 1.0f;

    return res;
}