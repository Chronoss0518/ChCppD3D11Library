#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBCircleCulling11.h"

using namespace ChD3D11;
using namespace CB;

void CBCircleCulling11::Init(ID3D11Device* _device)
{
	Release();
	CBBase11::Init(_device);
	buf.CreateBuffer(_device, CIRCLE_CULLING_DATA);
	SetInitFlg(true);
}

void CBCircleCulling11::Release()
{
	if (!*this)return;
	buf.Release();
	SetInitFlg(false);
}

void CBCircleCulling11::SetDrawStartDir(const ChVec2& _drawStartDir)
{
	if (!IsInit())return;
	data.drawStartDir = _drawStartDir;
	updateFlg = true;
}

void CBCircleCulling11::SetCenterPos(const ChVec2& _dirStartPos)
{
	if (!IsInit())return;
	data.centerPos = _dirStartPos;
	updateFlg = true;
}

void CBCircleCulling11::SetDrawValue(const float _drawValue)
{
	if (!IsInit())return;

	data.drawValue = _drawValue;

	if (data.drawValue < -1.0f)data.drawValue = -1.0f;
	if (data.drawValue > 1.0f)data.drawValue = 1.0f;

	updateFlg = true;
}

void CBCircleCulling11::SetDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	Update(_dc);
	buf.SetToPixelShader(_dc);
}

float CBCircleCulling11::GetDrawValue()
{
	if (!IsInit())return 0.0f;
	return data.drawValue;
}

void CBCircleCulling11::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;

	buf.UpdateResouce(_dc, &data);
	updateFlg = false;
}