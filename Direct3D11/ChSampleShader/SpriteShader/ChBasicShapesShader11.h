#ifndef Ch_D3D11_SS_BasicShapes_h
#define Ch_D3D11_SS_BasicShapes_h

#include"../ChSampleShaderBase11.h"


namespace ChD3D11
{

	namespace Shader
	{

		class BasicShapesPositionShader11 final :public SampleShaderBase11
		{
		public:

			virtual ~BasicShapesPositionShader11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			//三角形をセットする//
			void InitPositionTri();

			//正方形をセットする//
			void InitPositionSquare();

			//ひし形をセットする//
			void InitPositionRhombus();

			void Release()override;

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public://Set Functions//

			inline void SetAlphaBlendFlg(const bool _flg) { alphaBlendFlg = _flg; }

			inline void SetPositionData(const ChVec2& _position, int _no)
			{
				positionData.SetPosition(_position, _no);
			}

		public://Get Functions//

			inline ChLMat GetSpriteMatrix() { return bsData.GetSpriteMatrix(); }

			inline ChVec4 GetColor() { return bsData.GetColor(); }

		public://Add Functions//

			inline void AddPositionData(const ChVec2& _position)
			{
				positionData.AddPosition(_position);
			}

		public://Pop Functions//

			inline void PopPosition() { positionData.PopPosition(); }

		public://Other Functions//

			//図形の通常描画//
			void Draw(
				Sprite11& _sprite,
				const ChVec4& _baseColor,
				const ChLMat& _mat = ChLMat());

		private://Member Value//

			CB::CBBasicShapes11 bsData;
			CB::CBBasicShapesPosition11 positionData;

			VertexBuffer11<Ch3D::Vertex> vertexBuffer;
			IndexBuffer11 indexBuffer;

			bool alphaBlendFlg = false;

		};

		class BasicShapesCircleShader11 final :public SampleShaderBase11
		{
		public:

			virtual ~BasicShapesCircleShader11()
			{
				Release();
			}

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void InitCenterCircle();

			void Release()override;

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public://Set Functions//

			inline void SetAlphaBlendFlg(const bool _flg) { alphaBlendFlg = _flg; }

			inline void SetCircleData(const ChVec2& _centerPos, float _size, int _no)
			{
				circleData.SetCenterPosition(_centerPos, _no);
				circleData.SetSize(_size, _no);
			}

			inline void SetCircleCenterPosition(const ChVec2& _centerPos, int _no) { circleData.SetCenterPosition(_centerPos, _no); }

			inline void SetCircleCenterSize(float _size, int _no) { circleData.SetSize(_size, _no); }

		public://Get Functions//

			inline ChLMat GetSpriteMatrix() { return bsData.GetSpriteMatrix(); }

			inline ChVec4 GetColor() { return bsData.GetColor(); }

		public://Add Functions//

			inline void AddCircleData(const ChVec2& _centerPos, float _size)
			{
				circleData.AddCircleData(_centerPos, _size);
			}

		public://Pop Functions//

			inline void PopCircleData() { circleData.PopCircleData(); }

		public://Other Functions//

			//図形の通常描画//
			void Draw(
				Sprite11& _sprite,
				const ChVec4& _baseColor,
				const ChLMat& _mat = ChLMat());

		private://Member Value//

			CB::CBBasicShapes11 bsData;
			CB::CBBasicShapesCircle11 circleData;

			VertexBuffer11<Ch3D::Vertex> vertexBuffer;
			IndexBuffer11 indexBuffer;

			bool alphaBlendFlg = false;

		};
	}
}



#endif