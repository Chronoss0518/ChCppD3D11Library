
#ifndef Ch_D3D11_DXCo_h
#define Ch_D3D11_DXCo_h

#include"../ChShaderObject/ChShaderObject11.h"
#include"../ChShaderParts/ChShaderParts11.h"
#include"../ChSampleShader/SpriteShader/ChBaseDrawSprite11.h"
#include"../ChSprite/ChSprite11.h"
#include"../ChTexture/ChTexture11.h"

namespace ChD3D11
{

	//Direct3D11を利用するために作られたクラス//
	class DirectX3D11 final :public ChCp::Initializer
	{
	public:

		virtual ~DirectX3D11() { Release(); }

	public://Init and Release//

		void Init(
			HWND _hWnd, 
			const bool _fullScreenFlg, 
			const unsigned long _scrW,
			const unsigned long _scrH);

		/*
		void Init(
			ChWin::WindObject& _windObject,
			const bool _fullScreenFlg);

		*/

		virtual void Release();

	public://Set Functions//

		inline void SetBackColor(const ChVec4& _color)
		{
			if (!*this)return;
			backColor = _color;
		}

		inline void SetWindPos(const ChVec2& _pos)
		{
			if (!*this)return;
			view.SetTopLeftPos(_pos);
		}

		inline void SetWindSize(const ChVec2& _size)
		{
			if (!*this)return;
			view.SetSize(_size);
		}

	public://Get Functions//

		//Direct3D11をつかさどるデバイスの取得//
		inline ID3D11Device* const GetDevice() { return device; }

		//描画をつかさどるデバイスの取得//
		inline ID3D11DeviceContext* const GetDC() { return dContext; }

		inline IDXGISwapChain* const GetSC() { return scWindow; }

		inline IDXGISurface* const GetSurface() { return surface; }

		inline unsigned long GetCreateDeviceWitdh() { return createDeviceWitdh; }

		inline unsigned long GetCreateDeviceHeight() { return createDeviceHeight; }

		inline ChMath::Vector2Base<unsigned long>GetCreateDeviceSizeToChVector2()
		{
			ChMath::Vector2Base<unsigned long> res;
			res.w = createDeviceWitdh;
			res.h = createDeviceHeight;
			return res;
		}

	public://Is Functions//

		//デバイスが存在するかしないかの確認//
		inline bool IsInstanse()
		{
			if (ChPtr::NullCheck(device))return false;
			if (ChPtr::NullCheck(dContext))return false;
			if (ChPtr::NullCheck(scWindow))return false;
			return true;
		}

	public:

		//描画開始前に呼ぶ関数//
		void DrawStart();

		//すべての描画終了時に呼ぶ関数//
		void DrawEnd();

		//すべての描画終了時に呼ぶ関数//
		void DrawEnd(ChD3D11::TextureBase11& _tex);

	protected://Create Fucntions// 

		void CreateDevice(
			HWND _hWnd,
			const unsigned long _scrW,
			const unsigned long _scrH);

	protected://Member Value//

		//基本オブジェクトをつかさどるデバイス//
		ID3D11Device* device = nullptr;

		//描画用デバイス//
		ID3D11DeviceContext* dContext = nullptr;

		//保持するWindowデータ//
		IDXGISwapChain* scWindow = nullptr;

		//Direct2Dとの互換性を持たせるためのデータ//
		IDXGISurface* surface = nullptr;

		//実際に描画するためのダブルバッファ//
		ID3D11RenderTargetView* renderTarget = nullptr;

		unsigned long createDeviceWitdh = 0;
		unsigned long createDeviceHeight = 0;


		Sprite11 outSprite;

		Shader::BaseDrawSprite11 spriteShader;

		//DepthStencilBuffer用//
		DepthStencilTexture11 dsBuffer;

		ShaderParts::ViewPort view;

		//背景色//
		ChVec4 backColor = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);
		ShaderParts::DrawWindow window;
	};

	inline DirectX3D11& D3D11API()
	{
		static DirectX3D11 ins;
		return ins;
	}

	inline ID3D11Device* D3D11Device()
	{
		return D3D11API().GetDevice();
	};

	inline ID3D11DeviceContext* D3D11DC()
	{
		return D3D11API().GetDC();
	};
}

#endif