#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChSprite/ChSprite11.h"

#include"../../ChCB/ChCBSprite/ChCBSprite11.h"

#include"ChSampleSpriteShaderBase11.h"

using namespace ChD3D11;
using namespace Shader;


void SampleSpriteShaderBase11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleShaderBase11::Init(_device);

	spriteData.Init(_device, &GetWhiteTexture());

	Ch3D::Vertex vertexs[4];
	vertexBuffer.CreateBuffer(_device, &vertexs[0], 4);

	unsigned long indexs[] = {0,1,2,0,2,3};
	indexBuffer.CreateBuffer(_device, &indexs[0], 6);

	D3D11_RASTERIZER_DESC desc
	{
		D3D11_FILL_MODE::D3D11_FILL_SOLID,
		D3D11_CULL_MODE::D3D11_CULL_NONE,
		true,
		0,
		0.0f,
		0.0f,
		false,
		false,
		true,
		false
	};

	CreateRasteriser(desc);
}

void SampleSpriteShaderBase11::Release()
{
	if (!IsInit())return;

	SampleShaderBase11::Release();
	spriteData.Release();
}

void SampleSpriteShaderBase11::InitVertexShader()
{
#include"../SpriteShader/BaseSpriteVertex.inc"

	D3D11_INPUT_ELEMENT_DESC decl[3];

	decl[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA };
	decl[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

	SampleShaderBase11::CreateVertexShader(decl, sizeof(decl) / sizeof(D3D11_INPUT_ELEMENT_DESC), main, sizeof(main));
}

void SampleSpriteShaderBase11::DrawStart(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!IsInit())return;
	if (IsDraw())return;

	SampleShaderBase11::DrawStart(_dc);
}
