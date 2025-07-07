#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"ChShaderParts11.h"

using namespace ChD3D11::ShaderParts;

///////////////////////////////////////////////////////////////////////////////////
//ViewPort Method//
///////////////////////////////////////////////////////////////////////////////////

void ViewPort::SetDrawData(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	_dc->RSSetViewports(1, &View);
}

///////////////////////////////////////////////////////////////////////////////////
//DrawWindow Method//
///////////////////////////////////////////////////////////////////////////////////

void DrawWindow::Init(
	ID3D11Device* _device,
	IDXGISwapChain* _sc)
{

	if (ChPtr::NullCheck(_device))return;
	if (ChPtr::NullCheck(_sc))return;

	Release();

	window = _sc;
	ID3D11Texture2D* pBackBuffer = nullptr;
	window->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	_device->CreateRenderTargetView(pBackBuffer, nullptr, &bbTargetView);
	pBackBuffer->Release();
	SetInitFlg(true);
}

void DrawWindow::Init(ChD3D11::DirectX3D11& _app)
{
	if (!_app.IsInit())return;
	Init(_app.GetDevice(), _app.GetSC());
}

void DrawWindow::Release()
{
	if (!*this)return;

	if (ChPtr::NotNullCheck(bbTargetView))
	{
		bbTargetView->Release();
		bbTargetView = nullptr;
	}

	SetInitFlg(false);
}

void DrawWindow::SetDrawData(ID3D11DeviceContext* _dc,ID3D11DepthStencilView* _dsView)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!*this)return;

	_dc->OMSetRenderTargets(1, &bbTargetView, _dsView);
}

void DrawWindow::SetBackGroundColor(ID3D11DeviceContext* _dc,const ChVec4& _color)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!*this)return;

	_dc->ClearRenderTargetView(bbTargetView, _color.val.GetVal());
}

void DrawWindow::Draw()
{
	if (!*this)return;
	window->Present(sEffect, 0);
}
