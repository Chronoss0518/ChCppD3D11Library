#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBHighlight11.h"

using namespace ChD3D11;
using namespace CB;

void CBHighlight11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	CBBase11::Init(_device);
	blurBuf.CreateBuffer(GetDevice(), HIGHLIGHT_DATA_REGISTERNO);
	SetInitFlg(true);
}

void CBHighlight11::Release()
{
	if (!IsInit())return;
	blurBuf.Release();
	SetInitFlg(false);
	updateFlg = true;
}

void CBHighlight11::SetGameWindowSize(const ChVec2& _size)
{
	if (_size.w <= 0.0f || _size.h <= 0.0f)return;

	blurData.windowSize = _size;
	updateFlg = true;
}

void CBHighlight11::SetBlurPower(const int& _blurPower)
{
	if (_blurPower < 0)return;
	if (blurData.blurPower == _blurPower)return;

	blurData.blurPower = _blurPower;
	updateFlg = true;
}

void CBHighlight11::SetLiteBlurFlg(const bool _flg)
{
	if ((blurData.liteBlurFlg == 1) == _flg)return;
	blurData.liteBlurFlg = _flg ? 1 : 0;
	updateFlg = true;
}

void CBHighlight11::SetBoostPower(const float& _boostPower)
{
	if (_boostPower < 0)return;
	if (blurData.boostPower == _boostPower)return;

	blurData.boostPower = _boostPower;
	updateFlg = true;
}

void CBHighlight11::SetBlurData(const ChS_HighLight& _data)
{
	blurData = _data;
	updateFlg = true;
}

void CBHighlight11::SetPSSpriteData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	blurBuf.SetToPixelShader(_dc);
}

void CBHighlight11::SetVSSpriteData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	blurBuf.SetToVertexShader(_dc);
}

void CBHighlight11::SetShaderSpriteData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSSpriteData(_dc);
	SetPSSpriteData(_dc);
}


void CBHighlight11::UpdateSD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!updateFlg)return;
	blurBuf.UpdateResouce(_dc, &blurData);
	updateFlg = false;
}
