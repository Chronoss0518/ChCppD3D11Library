#ifndef Ch_D3D11_CB_Blur_h
#define Ch_D3D11_CB_Blur_h

#include"../ChCBBase11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/Blur.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBBlur11 final :public CBBase11
		{
		public://Constructor Destructor//

			virtual ~CBBlur11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release()override;

		public://Set Functions//

			void SetGameWindowSize(const ChVec2& _size);

			void SetBlurPower(const int& _power);

			void SetLiteBlurFlg(const bool _flg);

			void SetBlurData(const ChS_Blur& _data);

			void SetPSSpriteData(ID3D11DeviceContext* _dc);

			void SetVSSpriteData(ID3D11DeviceContext* _dc);

			void SetShaderSpriteData(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline ChS_Blur GetBlurData() { return blurData; }

			inline ChVec2 GetGameWindowSize() { return blurData.windowSize; }

			inline int GetBlurPower() { return blurData.blurPower; }

			inline bool GetLiteBlurFlg() { return blurData.liteBlurFlg == 1; }

		private://Update Functions//

			void UpdateSD(ID3D11DeviceContext* _dc);

		private://Member Values//

			ChS_Blur blurData;
			ConstantBuffer11<ChS_Blur> blurBuf;
			bool updateFlg = true;

		};

	}

}


#endif
