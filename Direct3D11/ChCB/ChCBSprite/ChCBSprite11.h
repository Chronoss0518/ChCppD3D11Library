#ifndef Ch_D3D11_CB_Sprite_h
#define Ch_D3D11_CB_Sprite_h

#include"../ChCBBase11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawSprite.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBSprite11 final :public CBBase11
		{
		public:

			virtual ~CBSprite11() { Release(); }

		public://Init And Release//

			void Init(
				ID3D11Device* _device,
				TextureBase11* _defaultBase);

			void Release()override;

		public://Set Functions//

			void SetSpriteMatrix(const ChLMat& _mat);

			void SetBaseColor(const ChVec4& _color);

			inline void SetBaseTexture(TextureBase11* _tex) { baseTex = _tex; }

			void SetSpriteData(const ChSpriteData& _data);

			void SetPSSpriteData(ID3D11DeviceContext* _dc);

			void SetVSSpriteData(ID3D11DeviceContext* _dc);

			void SetShaderSpriteData(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline ChSpriteData GetSpriteData() { return spData; }

			inline ChLMat GetSpriteMatrix() { return spData.spriteMat; }

			inline ChVec4 GetBaseColor() { return spData.baseColor; }

		private://Update Functions

			void UpdateSD(ID3D11DeviceContext* _dc);

		private://Member Value//

			ChSpriteData spData;
			ConstantBuffer11<ChSpriteData> spBuf;
			bool sUpdateFlg = true;

			TextureBase11* baseTex = nullptr;
			TextureBase11* defaultBase = nullptr;

		};

	}

}


#endif
