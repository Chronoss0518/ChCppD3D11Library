#ifndef Ch_D3D11_SS_BasicBlur_h
#define Ch_D3D11_SS_BasicBlur_h

#include"ChSampleSpriteShaderBase11.h"


namespace ChD3D11
{

	class Sprite11;

	namespace Shader
	{

		class BasicBlurShader11 final :public SampleSpriteShaderBase11
		{
		public:

			virtual ~BasicBlurShader11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitPixelShader()override;

		public://Set Functions//

			inline void SetBlurPower(const int& _blurPower) { blurData.SetBlurPower(_blurPower); }

			inline void SetGameWindowSize(const ChVec2& _size) { blurData.SetGameWindowSize(_size); }

			inline void SetLiteBlurFlg(const bool _flg) { blurData.SetLiteBlurFlg(_flg); }

		public://Get Functions//

			inline int GetBlurPower() { return blurData.GetBlurPower(); }

			inline ChVec2 GetGameWindowSize() { return blurData.GetGameWindowSize(); }

			inline bool GetLiteBlurFlg() { return blurData.GetLiteBlurFlg(); }

		public://Other Functions//

			//í èÌï`âÊ//
			void Draw(
				TextureBase11& _tex,
				Sprite11& _sprite,
				const ChLMat& _mat = ChLMat());

			//í èÌï`âÊ//
			void Draw(
				TextureBase11& _tex,
				Sprite11& _sprite,
				const ChVec4& _baseColor,
				const ChLMat& _mat = ChLMat());

		private://Member Value//

			CB::CBBlur11 blurData;

		};
	}
}



#endif