#include<Windows.h>
#include"../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"

#include"../../BaseIncluder/ChD3D11I.h"

#include"../../../ChCppWinLibrary/WindowsObject/WindObject/ChWindObject.h"
#include"ChDirectX11Controller.h"

#include"../ChShaderObject/ChShaderObject11.h"
#include"../ChShaderParts/ChShaderParts11.h"
#include"../ChSampleShader/SpriteShader/ChBaseDrawSprite11.h"
#include"../ChSprite/ChSprite11.h"
#include"../ChTexture/ChTexture11.h"

using namespace ChD3D11;

#if 0
void DirectX3D11::Init(
	ChWin::WindObject& _windObject,
	const bool _fullScreenFlg)
{
	if (!_windObject.IsInit())return;

	auto windSize = _windObject.GetWindSize();

	Init(_windObject.GethWnd(),
		_fullScreenFlg,
		static_cast<unsigned long>(windSize.w),
		static_cast<unsigned long>(windSize.h));

}
#endif

void DirectX3D11::Init(
	HWND _hWnd,
	const bool _fullScreenFlg,
	const unsigned long _scrW,
	const unsigned long _scrH)
{
	if (IsInit())return;
	if (ChPtr::NullCheck(_hWnd))return;
	
	CreateDevice(_hWnd, _scrW, _scrH);
	if (!IsInstanse())
	{
		PostQuitMessage(0);
		return;
	}
	scWindow->SetFullscreenState(_fullScreenFlg, nullptr);

	spriteShader = ChPtr::Make_S<Shader::BaseDrawSprite11>();
	spriteShader->Init(device);

	dsBuffer = ChPtr::Make_S<DepthStencilTexture11>();
	dsBuffer->CreateDepthBuffer(device, _scrW, _scrH);

	outSprite = ChPtr::Make_S<Sprite11>();
	outSprite->Init();

	window = ChPtr::Make_S<ShaderParts::DrawWindow>();
	window->Init(device, scWindow);
	window->SetSwapEffect(DXGI_SWAP_EFFECT_DISCARD);

	view = ChPtr::Make_S<ShaderParts::ViewPort>();
	view->SetDrawDepth(0.0f, 1.0f);
	view->SetTopLeftPos(ChVec2(0.0f, 0.0f));
	view->SetSize(ChVec2(_scrW, _scrH));

	SetInitFlg(true);
}

void DirectX3D11::Release()
{
	if (view != nullptr) { view = nullptr; }
	if (window != nullptr) { window->Release(); window = nullptr; }
	if (outSprite != nullptr) { outSprite = nullptr; }
	if (dsBuffer != nullptr) { dsBuffer->Release(); dsBuffer = nullptr; }
	if (spriteShader != nullptr) { spriteShader->Release(); spriteShader = nullptr; }

	if (ChPtr::NotNullCheck(factory)) { factory->Release(); factory = nullptr; }
	if (ChPtr::NotNullCheck(device)) { device->Release(); device = nullptr; }
	if (ChPtr::NotNullCheck(dContext)){dContext->ClearState();  dContext->Release(); dContext = nullptr;}
	if (ChPtr::NotNullCheck(scWindow)) { scWindow->Release(); scWindow = nullptr; }
	if (ChPtr::NotNullCheck(surface)) { surface->Release(); surface = nullptr; }
	if (ChPtr::NotNullCheck(renderTarget)) { renderTarget->Release(); renderTarget = nullptr; }

	SetInitFlg(false);
}

void DirectX3D11::CreateDevice(
	HWND _hWnd,
	const unsigned long _scrW,
	const unsigned long _scrH)
{
	//DirectXの機能設定//
	D3D_FEATURE_LEVEL lv[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL rLv;

	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
	{
		Release();
		return;
	}

	if (FAILED(D3D11CreateDevice(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		//0, 
		lv,
		1,
		D3D11_SDK_VERSION,
		&device,
		&rLv,
		&dContext)))
	{
		Release();
		return;
	};

	{
		DXGI_SWAP_CHAIN_DESC scd;
		ChStd::MZero(&scd);
		scd.BufferCount = 1;
		scd.BufferDesc.Width = static_cast<unsigned int>(createDeviceWitdh = _scrW);
		scd.BufferDesc.Height = static_cast<unsigned int>(createDeviceHeight = _scrH);
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		//塗り替える時間//
		//scd.BufferDesc.RefreshRate.Numerator = 0;
		//scd.BufferDesc.RefreshRate.Denominator = 0;

		//画面出力//
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		//ハンドル紐づけ//
		scd.OutputWindow = _hWnd;
		//1ピクセルに使う中間補完色の数//
		scd.SampleDesc.Count = 1;
		//画質レベル//
		scd.SampleDesc.Quality = 0;

		scd.Windowed = true;


		if (FAILED(factory->CreateSwapChain(
			device,
			&scd,
			&scWindow)))
		{
			Release();
			return;
		};
	}

	if (FAILED(scWindow->GetBuffer(0, IID_PPV_ARGS(&surface))))
	{
		Release();
		return;
	}

	ID3D11Texture2D* pBackBuffer = nullptr;

	scWindow->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	device->CreateRenderTargetView(pBackBuffer, nullptr, &renderTarget);

	pBackBuffer->Release();
}

void DirectX3D11::SetWindPos(const ChVec2& _pos)
{
	if (!IsInit())return;
	view->SetTopLeftPos(_pos);
}

void DirectX3D11::SetWindSize(const ChVec2& _size)
{
	if (!IsInit())return;
	view->SetSize(_size);
}

void DirectX3D11::DrawStart()
{
	if (!IsInit())return;

	window->SetBackGroundColor(dContext, backColor);
	dsBuffer->ClearDepthBuffer(dContext);
	view->SetDrawData(dContext);
	window->SetDrawData(dContext, dsBuffer->GetDSView());
}

void DirectX3D11::DrawEnd()
{
	if (!IsInit())return;
	if (ChPtr::NullCheck(device))return;

	window->SetDrawData(dContext, dsBuffer->GetDSView());

	// バックバッファをプライマリバッファにコピー//
	window->Draw();
}

void DirectX3D11::DrawEnd(ChD3D11::TextureBase11& _tex)
{
	if (!IsInit())return;
	if (ChPtr::NullCheck(device))return;

	window->SetDrawData(dContext, dsBuffer->GetDSView());
	spriteShader->DrawStart(dContext);
	spriteShader->Draw(_tex, *outSprite);
	spriteShader->DrawEnd();

	// バックバッファをプライマリバッファにコピー//
	window->Draw();
}
