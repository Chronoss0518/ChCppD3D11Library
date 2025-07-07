#ifndef Ch_D3D11_SS_BasicHghlight_h
#define Ch_D3D11_SS_BasicHghlight_h

#include"ChSampleSpriteShaderBase11.h"


namespace ChD3D11
{

	class Sprite11;

	namespace Shader
	{

		class BasicHighlightShader11 final :public SampleSpriteShaderBase11
		{
		public:

			virtual ~BasicHighlightShader11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitPixelShader()override;

		public://Set Functions//

			inline void SetBlurPower(const int& _blurPower) { highlightMapData.SetBlurPower(_blurPower); }

			inline void SetGameWindowSize(const ChVec2& _size) { highlightMapData.SetGameWindowSize(_size); }

			inline void SetLiteBlurFlg(const bool _flg) { highlightMapData.SetLiteBlurFlg(_flg); }

			inline void SetBoostPower(const float _boostPower) { highlightMapData.SetBoostPower(_boostPower); }

		private:

			inline void SetAlphaBlendFlg(const bool _flg) { alphaBlendFlg = true; }

		public://Get Functions//

			inline int GetBlurPower() { return highlightMapData.GetBlurPower(); }

			inline ChVec2 GetGameWindowSize() { return highlightMapData.GetGameWindowSize(); }

			inline bool GetLiteBlurFlg() { return highlightMapData.GetLiteBlurFlg(); }

			inline float GetBoostPower() { return highlightMapData.GetBoostPower(); }

		public://Other Functions//

			void DrawStart(ID3D11DeviceContext* _dc)override;

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

			void DrawEnd()override;

		private://Member Value//

			CB::CBHighlight11 highlightMapData;

			ID3D11SamplerState* sampler = nullptr;

		};
	}
}



#endif