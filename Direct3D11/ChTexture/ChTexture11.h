//DirectXTex Library License//
/*

The MIT License (MIT)

Copyright (c) 2011-2021 Microsoft Corp

Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the "Software"), to deal in the Software
without restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef Ch_D3D11_Tex_h
#define Ch_D3D11_Tex_h

#include<D3D11.h>

#include"../../../ChCppBaseLibrary/BasePack/ChStr.h"

struct IWICBitmap;

namespace ChD3D11
{

	class TextureBase11
	{

	public:

		virtual ~TextureBase11();

	public://Init And Release//

		virtual void Release();

	public://Set Functions//

		inline void SetSampler(D3D11_SAMPLER_DESC& _sDesc)
		{
			sDesc = _sDesc;
			sdUpdateFlg = true;
		}

		void SetDrawData(ID3D11DeviceContext* _dc, unsigned int _textureNo);

	public://Get Functions//

		ID3D11ShaderResourceView* GetSRView()
		{
			return texView;
		}

		ID3D11Resource* GetTex()
		{
			return baseTex;
		}

		D3D11_TEXTURE2D_DESC GetTextureDesc();


		D3D11_SAMPLER_DESC GetSamplerDesc()
		{
			return sDesc;
		}

		ChMath::Vector2Base<unsigned int> GetTextureSize();

	public://Is Functionss//

		bool IsTex() { return ChPtr::NotNullCheck(baseTex); }

	protected:

		void Init(ID3D11Device* _device);

		void CreateSRV();

		void InitSampler();

		void UpdateSampler();

		ChVec4 GetBitColor(
			const unsigned int _width,
			const unsigned int _height);

		D3D11_SAMPLER_DESC sDesc;
		bool sdUpdateFlg = true;
		ID3D11SamplerState* sampler = nullptr;

		ID3D11ShaderResourceView* texView = nullptr;

		ID3D11Texture2D* baseTex = nullptr;
		unsigned long textureSize = 0;

		ID3D11Device* device = nullptr;

		std::vector<ChVec4> pixelData;

	};

	class Texture11 :public TextureBase11
	{
	public://Constructer Destructer//

		Texture11() {}

	public://Create Functions//


		void CreateTextureFromShiftJis(
			const std::string& _texPath,
			ID3D11Device* _device)
		{
			CreateTexture(ChStr::GetUTF16FromShiftJis(_texPath), _device);
		}

		void CreateTextureFromShiftJis(const std::string& _texPath)
		{
			if (!D3D11API().IsInit())return;
			ID3D11Device* tmpDevice = D3D11Device();
			CreateTexture(ChStr::GetUTF16FromShiftJis(_texPath), tmpDevice);
		}

		void CreateTextureFromUTF8(
			const std::string& _texPath,
			ID3D11Device* _device)
		{
			CreateTexture(ChStr::GetUTF16FromUTF8(_texPath), _device);
		}

		void CreateTextureFromUTF8(const std::string& _texPath)
		{
			if (!D3D11API().IsInit())return;
			ID3D11Device* tmpDevice = D3D11Device();
			CreateTexture(ChStr::GetUTF16FromUTF8(_texPath), tmpDevice);
		}

#ifdef UNICODE
		void CreateTexture(
			const std::string& _texPath,
			ID3D11Device* _device)
		{
			CreateTexture(ChStr::GetUTF16FromUTF8(_texPath), _device);
		}

		void CreateTexture(const std::string& _texPath)
		{
			if (!D3D11API().IsInit())return;
			ID3D11Device* tmpDevice = D3D11Device();
			CreateTexture(ChStr::GetUTF16FromUTF8(_texPath), tmpDevice);
		}
#else
		void CreateTexture(
			const std::string& _texPath,
			ID3D11Device* _device)
		{
			CreateTexture(ChStr::GetUTF16FromShiftJis(_texPath), _device);
		}

		void CreateTexture(const std::string& _texPath)
		{
			if (!D3D11API().IsInit())return;
			ID3D11Device* tmpDevice = D3D11Device();
			CreateTexture(ChStr::GetUTF16FromShiftJis(_texPath), tmpDevice);
		}
#endif

		void CreateTexture(
			const std::wstring& _texPath,
			ID3D11Device* _device);

		inline void CreateTexture(const std::wstring& _texPath)
		{
			if (!D3D11API().IsInit())return;
			ID3D11Device* tmpDevice = (D3D11Device());
			CreateTexture(_texPath, tmpDevice);
		}

		void CreateColorTexture(
			ID3D11Device* _device,
			const ChVec4& _color,
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			const ChVec4& _color,
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			ID3D11Device* _device,
			const ChVec4* _colorArray,
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			const ChVec4* _colorArray,
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			ID3D11Device* _device,
			IWICBitmap* _bitmap,
			const unsigned int _CPUFlg = 0);

		void CreateColorTexture(
			IWICBitmap* _bitmap,
			const unsigned int _CPUFlg = 0);

	protected:

		D3D11_TEXTURE2D_DESC CreateDESC(
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg);

		ChVec4* SetPixel(const ChVec4* _colorArray, const unsigned long _textureSize);

		ChVec4* SetPixel(const ChVec4& _colorArray, const unsigned long _textureSize);
	};

	class RenderTarget11 :public TextureBase11
	{
	public://InitAndRelease//

		void Release()override;

	public://Create Functions//

		void CreateRenderTarget(
			ID3D11Device* _device,
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

		void CreateRenderTarget(
			const unsigned long _width,
			const unsigned long _height,
			const unsigned int _CPUFlg = 0);

	public://Set Functions//

		void SetBackColor(ID3D11DeviceContext* _dc, const ChVec4& _buckColor);

	public://Get Functions//

		inline ID3D11RenderTargetView* GetRTView()
		{
			return rtView;
		}

	private://Member Values//

		ID3D11RenderTargetView* rtView = nullptr;
	};

	class DepthStencilTexture11 :public TextureBase11
	{
	public://Init And Release//

		void Release()override;

	public://Create Functions//

		void CreateDepthBuffer(
			ID3D11Device* _device,
			const float& _width,
			const float& _height,
			const unsigned int _CPUFlg = 0);

		void CreateDepthBuffer(
			const float& _width,
			const float& _height,
			const unsigned int _CPUFlg = 0);

	public://Other Functions//

		void ClearDepthBuffer(
			ID3D11DeviceContext* _dc,
			const UINT _flgment = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL);

	public://Get Functions//

		ID3D11DepthStencilView* GetDSView() { return dsView; }

	private://Member Values//

		ID3D11DepthStencilView* dsView = nullptr;

	};
}

#endif
