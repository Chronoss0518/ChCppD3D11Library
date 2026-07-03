#pragma once
#ifndef Ch_D3D11_CB_MultiplePolygon_h
#define Ch_D3D11_CB_MultiplePolygon_h

#include"../ChCBBase11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawMultiplePolygon.hlsli"

namespace ChD3D11
{

	class TextureBase11;

	namespace CB
	{
		class CBMultiplePolygon11 final :public CBBase11
		{
		public:

			virtual ~CBMultiplePolygon11() { Release(); }

		public://InitAndRelease//

			void Init(
				ID3D11Device* _device,
				TextureBase11* _defaultBase,
				TextureBase11* _defaultNormal);

			void Release()override;

		public://Set Functions//

			void SetFrameMatrix(const ChLMat& _mat,unsigned int _num);

			void SetWorldMatrix(const ChLMat& _mat, unsigned int _num);

			void SetMoveUV(const ChVec2& _move, unsigned int _num);

			void SetViewMatrix(const ChLMat& _mat);

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetMateDiffuse(const ChVec4& _diffuseCol, unsigned int _num);

			void SetMateSpecularColor(const ChVec3& _specularCol, unsigned int _num);

			void SetMateSpecularPower(const float _specularPow, unsigned int _num);

			void SetMateAmbientColor(const ChVec3& _ambientCol, unsigned int _num);

			void SetBaseTexture(TextureBase11* _tex, unsigned int _num);

			void SetNormalTexture(TextureBase11* _tex, unsigned int _num);

			void SetDrawData(const ChDrawData& _data);

			void SetCharaData(const ChCharaData& _data, unsigned int _num);

			void SetMaterialData(const ChMaterial& _data, unsigned int _num);

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

			inline ChDrawData GetDrawData() { return drawData; }

			inline ChLMat GetProjectionMatrix() { return drawData.proMat; }

			inline ChLMat GetViewMatrix() { return drawData.viewMat; }

			inline ChCharaDatas GetCharaDatas() { return charaData; }

			ChLMat GetWorldMatrix(unsigned int _num);

			ChLMat GetFrameMatrix(unsigned int _num);

			ChVec2 GetMoveUV(unsigned int _num);

		public://Update Function//

			void UpdateDD(ID3D11DeviceContext* _dc);

			void UpdateCD(ID3D11DeviceContext* _dc);

			void UpdateMD(ID3D11DeviceContext* _dc);

		private://Member Value

			ChDrawData drawData;
			ConstantBuffer11<ChDrawData> drawBuf;
			bool dUpdateFlg = true;
			ChCharaDatas charaData;
			ConstantBuffer11<ChCharaDatas> charaBuf;
			bool cUpdateFlg = true;
			ChMaterials mateData;
			ConstantBuffer11<ChMaterials> mateBuf;
			bool mUpdateFlg = true;

			std::vector<TextureBase11*> baseTex;
			std::vector<TextureBase11*> normalTex;

			TextureBase11* defaultBase = nullptr;
			TextureBase11* defaultNormal = nullptr;

		};

	}

}


#endif
