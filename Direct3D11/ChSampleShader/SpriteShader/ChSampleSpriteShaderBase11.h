#ifndef Ch_D3D11_SS_SampleSpriteShaderBase_h
#define Ch_D3D11_SS_SampleSpriteShaderBase_h

#include"../../ChCB/ChCBSprite/ChCBSprite11.h"
#include"../ChSampleShaderBase11.h"


namespace ChD3D11
{
	class Sprite11;

	namespace Shader
	{

		class SampleSpriteShaderBase11 :public SampleShaderBase11
		{
		public://Constructor Destructor//

			virtual ~SampleSpriteShaderBase11(){Release();}

		public://Init And Release//

			virtual void Init(ID3D11Device* _device)override;

			virtual void Release()override;

		protected://Init And Release//

			void InitVertexShader()override;

		public://Set Functions//

			inline void SetAlphaBlendFlg(const bool _flg) { alphaBlendFlg = _flg; }

		public://Get Functions//

			inline ChLMat GetSpriteMatrix() { return spriteData.GetSpriteMatrix(); }

			inline ChVec4 GetBaseColor() { return spriteData.GetBaseColor(); }

		public://Other Functions//

			virtual void DrawStart(ID3D11DeviceContext* _dc)override;

		protected://Member Value//

			CB::CBSprite11 spriteData;

			VertexBuffer11<Ch3D::Vertex> vertexBuffer;
			IndexBuffer11 indexBuffer;

			bool alphaBlendFlg = false;

		};
	}
}



#endif