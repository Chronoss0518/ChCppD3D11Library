#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChPolygonBoard/ChPolygonBoard11.h"

#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"

#include"ChSamplePolygonShaderBase11.h"

using namespace ChCpp;
using namespace ChD3D11;
using namespace Shader;

#define DEBUG 0

void SamplePolygonShaderBase11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleShaderBase11::Init(_device);
	polyData.Init(_device, &GetWhiteTexture(), &GetNormalTexture());
}

void SamplePolygonShaderBase11::Release()
{
	if (!IsInit())return;

	SampleShaderBase11::Release();
	polyData.Release();
}

void SamplePolygonShaderBase11::CreateDefaultBlender()
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

#if false

	desc.RenderTarget[1].BlendEnable = true;
	desc.RenderTarget[1].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[1].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[1].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	desc.RenderTarget[1].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[1].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[1].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	desc.RenderTarget[1].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

#endif

	CreateBlender(desc);
}

void SamplePolygonShaderBase11::SetProjectionMatrix(const ChLMat& _mat)
{
	polyData.SetProjectionMatrix(_mat);
}

void SamplePolygonShaderBase11::SetViewMatrix(const ChLMat& _mat)
{
	polyData.SetViewMatrix(_mat);
}

void SamplePolygonShaderBase11::SetMoveUV(const ChVec2& _move)
{
	polyData.SetMoveUV(_move);
}

void SamplePolygonShaderBase11::SetFillMode(const D3D11_FILL_MODE _fill)
{
	fill = _fill;
	updateFlg = true;
}

void SamplePolygonShaderBase11::SetCullMode(const D3D11_CULL_MODE _cull)
{
	cull = _cull;
	updateFlg = true;
}

void SamplePolygonShaderBase11::SetShaderDrawData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	polyData.SetVSDrawData(_dc);
}

void SamplePolygonShaderBase11::SetShaderCharaData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	polyData.SetVSCharaData(_dc);
}

void SamplePolygonShaderBase11::DrawStart(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!IsInit())return;
	if (IsDraw())return;

	SampleShaderBase11::DrawStart(_dc);
	SetShaderDrawData(_dc);
}

void SamplePolygonShaderBase11::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;

	//•`‰æ•û–@//
	D3D11_RASTERIZER_DESC desc
	{
		fill,
		cull,
		false,
		0,
		0.0f,
		0.0f,
		false,
		false,
		false,
		true
	};

	SampleShaderBase11::CreateRasteriser(desc);
	updateFlg = false;
}
