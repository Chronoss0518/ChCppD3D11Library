#ifndef Ch_D3D11_CB_Light_h
#define Ch_D3D11_CB_Light_h

#include"../ChCBBase11.h"
#include"../../../ShaderHeaderFiles/HLSL/5.0/Light.hlsli"

namespace ChD3D11
{
	namespace CB
	{

		enum class UseColorType:int
		{
			Red,
			Green,
			Blue,
			Alpha
		};

		class CBLight11 final :public CBBase11
		{
		public:

			virtual ~CBLight11() { Release(); }

		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release()override;

		public://Set Functions//

			void SetLightDiffuse(const ChVec3& _dif);

			void SetUseLightFlg(const bool& _flg);

			void SetLightDir(const ChVec3& _dir);

			void SetLightAmbientPow(const float _amb);

			void SetDirectionLightData(const bool _useFlg, const ChVec3& _dif, const ChVec3& _dir, const float _ambPow);

			void SetDirectionLightData(const ChDirectionalLight& _data);

			void SetPLightPos(const ChVec3& _pos, const unsigned long _no = 0);

			void SetPLightLen(const float _len, const unsigned long _no = 0);

			void SetPLightDiffuse(const ChVec3& _dif, const unsigned long _no = 0);

			void SetPLightUseFlg(const bool& _flg, const unsigned long _no = 0);

			void SetPointLightData(const bool _useFlg, const ChVec3& _dif, const ChVec3& _pos, const float _len, const unsigned long _no = 0);

			void SetPointLightData(const ChPointLight& _data, const unsigned long _no = 0);

			void SetCamPos(const ChVec3& _camPos);

			void SetUseColorType(const UseColorType& _colorType);

			void SetLightData(const ChLightData& _ld);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetDrawData(ID3D11DeviceContext* _dc);

			void SetTexture(ID3D11DeviceContext* _dc);

			void SetImportLightPowMap(ChPtr::Shared<TextureBase11>& _lightPowMap)
			{
				if (!*this)return;
				importLightPowMap = _lightPowMap;
			}
		
		public://Get Functions//

			inline ChLightData GetLightData() { return lightDatas; }

			inline ChDirectionalLight GetDirectionalLightData() { return lightDatas.light; }

			inline ChPointLight GetPointLightData(const unsigned long _no)
			{
				if (_no >= LIGHT_PLIGHTCOUNT)return ChPointLight();
				return lightDatas.pLight[_no];
			}

			inline ChVec3 GetCameraPos() { return lightDatas.camPos; }

			inline UseColorType GetColorType() { return static_cast<UseColorType>(lightDatas.colorType); }

		private://Get Functions//

			TextureBase11* GetImportLightPowMap();

		public:

			void ClearImportLightPowMap();

		private:

			void Update(ID3D11DeviceContext* _dc);

		private:

			ChLightData lightDatas;
			ConstantBuffer11<ChLightData> buf;
			bool updateFlg = true;

			Texture11 lightPow;
			ChPtr::Shared<TextureBase11>importLightPowMap;

		};

	}

}

#endif
