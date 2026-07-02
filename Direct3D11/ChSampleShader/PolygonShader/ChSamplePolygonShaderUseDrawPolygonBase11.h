#ifndef Ch_D3D11_SS_ChSamplePolygonShaderUseDrawPolygonBase_h
#define Ch_D3D11_SS_ChSamplePolygonShaderUseDrawPolygonBase_h

#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"
#include"ChSamplePolygonShaderBase11.h"

namespace ChD3D11
{

	class PolygonBoard11;


	namespace Shader
	{

		class SamplePolygonShaderUseDrawPolygonBase11 :public SamplePolygonShaderBase11
		{
		public://Constructor Destructor//

			virtual ~SamplePolygonShaderUseDrawPolygonBase11() { Release(); }

		public://Init And Release//

			virtual void Init(ID3D11Device* _device)override;

			virtual void Release()override;

		public://Set Functions//

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetViewMatrix(const ChLMat& _mat);

			void SetMoveUV(const ChVec2& _move);

			virtual void SetShaderDrawData(ID3D11DeviceContext* _dc);

			virtual void SetShaderCharaData(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline ChVec2 GetMoveUV() { return polyData.GetMoveUV(); }

			inline ChLMat GetViewMatrix() { return polyData.GetViewMatrix(); }

			inline ChLMat GetProjectionMatrix() { return polyData.GetProjectionMatrix(); }

		public://Other Functions//

			virtual void DrawStart(ID3D11DeviceContext* _dc)override;

		protected://Member Value//

			CB::CBPolygon11 polyData;

		};
	}
}



#endif