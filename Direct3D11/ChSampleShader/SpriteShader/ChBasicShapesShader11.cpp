#include<Windows.h>
#include"../../../BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChSprite/ChSprite11.h"
#include"../../ChCB/ChCBBasicShapes/ChCBBasicShapes11.h"
#include"../../ChTexture/ChTexture11.h"

#include"Shader/BasicShapesPosition.hlsli"
#include"Shader/BasicShapesCircle.hlsli"

#include"ChBasicShapesShader11.h"

using namespace ChD3D11;
using namespace Shader;


void BasicShapesPositionShader11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleShaderBase11::Init(_device);

	bsData.Init(_device);
	positionData.Init(_device);

	Ch3D::Vertex vertexs[4];
	vertexBuffer.CreateBuffer(_device, &vertexs[0], 4);

	unsigned long indexs[] = { 0,1,2,0,2,3 };
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

void BasicShapesPositionShader11::InitPositionTri()
{
	positionData.ClearPosition();
	positionData.AddPosition(ChVec2(0.5f, 0.8f));
	positionData.AddPosition(ChVec2(0.2f, 0.2f));
	positionData.AddPosition(ChVec2(0.8f, 0.2f));
}

void BasicShapesPositionShader11::InitPositionSquare()
{
	positionData.ClearPosition();
	positionData.AddPosition(ChVec2(0.25f, 0.25f));
	positionData.AddPosition(ChVec2(0.75f, 0.25f));
	positionData.AddPosition(ChVec2(0.75f, 0.75f));
	positionData.AddPosition(ChVec2(0.25f, 0.75f));
}

void BasicShapesPositionShader11::InitPositionRhombus()
{
	positionData.ClearPosition();
	positionData.AddPosition(ChVec2(0.25f, 0.5f));
	positionData.AddPosition(ChVec2(0.5f, 0.25f));
	positionData.AddPosition(ChVec2(0.75f, 0.5f));
	positionData.AddPosition(ChVec2(0.5f, 0.75f));
}

void BasicShapesPositionShader11::Release()
{
	if (!IsInit())return;

	SampleShaderBase11::Release();

	bsData.Release();
	positionData.Release();
}

void BasicShapesPositionShader11::InitVertexShader()
{
#include"BasicShapesVertex.inc"

	D3D11_INPUT_ELEMENT_DESC decl[3];

	decl[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA };
	decl[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


	SampleShaderBase11::CreateVertexShader(decl, sizeof(decl) / sizeof(D3D11_INPUT_ELEMENT_DESC), main, sizeof(main));

}

void BasicShapesPositionShader11::InitPixelShader()
{

#include"BasicShapesPositionPixel.inc"

	SampleShaderBase11::CreatePixelShader(main, sizeof(main));
}


void BasicShapesPositionShader11::Draw(
	Sprite11& _sprite,
	const ChVec4& _baseColor,
	const ChLMat& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;

	bsData.SetSpriteMatrix(_mat);

	bsData.SetColor(_baseColor);

	bsData.SetShaderBasicShapesData(GetDC());

	positionData.SetPSBasicShapesPositionData(GetDC());

	if (alphaBlendFlg)
	{
		SampleShaderBase11::SetShaderBlender(GetDC());
	}

	unsigned int offsets = 0;

	auto&& vertexs = _sprite.GetVertexs();

	vertexBuffer.UpdateResouce(GetDC(), &vertexs.vertex[0]);

	vertexBuffer.SetVertexBuffer(GetDC(), offsets);

	indexBuffer.SetIndexBuffer(GetDC());

	GetDC()->DrawIndexed(6, 0, 0);

	if (alphaBlendFlg)
	{
		SampleShaderBase11::SetShaderDefaultBlender(GetDC());
	}
}

void BasicShapesCircleShader11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleShaderBase11::Init(_device);

	bsData.Init(_device);
	circleData.Init(_device);

	Ch3D::Vertex vertexs[4];
	vertexBuffer.CreateBuffer(_device, &vertexs[0], 4);

	unsigned long indexs[] = { 0,1,2,0,2,3 };
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

void BasicShapesCircleShader11::InitCenterCircle()
{
	circleData.ClearCircleData();
	circleData.AddCircleData(ChVec2(0.5f, 0.5f),0.4f);
}

void BasicShapesCircleShader11::Release()
{
	if (!IsInit())return;

	SampleShaderBase11::Release();

	circleData.Release();
	bsData.Release();
}

void BasicShapesCircleShader11::InitVertexShader()
{
#include"BasicShapesVertex.inc"

	D3D11_INPUT_ELEMENT_DESC decl[3];

	decl[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA };
	decl[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };


	SampleShaderBase11::CreateVertexShader(decl, sizeof(decl) / sizeof(D3D11_INPUT_ELEMENT_DESC), main, sizeof(main));

}

void BasicShapesCircleShader11::InitPixelShader()
{

#include"BasicShapesCirclePixel.inc"

	SampleShaderBase11::CreatePixelShader(main, sizeof(main));
}


void BasicShapesCircleShader11::Draw(
	Sprite11& _sprite,
	const ChVec4& _baseColor,
	const ChLMat& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;

	bsData.SetSpriteMatrix(_mat);

	bsData.SetColor(_baseColor);

	bsData.SetShaderBasicShapesData(GetDC());

	circleData.SetPSBasicShapesCircleData(GetDC());

	if (alphaBlendFlg)
	{
		SampleShaderBase11::SetShaderBlender(GetDC());
	}

	unsigned int offsets = 0;

	auto&& vertexs = _sprite.GetVertexs();

	vertexBuffer.UpdateResouce(GetDC(), &vertexs.vertex[0]);

	vertexBuffer.SetVertexBuffer(GetDC(), offsets);

	indexBuffer.SetIndexBuffer(GetDC());

	GetDC()->DrawIndexed(6, 0, 0);

	if (alphaBlendFlg)
	{
		SampleShaderBase11::SetShaderDefaultBlender(GetDC());
	}
}

