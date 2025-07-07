#ifndef Ch_D3D11_CB_CircleCulling_h
#define Ch_D3D11_CB_CircleCulling_h

#include"../ChCBBase11.h"
#include"../../../ShaderHeaderFiles/HLSL/5.0/CircleCulling.hlsli"

namespace ChD3D11
{
	namespace CB
	{

		class CBCircleCulling11 final :public CBBase11
		{
		public://Constructor Destructor//

			virtual ~CBCircleCulling11() { Release(); }

		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release()override;

		public://Set Functions//

			void SetDrawStartDir(const ChVec2& _drawStartDir);
			
			void SetCenterPos(const ChVec2& _dirStartPos);

			void SetDrawValue(const float _drawValue);

			void SetDrawData(ID3D11DeviceContext* _dc);

		public://Get Functions//

			float GetDrawValue();

		private://Update Functions//

			void Update(ID3D11DeviceContext* _dc);

		private://Member Value//

			ChCircleCullingData data;
			ConstantBuffer11<ChCircleCullingData> buf;
			bool updateFlg = true;


		};

	}

}


#endif
