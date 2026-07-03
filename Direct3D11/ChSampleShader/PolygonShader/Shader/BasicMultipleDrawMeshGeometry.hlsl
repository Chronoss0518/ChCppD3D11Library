
#define __SHADER__
#define _SM5_0_

#include"MultiplePolygonBase.hlsli"

#include"../../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawMultiplePolygon.hlsli"

[maxvertexcount(3)]
void main(
	triangle VS_OUT input[3],
	inout TriangleStream<VS_OUT> output
)
{
    if (frameDatas.drawFlgs[input[0].frameNo] == 0)
        return;
	
	for (uint i = 0; i < 3; i++)
	{
        output.Append(input[i]);
    }
}