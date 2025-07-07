#ifndef Ch_D3D11_SS_CircleCullingSprite_h
#define Ch_D3D11_SS_CircleCullingSprite_h

#include"ChSampleSpriteShaderBase11.h"


namespace ChD3D11
{

	class Sprite11;

	namespace Shader
	{

		class CircleCullingSprite11 final :public SampleSpriteShaderBase11
		{
		public:

			virtual ~CircleCullingSprite11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitPixelShader()override;

		public://Set Functions//

			void SetStartDrawDir(const ChVec2& _dir);

			void SetCenterPos(const ChVec2& _pos);
			
			void SetDrawValue(const float& _dir);

		public://Get Functions//

			inline float GetDrawValue() { return circleCullingData.GetDrawValue(); }

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

			CB::CBCircleCulling11 circleCullingData;

		};
	}
}



#endif