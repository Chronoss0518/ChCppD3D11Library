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

		class SampleShaderBase11:public ChCp::Initializer
		{
		public:

			virtual ~SampleShaderBase11() { Release(); }

		public://Init And Release//

			virtual void Init(ID3D11Device* _device);

			virtual void Release();

		protected://Init And Release//

			virtual void InitVertexShader() = 0;

			virtual void InitPixelShader() = 0;
			
			virtual void InitGeometryShader() {};

			virtual void InitHullShader() {};

			virtual void InitDomainShader() {};

			virtual void InitComputeShader() {};

		protected://Create Shader Functions//

			void CreateVertexShader(
				const D3D11_INPUT_ELEMENT_DESC* _decl,
				unsigned long _declNum,
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

			void CreatePixelShader(
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

			void CreateGeometryShader(
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

			void CreateHullShader(
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

			void CreateDomainShader(
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

			void CreateComputeShader(
				const unsigned char* _shaderByte,
				unsigned long _shaderByteNum);

		protected://Create Functions//

			void CreateRasteriser(const D3D11_RASTERIZER_DESC& _desc);

			void CreateBlender(const D3D11_BLEND_DESC& _desc);

			void CreateDepthStencilTester(const D3D11_DEPTH_STENCIL_DESC& _desc);

		public://Set Functions//

			void SetShader(ID3D11DeviceContext* _dc);

		protected://Set Functions//

			void SetShaderRasteriser(ID3D11DeviceContext* _dc);

			void SetShaderBlender(ID3D11DeviceContext* _dc,float* _blendFacotr = nullptr, unsigned int _sampleMask = 0xffffffff);

			void SetShaderDefaultBlender(ID3D11DeviceContext* _dc);

			void SetShaderDepthStencilTester(ID3D11DeviceContext* _dc, unsigned int _stencilRef = 0);

			void SetShaderDefaultDepthStencilTester(ID3D11DeviceContext* _dc);

			inline void SetPrimitiveTopology(const D3D_PRIMITIVE_TOPOLOGY _pt) { primitiveTopology = _pt; }

		protected://Get Functions//

			inline Texture11& GetWhiteTexture() { return whiteTex; }

			inline Texture11& GetNormalTexture() { return normalTex; }

			ID3D11Device* GetDevice() { return device; }

			ID3D11DeviceContext* GetDC() { return dc; }

		private://Get Functions//

			inline static bool& GetShaderNowRunFlg()
			{
				static bool flg;
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

			VertexShader11 vs;
			GeometryShader11 gs;
			HullShader11 hs;
			DomainShader11 ds;
			PixelShader11 ps;
			ComputeShader11 cs;

			Texture11 whiteTex;
			Texture11 normalTex;

			D3D_PRIMITIVE_TOPOLOGY primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

			bool drawFlg = false;

			ID3D11BlendState* blender = nullptr;
		};
	}
}

#endif