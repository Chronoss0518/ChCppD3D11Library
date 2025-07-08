#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChSprite/ChSprite11.h"

#include"../../ChCB/ChCBSprite/ChCBSprite11.h"
#include"../../ChCB/ChCBHighlight/ChCBHighlight11.h"

#include"ChBasicHighlightShader11.h"

using namespace ChD3D11;
using namespace Shader;


void BasicHighlightShader11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleSpriteShaderBase11::Init(_device);

	highlightMapData.Init(_device);

	{
		D3D11_BLEND_DESC desc;
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_COLOR;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_DEST_COLOR;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_MAX;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;


		CreateBlender(desc);
	}

	{

		D3D11_SAMPLER_DESC sDesc;
		ZeroMemory(&sDesc, sizeof(D3D11_SAMPLER_DESC));
		sDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		sDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		sDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;

		_device->CreateSamplerState(&sDesc, &sampler);

	}
}

void BasicHighlightShader11::Release()
{
	if (!IsInit())return;

	SampleSpriteShaderBase11::Release();

	highlightMapData.Release();
}

void BasicHighlightShader11::InitPixelShader()
{

#include"../SpriteShader/BasicHighlightPixel.inc"

	SampleSpriteShaderBase11::CreatePixelShader(main, sizeof(main));
}


void BasicHighlightShader11::DrawStart(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!IsInit())return;
	if (IsDraw())return;

	SampleSpriteShaderBase11::DrawStart(_dc);

	SampleSpriteShaderBase11::SetShaderBlender(GetDC());

}

void BasicHighlightShader11::Draw(
	TextureBase11& _tex,
	Sprite11& _sprite,
	const ChLMat& _mat)
{
	Draw(_tex, _sprite, ChVec4(1.0f), _mat);
}

void BasicHighlightShader11::Draw(
	TextureBase11& _tex,
	Sprite11& _sprite,
	const ChVec4& _baseColor,
	const ChLMat& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (!_tex.IsTex())return;

	spriteData.SetSpriteMatrix(_mat);

	spriteData.SetBaseColor(_baseColor);

	spriteData.SetShaderSpriteData(GetDC());

	spriteData.SetBaseTexture(&_tex);

	spriteData.SetShaderTexture(GetDC());

	highlightMapData.SetPSSpriteData(GetDC());

	GetDC()->PSSetSamplers(HIGHLIGHT_SAMPLER_REGISTERNO, 1, &sampler);

	unsigned int offsets = 0;

	auto&& vertexs = _sprite.GetVertexs();

	vertexBuffer.UpdateResouce(GetDC(), &vertexs.vertex[0]);

	vertexBuffer.SetVertexBuffer(GetDC(), offsets);

	indexBuffer.SetIndexBuffer(GetDC());

	GetDC()->DrawIndexed(6, 0, 0);

}

void BasicHighlightShader11::DrawEnd()
{
	if (!IsDraw())return;

	SampleSpriteShaderBase11::DrawEnd();

	SampleSpriteShaderBase11::SetShaderDefaultBlender(GetDC());

}
