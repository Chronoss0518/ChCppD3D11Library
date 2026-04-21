#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBOutLine11.h"

using namespace ChD3D11;
using namespace CB;

void CBOutLine11::Init(
	ID3D11Device* _device)
{
	if (IsInit())return;

	CBBase11::Init(_device);
	outlineBuf.CreateBuffer(GetDevice(), OUTLINE_DATA_REGISTERNO);
	SetInitFlg(true);
}

void CBOutLine11::Release()
{
	if (!IsInit())return;

	outlineBuf.Release();
	SetInitFlg(false);
	updateFlg = true;
}

void CBOutLine11::SetWidth(const float _width)
{
	if (_width <= 0.0f)return;

	outlineData.width = _width;
	updateFlg = true;
}

void CBOutLine11::SetOutLineColor(const ChVec4& _color)
{
	outlineData.outlineColor = _color;
	updateFlg = true;
}

void CBOutLine11::SetOutLineData(const ChOutLineData& _data)
{
	outlineData = _data;
	updateFlg = true;
}

void CBOutLine11::SetPSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	outlineBuf.SetToPixelShader(_dc);
}

void CBOutLine11::SetVSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	outlineBuf.SetToVertexShader(_dc);
}

void CBOutLine11::SetShaderDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSDrawData(_dc);
	SetPSDrawData(_dc);
}


void CBOutLine11::UpdateSD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!updateFlg)return;
	outlineBuf.UpdateResouce(_dc, &outlineData);
	updateFlg = false;
}
