#ifndef Ch_D3D11_CB_Polygon_h
#define Ch_D3D11_CB_Polygon_h

#include"../ChCBBase11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawPolygon.hlsli"

namespace ChD3D11
{

	class TextureBase11;

	namespace CB
	{
		class CBPolygon11 final :public CBBase11
		{
		public:

			virtual ~CBPolygon11() { Release(); }

		public://InitAndRelease//

			void Init(
				ID3D11Device* _device,
				TextureBase11* _defaultBase, 
				TextureBase11* _defaultNormal);

			void Release()override;

		public://Set Functions//

			void SetFrameMatrix(const ChLMat& _mat);

			void SetWorldMatrix(const ChLMat& _mat);

			void SetMoveUV(const ChVec2& _move);

			void SetViewMatrix(const ChLMat& _mat);

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetMateDiffuse(const ChVec4& _diffuseCol);

			void SetMateSpecularColor(const ChVec3& _specularCol);

			void SetMateSpecularPower(const float _specularPow);

			void SetMateAmbientColor(const ChVec3& _ambientCol);

			inline void SetBaseTexture(TextureBase11* _tex) { baseTex = _tex; }

			inline void SetNormalTexture(TextureBase11* _tex) { normalTex = _tex; }

			void SetDrawData(const ChP_DrawData& _data);

			void SetCharaData(const ChP_CharaData& _data);

			void SetMaterialData(const ChP_Material& _data);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetShaderDrawData(ID3D11DeviceContext* _dc);

			void SetPSCharaData(ID3D11DeviceContext* _dc);

			void SetVSCharaData(ID3D11DeviceContext* _dc);

			void SetShaderCharaData(ID3D11DeviceContext* _dc);

			void SetPSMaterialData(ID3D11DeviceContext* _dc);

			void SetVSMaterialData(ID3D11DeviceContext* _dc);

			void SetShaderMaterialData(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline ChP_DrawData GetDrawData() { return drawData; }

			inline ChLMat GetProjectionMatrix() { return drawData.proMat; }

			inline ChLMat GetViewMatrix() { return drawData.viewMat; }

			inline ChP_CharaData GetCharaData() { return charaData; }

			inline ChLMat GetWorldMatrix() { return charaData.worldMat; }

			inline ChLMat GetFrameMatrix() { return charaData.frameMatrix; }

			inline ChVec2 GetMoveUV() { return charaData.moveUV; }

		public://Update Function//

			void UpdateDD(ID3D11DeviceContext* _dc);

			void UpdateCD(ID3D11DeviceContext* _dc);

			void UpdateMD(ID3D11DeviceContext* _dc);

		private://Member Value

			ChP_DrawData drawData;
			ConstantBuffer11<ChP_DrawData> drawBuf;
			bool dUpdateFlg = true;
			ChP_CharaData charaData;
			ConstantBuffer11<ChP_CharaData> charaBuf;
			bool cUpdateFlg = true;
			ChP_Material mateData;
			ConstantBuffer11<ChP_Material> mateBuf;
			bool mUpdateFlg = true;

			TextureBase11* baseTex = nullptr;
			TextureBase11* normalTex = nullptr;

			TextureBase11* defaultBase = nullptr;
			TextureBase11* defaultNormal = nullptr;

		};

	}

}


#endif
