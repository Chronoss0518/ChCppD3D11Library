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

			void SetViewMatrix(const ChLMat& _mat);

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetWorldMatrix(const ChLMat& _mat);

			void SetFrameMatrix(const ChLMat& _mat,unsigned long _num);

			void SetDrwaFlags(const bool _flg, unsigned long _num);

			void SetMoveUV(const ChVec2& _move, unsigned long _num);

			void SetMateDiffuse(const ChVec4& _diffuseCol, unsigned long _num);

			void SetMateSpecularColor(const ChVec3& _specularCol, unsigned long _num);

			void SetMateSpecularPower(const float _specularPow, unsigned long _num);

			void SetMateAmbientColor(const ChVec3& _ambientCol, unsigned long _num);

			void SetBaseTexture(TextureBase11* _tex, unsigned long _num);

			void SetNormalTexture(TextureBase11* _tex);

			void SetDrawData(const ChDrawData& _data);

			void SetModelData(const ChModelData& _data);

			void SetCharaData(const ChFrameData& _data, const bool _flg, unsigned long _num);

			void SetMaterialData(const ChMaterialData& _data, unsigned long _num);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetGSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetShaderDrawData(ID3D11DeviceContext* _dc);

			void SetPSModelData(ID3D11DeviceContext* _dc);

			void SetGSModelData(ID3D11DeviceContext* _dc);

			void SetVSModelData(ID3D11DeviceContext* _dc);

			void SetShaderModelData(ID3D11DeviceContext* _dc);

			void SetPSFrameData(ID3D11DeviceContext* _dc);

			void SetGSFrameData(ID3D11DeviceContext* _dc);

			void SetVSFrameData(ID3D11DeviceContext* _dc);

			void SetShaderFrameData(ID3D11DeviceContext* _dc);

			void SetPSMaterialData(ID3D11DeviceContext* _dc);

			void SetGSMaterialData(ID3D11DeviceContext* _dc);

			void SetVSMaterialData(ID3D11DeviceContext* _dc);

			void SetShaderMaterialData(ID3D11DeviceContext* _dc);

			void SetShaderTexture(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline ChDrawData GetDrawData() { return drawData; }

			inline ChLMat GetProjectionMatrix() { return drawData.proMat; }

			inline ChLMat GetViewMatrix() { return drawData.viewMat; }

			inline ChFrameDatas GetFrameDatas() { return frameData; }

			ChLMat GetWorldMatrix();

			ChLMat GetFrameMatrix(unsigned int _num);

			ChVec2 GetMoveUV(unsigned int _num);

		public://Update Function//

			void UpdateDD(ID3D11DeviceContext* _dc);

			void UpdateMoD(ID3D11DeviceContext* _dc);

			void UpdateFD(ID3D11DeviceContext* _dc);

			void UpdateMaD(ID3D11DeviceContext* _dc);

		private://Member Value

			ChDrawData drawData;
			ConstantBuffer11<ChDrawData> drawBuf;
			bool dUpdateFlg = true;
			ChModelData modelData;
			ConstantBuffer11<ChModelData> modelBuf;
			bool moUpdateFlg = true;
			ChFrameDatas frameData;
			ConstantBuffer11<ChFrameDatas> frameBuf;
			bool fUpdateFlg = true;
			ChMaterialDatas mateData;
			ConstantBuffer11<ChMaterialDatas> mateBuf;
			bool maUpdateFlg = true;

			TextureBase11* baseTex[CH_DMP_MAX_FRAME_COUNT];
			TextureBase11* normalTex = nullptr;

			TextureBase11* defaultBase = nullptr;
			TextureBase11* defaultNormal = nullptr;

		};

	}

}


#endif
