#ifndef Ch_ModelBase_h
#define Ch_ModelBase_h

#ifdef __SHADER__

struct VS_OUT
{
    float4 pos                  : SV_POSITION;
    float3 vertexNormal         : NORMAL0;
    float3 faceNormal           : NORMAL1;
    float4 color                : COLOR0;
    float4 worldPos             : POSITION0;
    float4 viewPos              : POSITION1;
    float4 proPos               : POSITION2;
    float2 uv                   : TEXCOORD0;
    uint instanceID     : SV_InstanceID;
};

#endif

#endif