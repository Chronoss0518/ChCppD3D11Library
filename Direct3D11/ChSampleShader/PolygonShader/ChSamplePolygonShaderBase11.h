#ifndef Ch_D3D11_SS_SamplePolygonShaderBase_h
#define Ch_D3D11_SS_SamplePolygonShaderBase_h

#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"
#include"../ChSampleShaderBase11.h"

namespace ChD3D11
{

	class PolygonBoard11;


	namespace Shader
	{

		class SamplePolygonShaderBase11 :public SampleShaderBase11
		{
		public://Constructor Destructor//

			virtual ~SamplePolygonShaderBase11() { Release(); }

		public://Init And Release//

			virtual void Init(ID3D11Device* _device)override;

			virtual void Release()override;

		public://Set Functions//

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetViewMatrix(const ChLMat& _mat);

			void SetMoveUV(const ChVec2& _move);

			void SetFillMode(const D3D11_FILL_MODE _fill);

			void SetCullMode(const D3D11_CULL_MODE _cull);

			inline void SetAlphaBlendFlg(const bool _flg) { alphaBlendFlg = _flg; }

			virtual void SetShaderDrawData(ID3D11DeviceContext* _dc);

			virtual void SetShaderCharaData(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline D3D11_FILL_MODE GetFillMode() { return fill; }

			inline D3D11_CULL_MODE GetCullMode() { return cull; }

			inline ChVec2 GetMoveUV() { return polyData.GetMoveUV(); }

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