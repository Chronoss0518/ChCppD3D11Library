#ifndef Ch_D3D11_CB_BasicShapes_h
#define Ch_D3D11_CB_BasicShapes_h

#include"../ChCBBase11.h"
#include"../../ChSampleShader/SpriteShader/Shader/BasicShapesPosition.hlsli"
#include"../../ChSampleShader/SpriteShader/Shader/BasicShapesCircle.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBBasicShapes11 final :public CBBase11
		{
		public:

			virtual ~CBBasicShapes11() { Release(); }

		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release()override;

		public://Set Functions//

			void SetSpriteMatrix(const ChLMat& _mat);

			void SetColor(const ChVec4& _color);

			void SetBasicShapesData(const BasicShapesData& _data);

			void SetPSBasicShapesData(ID3D11DeviceContext* _dc);

			void SetVSBasicShapesData(ID3D11DeviceContext* _dc);

			void SetShaderBasicShapesData(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline BasicShapesData GetSpriteData() { return bsData; }

			inline ChLMat GetSpriteMatrix() { return bsData.spriteMat; }

			inline ChVec4 GetColor() { return bsData.color; }

		private://Update Functions//

			void UpdateSD(ID3D11DeviceContext* _dc);

		private://Member Values//

			BasicShapesData bsData;
			ConstantBuffer11<BasicShapesData> bsBuf;
			bool bsUpdateFlg = true;

		};

		class CBBasicShapesPosition11 final :public CBBase11
		{
		public://Constructor Destructor//

			virtual ~CBBasicShapesPosition11() { Release(); }

		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release()override;

		public://Set Functions//

			void SetPosition(const ChVec2& _position,uint _no);

			void SetPSBasicShapesPositionData(ID3D11DeviceContext* _dc);

			void SetVSBasicShapesPositionData(ID3D11DeviceContext* _dc);

			void SetShaderBasicShapesPositionData(ID3D11DeviceContext* _dc);
		
		public://Get Functions//

			inline BasicShapesPositionData GetBasicShapesPositionData() { return positionData; }

			inline ChBasicShapesPositions GetPositions() { return positionData.positions; }

			inline int GetUsePositionCount() { return positionData.positions.usePositionCount; }

		public://Add Functions//

			void AddPosition(const ChVec2& _position);

		public://Pop Functions//

			void PopPosition();

		public://Clear Functions//

			void ClearPosition();

		private://Update Functions//

			void UpdateSD(ID3D11DeviceContext* _dc);

		private://Member Values//

			BasicShapesPositionData positionData;
			ConstantBuffer11<BasicShapesPositionData> positionBuf;
			bool updateFlg = true;
		};

		class CBBasicShapesCircle11 final :public CBBase11
		{
		public://Constructor Destructor//

			virtual ~CBBasicShapesCircle11() { Release(); }

		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release()override;

		public://Set Functions//

			void SetCenterPosition(const ChVec2& _centerPos, int _no);

			void SetSize(float _size,int _no);

			void SetPSBasicShapesCircleData(ID3D11DeviceContext* _dc);

			void SetVSBasicShapesCircleData(ID3D11DeviceContext* _dc);

			void SetShaderBasicShapesCircleData(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline BasicShapesCircleData GetSpriteData() { return circleData; }

			inline int GetUseCircleCount() { return circleData.circleDatas.usePositionCount; }

		public://Add Functions//

			void AddCircleData(const ChVec2& _centerPos, float _size);

		public://Pop Functions//

			void PopCircleData();

		public://Clear Functions//

			void ClearCircleData();

		private://Update Functions//

			void UpdateSD(ID3D11DeviceContext* _dc);

		private://Member Values//

			BasicShapesCircleData circleData;
			ConstantBuffer11<BasicShapesCircleData> circleBuf;
			bool updateFlg = true;

		};
	}
}


#endif
