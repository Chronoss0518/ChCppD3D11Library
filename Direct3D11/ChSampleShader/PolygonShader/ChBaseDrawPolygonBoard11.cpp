#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChPolygonBoard/ChPolygonBoard11.h"

#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"

#include"ChBaseDrawPolygonBoard11.h"

using namespace ChCpp;
using namespace ChD3D11;
using namespace Shader;

#define DEBUG 0


void BaseDrawPolygonBoard11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SamplePolygonShaderBase11::Init(_device);

	{
		D3D11_BLEND_DESC desc;
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

		desc.RenderTarget[1].BlendEnable = true;
		desc.RenderTarget[1].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[1].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[1].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[1].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[1].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[1].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[1].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

		CreateBlender(desc);
	}

	vertexBuffer.CreateBuffer(_device, drawVertexs, 3);
	unsigned long indexs[3] = { 0,1,2 };
	indexBuffer.CreateBuffer(_device, indexs, 3);
}

void BaseDrawPolygonBoard11::Release()
{
	if (!IsInit())return;

	SamplePolygonShaderBase11::Release();
	vertexBuffer.Release();
	indexBuffer.Release();
}

void BaseDrawPolygonBoard11::InitVertexShader()
{

#include"../PolygonShader/BasePoboVertex.inc"

	D3D11_INPUT_ELEMENT_DESC decl[4];

	decl[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA };
	decl[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

	SamplePolygonShaderBase11::CreateVertexShader(decl, sizeof(decl) / sizeof(D3D11_INPUT_ELEMENT_DESC), main, sizeof(main));
}

void BaseDrawPolygonBoard11::InitPixelShader()
{
#include"../PolygonShader/BasePolygonPixcel.inc"

	SamplePolygonShaderBase11::CreatePixelShader(main, sizeof(main));
}

void BaseDrawPolygonBoard11::DrawStart(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (IsDraw())return;

	SamplePolygonShaderBase11::DrawStart(_dc);

	SetShaderDrawData(_dc);
}

void BaseDrawPolygonBoard11::Draw(
	TextureBase11& _tex,
	PolygonBoard11& _polygon,
	const ChLMat& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (_polygon.GetVertexSize() < 3)return;

	polyData.SetWorldMatrix(_mat);
	polyData.SetFrameMatrix(ChLMat());

	polyData.SetShaderCharaData(GetDC());

	auto mate = _polygon.GetMaterial();

	polyData.SetMateDiffuse(mate.diffuse);
	polyData.SetMateSpecularColor(mate.specularColor);
	polyData.SetMateSpecularPower(mate.specularPower);
	polyData.SetMateAmbientColor(mate.ambient);

	polyData.SetShaderMaterialData(GetDC());

	polyData.SetBaseTexture(&_tex);
	polyData.SetNormalTexture(nullptr);

	polyData.SetShaderTexture(GetDC());

	unsigned int offsets = 0;

	drawVertexs[0] = _polygon.GetVertex(0);

	if (alphaBlendFlg)
	{
		SamplePolygonShaderBase11::SetShaderBlender(GetDC());
	}

	for (unsigned long i = 1; i < _polygon.GetVertexSize() - 1; i++)
	{
		drawVertexs[1] = _polygon.GetVertex(i);
		drawVertexs[2] = _polygon.GetVertex(i + 1);

		vertexBuffer.UpdateResouce(GetDC(), &drawVertexs[0]);

		vertexBuffer.SetVertexBuffer(GetDC(), offsets);

		indexBuffer.SetIndexBuffer(GetDC());

		GetDC()->DrawIndexed(3, 0, 0);
	}

	if (alphaBlendFlg)
	{
		SamplePolygonShaderBase11::SetShaderDefaultBlender(GetDC());
	}
}

void BaseDrawPolygonBoard11::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;

	SamplePolygonShaderBase11::Update(_dc);
}
