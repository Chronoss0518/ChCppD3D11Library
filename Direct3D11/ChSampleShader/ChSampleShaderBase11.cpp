#include<Windows.h>
#include"../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"ChSampleShaderBase11.h"

using namespace ChD3D11;
using namespace Shader;

void SampleShaderBase11::Init(ID3D11Device* _device)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(_device))return;

	device = _device;

	whiteTex.CreateColorTexture(_device, ChVec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);
	normalTex.CreateColorTexture(_device, ChVec4(0.5f, 1.0f, 0.5f, 1.0f), 1, 1);

	InitVertexShader();
	InitPixelShader();
	InitGeometryShader();
	InitHullShader();
	InitDomainShader();
	InitComputeShader();

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

	SetInitFlg(true);
}

void SampleShaderBase11::CreateVertexShader(
	const D3D11_INPUT_ELEMENT_DESC* _decl,
	unsigned long _declNum,
	const unsigned char* _shaderByte,
	unsigned long _shaderByteNum)
{
	if (ChPtr::NullCheck(device))return;
	vs.Init(device, _decl, _declNum, _shaderByte, _shaderByteNum);
}

void SampleShaderBase11::CreatePixelShader(
	const unsigned char* _shaderByte,
	unsigned long _shaderByteNum)
{
	if (ChPtr::NullCheck(device))return;
	ps.Init(device, _shaderByte, _shaderByteNum);
}

void SampleShaderBase11::CreateGeometryShader(
	const unsigned char* _shaderByte,
	unsigned long _shaderByteNum)
{
	if (ChPtr::NullCheck(device))return;
	gs.Init(device, _shaderByte, _shaderByteNum);
}

void SampleShaderBase11::CreateHullShader(
	const unsigned char* _shaderByte,
	unsigned long _shaderByteNum)
{
	if (ChPtr::NullCheck(device))return;
	hs.Init(device, _shaderByte, _shaderByteNum);
}

void SampleShaderBase11::CreateDomainShader(
	const unsigned char* _shaderByte,
	unsigned long _shaderByteNum)
{
	if (ChPtr::NullCheck(device))return;
	ds.Init(device, _shaderByte, _shaderByteNum);
}

void SampleShaderBase11::CreateComputeShader(
	const unsigned char* _shaderByte,
	unsigned long _shaderByteNum)
{
	if (ChPtr::NullCheck(device))return;
	cs.Init(device, _shaderByte, _shaderByteNum);
}

void SampleShaderBase11::Release()
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
	vs.Release();
	ps.Release();

	whiteTex.Release();
	normalTex.Release();

	SetInitFlg(false);
}

void SampleShaderBase11::SetShader(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	vs.SetShader(_dc);
	ps.SetShader(_dc);
	gs.SetShader(_dc);
	hs.SetShader(_dc);
	ds.SetShader(_dc);
	ps.SetShader(_dc);
}

void SampleShaderBase11::SetShaderRasteriser(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (ChPtr::NullCheck(rasteriser))return;

	_dc->RSSetState(rasteriser);
}

void SampleShaderBase11::SetShaderBlender(ID3D11DeviceContext* _dc, float* _blendFacotr, unsigned int _sampleMask)
{
	if (ChPtr::NullCheck(_dc))return;
	if (ChPtr::NullCheck(blender))return;

	_dc->OMSetBlendState(blender, _blendFacotr, _sampleMask);
}

void SampleShaderBase11::SetShaderDefaultBlender(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	_dc->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}

void SampleShaderBase11::SetShaderDepthStencilTester(ID3D11DeviceContext* _dc, unsigned int _stencilRef)
{
	if (ChPtr::NullCheck(_dc))return;
	_dc->OMSetDepthStencilState(depthStencilTester, _stencilRef);
}

void SampleShaderBase11::SetShaderDefaultDepthStencilTester(ID3D11DeviceContext* _dc)
{
	_dc->OMSetDepthStencilState(nullptr, 0);
}

void SampleShaderBase11::CreateRasteriser(const D3D11_RASTERIZER_DESC& _desc)
{
	if (ChPtr::NullCheck(device))return;
	if (ChPtr::NotNullCheck(rasteriser))
	{
		rasteriser->Release();
		rasteriser = nullptr;
	}
	device->CreateRasterizerState(&_desc, &rasteriser);
}

void SampleShaderBase11::CreateBlender(const D3D11_BLEND_DESC& _desc)
{
	if (ChPtr::NullCheck(device))return;
	if (ChPtr::NotNullCheck(blender))
	{
		blender->Release();
		blender = nullptr;
	}
	device->CreateBlendState(&_desc, &blender);
}

void SampleShaderBase11::CreateDepthStencilTester(const D3D11_DEPTH_STENCIL_DESC& _desc)
{
	if (ChPtr::NullCheck(device))return;
	if (ChPtr::NotNullCheck(depthStencilTester))
	{
		depthStencilTester->Release();
		depthStencilTester = nullptr;
	}

	device->CreateDepthStencilState(&_desc, &depthStencilTester);
}

void SampleShaderBase11::DrawStart(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (GetShaderNowRunFlg())return;

	_dc->IASetPrimitiveTopology(primitiveTopology);
	SetShader(_dc);
	Update(_dc);
	SetShaderRasteriser(_dc);
	dc = _dc;
	drawFlg = true; 
	GetShaderNowRunFlg() = true;
}

void SampleShaderBase11::DrawEnd()
{
	if (!drawFlg)return;
	drawFlg = false;
	dc = nullptr;
	GetShaderNowRunFlg() = false;

}