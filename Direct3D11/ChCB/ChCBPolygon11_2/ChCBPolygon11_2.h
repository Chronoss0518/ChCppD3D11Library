#ifndef Ch_D3D11_CB_Polygon_h
#define Ch_D3D11_CB_Polygon_h

#include"../ChCBBase11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/DrawPolygon2.hlsli"

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

			//_drawMaxCountÇÕChP_MAX_INSTANCE_COUNTÇÊÇËè¨Ç≥Ç¢ïKóvÇ™Ç†ÇÈÅB//
			void Init(
				ID3D11Device* _device,
				TextureBase11* _defaultBase,
				size_t _drawMaxCount);

			void Release()override;

		public://Set Functions//

			void SetFrameMatrix(const ChLMat& _mat, size_t _no);

			void SetWorldMatrix(const ChLMat& _mat, size_t _no);

			void SetMoveUV(const ChVec2& _move, size_t _no);

			void SetViewMatrix(const ChLMat& _mat);

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetMateDiffuse(const ChVec4& _diffuseCol, size_t _no);

			void SetMateSpecularColor(const ChVec3& _specularCol, size_t _no);

			void SetMateSpecularPower(const float _specularPow, size_t _no);

			void SetMateAmbientColor(const ChVec3& _ambientCol, size_t _no);

			inline void SetBaseTexture(TextureBase11* _tex) { baseTex = _tex; }

			void SetDrawData(const ChP_DrawData& _data);

			void SetCharaData(const ChP_CharaData& _data,size_t _no);

			void SetMaterialData(const ChP_Material& _data, size_t _no);

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

			inline ChP_CharaData GetCharaData(size_t _no) { return _no < ChP_MAX_INSTANCE_COUNT ? charaData[_no] : ChP_CharaData(); }

			inline ChLMat GetWorldMatrix(size_t _no) { return _no < ChP_MAX_INSTANCE_COUNT ? charaData[_no].worldMat : ChLMat(); }

			inline ChLMat GetFrameMatrix(size_t _no) { return _no < ChP_MAX_INSTANCE_COUNT ? charaData[_no].frameMatrix : ChLMat(); }

			inline ChVec2 GetMoveUV(size_t _no) { return _no < ChP_MAX_INSTANCE_COUNT ? charaData[_no].moveUV : ChVec2(); }

		public://Update Function//

			void UpdateDD(ID3D11DeviceContext* _dc);

			void UpdateCD(ID3D11DeviceContext* _dc);

			void UpdateMD(ID3D11DeviceContext* _dc);

		private://Member Value

			ChP_DrawData drawData;
			ConstantBuffer11<ChP_DrawData> drawBuf;
			bool dUpdateFlg = true;
			ChP_CharaData* charaData = nullptr;
			ConstantBuffer11<ChP_CharaData> charaBuf;
			bool cUpdateFlg = true;
			ChP_Material* mateData = nullptr;
			ConstantBuffer11<ChP_Material> mateBuf;
			bool mUpdateFlg = true;

			size_t drawMaxCount = 0;

			TextureBase11* baseTex = nullptr;

			TextureBase11* defaultBase = nullptr;
		};

	}

}


#endif
