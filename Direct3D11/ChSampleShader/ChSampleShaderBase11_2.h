#ifndef Ch_D3D11_SSBase_h
#define Ch_D3D11_SSBase_h

#include"../ChTexture/ChTexture11.h"
#include"../ChShaderObject/ChShaderObject11.h"

namespace ChD3D11
{
	class Texture11;
	class TextureBase11;
	class RenderTarget11;

	namespace Shader
	{
		//this class is In VertexShader And PixelShader//
		class ShaderBase11Interface
		{
		protected:

			virtual ~ShaderBase11Interface() { vs.Release(); ps.Release(); }

		protected://Init And Release//

			inline void InitVertexShader(
				ID3D11Device* _device,
				const D3D11_INPUT_ELEMENT_DESC* _decl,
				unsigned long _declNum,
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum)
			{
				if (ChPtr::NullCheck(_device))return;
				vs.Init(_device, _decl, _declNum, _shaderByte, _shaderByteNum);
			}

			inline void InitPixelShader(
				ID3D11Device* _device,
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum)
			{
				if (ChPtr::NullCheck(_device))return;
				ps.Init(_device, _shaderByte, _shaderByteNum);
			}

		protected://Set Functions//

			inline void SetVertexShader(ID3D11DeviceContext* _dc)
			{
				if (ChPtr::NullCheck(_dc))return;
				vs.SetShader(_dc);
			}

			inline void SetPixelShader(ID3D11DeviceContext* _dc)
			{
				if (ChPtr::NullCheck(_dc))return;
				ps.SetShader(_dc);
			}

		private:

			VertexShader11 vs;
			PixelShader11 ps;
		};

		class GShader11Interface
		{
		protected:

			virtual ~GShader11Interface() { gs.Release(); }

		protected://Init And Release//

			inline void InitGeometryShader(
				ID3D11Device* _device,
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum)
			{
				if (ChPtr::NullCheck(_device))return;
				gs.Init(_device, _shaderByte, _shaderByteNum);
			}

		protected://Set Functions//

			inline void SetGeometryShader(ID3D11DeviceContext* _dc)
			{
				if (ChPtr::NullCheck(_dc))return;
				gs.SetShader(_dc);
			}

		private:

			GeometryShader11 gs;
		};

		class HShader11Interface
		{
		protected:

			virtual ~HShader11Interface() { hs.Release(); }

		protected://Init And Release//

			inline void InitHullShader(
				ID3D11Device* _device,
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum)
			{
				if (ChPtr::NullCheck(_device))return;
				hs.Init(_device, _shaderByte, _shaderByteNum);
			}

		protected://Set Functions//

			inline void SetHullShader(ID3D11DeviceContext* _dc)
			{
				if (ChPtr::NullCheck(_dc))return;
				hs.SetShader(_dc);
			}

		private:

			HullShader11 hs;
		};

		class DShader11Interface
		{
		protected:

			virtual ~DShader11Interface() { ds.Release(); }

		protected://Init And Release//

			inline void InitDomainShader(
				ID3D11Device* _device,
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum)
			{
				if (ChPtr::NullCheck(_device))return;
				ds.Init(_device, _shaderByte, _shaderByteNum);
			}

		protected://Set Functions//

			inline void SetDomainShader(ID3D11DeviceContext* _dc)
			{
				if (ChPtr::NullCheck(_dc))return;
				ds.SetShader(_dc);
			}

		private:

			DomainShader11 ds;
		};

		class CShader11Interface
		{
		protected:

			virtual ~CShader11Interface() { cs.Release(); }

		protected://Init And Release//

			inline void InitComputeShader(
				ID3D11Device* _device,
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum)
			{
				if (ChPtr::NullCheck(_device))return;
				cs.Init(_device, _shaderByte, _shaderByteNum);
			}

		protected://Set Functions//

			inline void SetComputeShader(ID3D11DeviceContext* _dc)
			{
				if (ChPtr::NullCheck(_dc))return;
				cs.SetShader(_dc);
			}

		private:

			ComputeShader11 cs;
		};

		class SampleShaderBase11_2
		{
		public:

			virtual ~SampleShaderBase11_2() { Release(); }

		public://Init And Release//

			virtual void Init(
				ID3D11Device* _device,
				size_t _drawMaxCount);

			virtual void Release();

		protected://Create Functions//

			void CreateRasteriser(const D3D11_RASTERIZER_DESC& _desc);

			void CreateBlender(const D3D11_BLEND_DESC& _desc);

			void CreateDepthStencilTester(const D3D11_DEPTH_STENCIL_DESC& _desc);

		protected://Set Functions//

			void SetShaderRasteriser(ID3D11DeviceContext* _dc);

			void SetShaderBlender(ID3D11DeviceContext* _dc, float* _blendFacotr = nullptr, unsigned int _sampleMask = 0xffffffff);

			void SetShaderDefaultBlender(ID3D11DeviceContext* _dc);

			void SetShaderDepthStencilTester(ID3D11DeviceContext* _dc, unsigned int _stencilRef = 0);

			void SetShaderDefaultDepthStencilTester(ID3D11DeviceContext* _dc);

			inline void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY _pt) { primitiveTopology = _pt; }

		protected://Get Functions//

			inline Texture11& GetWhiteTexture() { return whiteTex; }

			ID3D11Device* GetDevice() { return device; }

			ID3D11DeviceContext* GetDC() { return dc; }

			inline size_t maxDrawCount() { return drawMaxCount; }

		private://Get Functions//

			inline static bool& GetShaderNowRunFlg()
			{
				static bool flg = false;
				return flg;
			}

		protected://Is Functions//

			bool IsDraw()const { return drawFlg; }

		public://Update Function//

			virtual void Update(ID3D11DeviceContext* _dc) {};

		public://Other Functions//

			virtual void DrawStart(ID3D11DeviceContext* _dc);

			virtual void DrawEnd();

		private://Member Value//

			ID3D11RasterizerState* rasteriser = nullptr;
			ID3D11DepthStencilState* depthStencilTester = nullptr;
			ID3D11Device* device = nullptr;
			ID3D11DeviceContext* dc = nullptr;

			Texture11 whiteTex;

			D3D_PRIMITIVE_TOPOLOGY primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

			bool drawFlg = false;

			ID3D11BlendState* blender = nullptr;

			size_t drawMaxCount = 0;
		};
	}
}

#endif