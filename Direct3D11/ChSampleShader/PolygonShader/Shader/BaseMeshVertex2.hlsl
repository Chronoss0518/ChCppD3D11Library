
#define __SHADER__
#define _SM5_0_

#include"PolygonBase2.hlsli"

#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawPolygon.hlsli"
#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/BoneBlending.hlsli"

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
    uint _instanceID : SV_InstanceID
){
    VS_OUT res;

    res.worldPos = _pos;

    float4x4 tmpMat = _blendNum > 0 ?
		BlendMatrix(_blendPow, _blendNum) :
		charaDatas.frameMatrix;
	
    MTWStruct tmp = ModelToWorld(res.worldPos, _uv, _normal, _faceNormal, tmpMat);

    res.worldPos = tmp.worldPos;
    res.viewPos = tmp.viewPos;
    res.proPos = tmp.proPos;
    res.pos = tmp.proPos;
    res.vertexNormal = tmp.vertexNormal;
    res.faceNormal = tmp.faceNormal;
    res.uv = tmp.uv;
    res.instanceID = _instanceID;

    res.color = _color;

    return res;
}


