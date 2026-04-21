#ifndef Ch_D3D11_CB_OutLine_h
#define Ch_D3D11_CB_OutLine_h

#include"../ChCBBase11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/OutLine.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBOutLine11 final :public CBBase11
		{
		public://Constructor Destructor//

			virtual ~CBOutLine11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release()override;

		public://Set Functions//

			void SetWidth(const float _width);

			void SetOutLineColor(const ChVec4& _color);

			void SetOutLineData(const ChOutLineData& _data);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetShaderDrawData(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline ChOutLineData GetOutLineData() { return outlineData; }

			inline float GetWidth() { return outlineData.width; }

			inline ChVec4 GetOutLineColor() { return outlineData.outlineColor; }

		private://Update Functions//

			void UpdateSD(ID3D11DeviceContext* _dc);

		private://Member Values//

			ChOutLineData outlineData;
			ConstantBuffer11<ChOutLineData> outlineBuf;
			bool updateFlg = true;

		};

	}

}


#endif
