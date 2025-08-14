#include<Windows.h>
#include"../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"ChSampleShaderBase11_2.h"

using namespace ChD3D11;
using namespace Shader;

void SampleShaderBase11_2::Init(
	ID3D11Device* _device,
	size_t _drawMaxCount)
{
	if (ChPtr::NullCheck(_device))return;
	if (IsInit())return;

	device = _device;

	whiteTex.CreateColorTexture(_device, ChVec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);
	//normalTex.CreateColorTexture(_device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);

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

		CreateBlender(desc);
	}

	{
		D3D11_DEPTH_STENCIL_DESC desc = {
			true,
			D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO ,
			D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS,
			false,
			D3D11_DEFAULT_STENCIL_READ_MASK,
			D3D11_DEFAULT_STENCIL_WRITE_MASK,
			D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP,
			D3D11_STENCIL_OP::D3D11_STENCIL_OP_KEEP
		};

		CreateDepthStencilTester(desc);
	}

	drawMaxCount = _drawMaxCount;

	SetInitFlg(true);
}

void SampleShaderBase11_2::Release()
{
	if (!IsInit())return;

	if (ChPtr::NotNullCheck(rasteriser))
	{
		rasteriser->Release();
		rasteriser = nullptr;
	}

	if (ChPtr::NotNullCheck(blender))
	{
		blender->Release();
		blender = nullptr;
	}

	if (ChPtr::NotNullCheck(depthStencilTester))
	{
		depthStencilTester->Release();
		depthStencilTester = nullptr;
	}

	whiteTex.Release();

	SetInitFlg(false);

}

void SampleShaderBase11_2::SetShaderRasteriser(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (ChPtr::NullCheck(rasteriser))return;

	_dc->RSSetState(rasteriser);
}

void SampleShaderBase11_2::SetShaderBlender(ID3D11DeviceContext* _dc, float* _blendFacotr, unsigned int _sampleMask)
{
	if (ChPtr::NullCheck(_dc))return;
	if (ChPtr::NullCheck(blender))return;

	_dc->OMSetBlendState(blender, _blendFacotr, _sampleMask);
}

void SampleShaderBase11_2::SetShaderDefaultBlender(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	_dc->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void SampleShaderBase11_2::SetShaderDepthStencilTester(ID3D11DeviceContext* _dc, unsigned int _stencilRef)
{
	if (ChPtr::NullCheck(_dc))return;
	_dc->OMSetDepthStencilState(depthStencilTester, _stencilRef);
}

void SampleShaderBase11_2::SetShaderDefaultDepthStencilTester(ID3D11DeviceContext* _dc)
{
	_dc->OMSetDepthStencilState(nullptr, 0);
}

void SampleShaderBase11_2::CreateRasteriser(const D3D11_RASTERIZER_DESC& _desc)
{
	if (ChPtr::NullCheck(device))return;
	if (ChPtr::NotNullCheck(rasteriser))
	{
		rasteriser->Release();
		rasteriser = nullptr;
	}
	device->CreateRasterizerState(&_desc, &rasteriser);
}

void SampleShaderBase11_2::CreateBlender(const D3D11_BLEND_DESC& _desc)
{
	if (ChPtr::NullCheck(device))return;
	if (ChPtr::NotNullCheck(blender))
	{
		blender->Release();
		blender = nullptr;
	}
	device->CreateBlendState(&_desc, &blender);
}

void SampleShaderBase11_2::CreateDepthStencilTester(const D3D11_DEPTH_STENCIL_DESC& _desc)
{
	if (ChPtr::NullCheck(device))return;
	if (ChPtr::NotNullCheck(depthStencilTester))
	{
		depthStencilTester->Release();
		depthStencilTester = nullptr;
	}

	device->CreateDepthStencilState(&_desc, &depthStencilTester);
}

void SampleShaderBase11_2::DrawStart(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (GetShaderNowRunFlg())return;

	_dc->IASetPrimitiveTopology(primitiveTopology);

	Update(_dc);
	SetShaderRasteriser(_dc);
	dc = _dc;
	drawFlg = true;
	GetShaderNowRunFlg() = true;
}

void SampleShaderBase11_2::DrawEnd()
{
	if (!drawFlg)return;
	drawFlg = false;
	dc = nullptr;
	GetShaderNowRunFlg() = false;

}