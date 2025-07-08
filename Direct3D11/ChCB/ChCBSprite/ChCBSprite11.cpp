#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBSprite11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/5.0/Texture/BaseTexture.hlsli"

using namespace ChD3D11;
using namespace CB;

void CBSprite11::Init(
	ID3D11Device* _device,
	TextureBase11* _defaultBase)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(_defaultBase))return;
	if (!_defaultBase->IsTex())return;

	CBBase11::Init(_device);

	spBuf.CreateBuffer(GetDevice(), SPRITE_DATA_REGISTERNO);
	defaultBase = _defaultBase;
	SetInitFlg(true);
}

void CBSprite11::Release()
{
	if (!IsInit())return;

	spBuf.Release();
	SetInitFlg(false);
	sUpdateFlg = true;
}

void CBSprite11::SetSpriteMatrix(const ChLMat& _mat)
{
	spData.spriteMat = _mat;
	sUpdateFlg = true;
}

void CBSprite11::SetBaseColor(const ChVec4& _color)
{
	spData.baseColor = _color;
	sUpdateFlg = true;
}

void CBSprite11::SetSpriteData(const ChS_SpriteData& _data)
{
	spData = _data;
	sUpdateFlg = true;
}

void CBSprite11::SetPSSpriteData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	spBuf.SetToPixelShader(_dc);
}

void CBSprite11::SetVSSpriteData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	spBuf.SetToVertexShader(_dc);
}

void CBSprite11::SetShaderSpriteData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSSpriteData(_dc);
	SetPSSpriteData(_dc);
}

void CBSprite11::SetShaderTexture(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	CBBase11::SetShaderTexture(_dc, baseTex, *defaultBase, BASE_TEXTURE_REGISTER);
}

void CBSprite11::UpdateSD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!sUpdateFlg)return;
	spBuf.UpdateResouce(_dc, &spData);
	sUpdateFlg = false;
}
