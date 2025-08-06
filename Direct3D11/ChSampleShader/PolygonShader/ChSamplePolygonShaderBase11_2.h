#ifndef Ch_D3D11_SS_SamplePolygonShaderBase_h
#define Ch_D3D11_SS_SamplePolygonShaderBase_h

#include"../../ChCB/ChCBPolygon11_2/ChCBPolygon11_2.h"
#include"../ChSampleShaderBase11_2.h"

namespace ChD3D11
{

	class PolygonBoard11;


	namespace Shader
	{

		class SamplePolygonShaderBase11_2 :
			public SampleShaderBase11_2,
			public ShaderBase11Interface
		{
		public://Constructor Destructor//

			virtual ~SamplePolygonShaderBase11_2() { Release(); }

		public://Init And Release//

			virtual void Init(
				ID3D11Device* _device,
				size_t _drawMaxCount)override;

			virtual void Release()override;

		public://Set Functions//

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetViewMatrix(const ChLMat& _mat);

			void SetMoveUV(const ChVec2& _move, size_t _no);

			void SetFillMode(const D3D11_FILL_MODE _fill);

			void SetCullMode(const D3D11_CULL_MODE _cull);

			inline void SetAlphaBlendFlg(const bool _flg) { alphaBlendFlg = _flg; }

			virtual void SetShaderDrawData(ID3D11DeviceContext* _dc);

			virtual void SetShaderCharaData(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline D3D11_FILL_MODE GetFillMode() { return fill; }

			inline D3D11_CULL_MODE GetCullMode() { return cull; }

			inline ChVec2 GetMoveUV(size_t _no = 0) { return polyData.GetMoveUV(_no); }

			inline ChLMat GetViewMatrix() { return polyData.GetViewMatrix(); }

			inline ChLMat GetProjectionMatrix() { return polyData.GetProjectionMatrix(); }

		public://Other Functions//

			virtual void DrawStart(ID3D11DeviceContext* _dc)override;

		protected://Update Functions

			virtual void Update(ID3D11DeviceContext* _dc)override;

		protected://Member Value//

			CB::CBPolygon11 polyData;

			D3D11_FILL_MODE fill = D3D11_FILL_MODE::D3D11_FILL_SOLID;
			D3D11_CULL_MODE cull = D3D11_CULL_MODE::D3D11_CULL_NONE;
			bool updateFlg = true;

			bool alphaBlendFlg = false;

			RenderTarget11* setHighLightMapRT = nullptr;
		};
	}
}



#endif