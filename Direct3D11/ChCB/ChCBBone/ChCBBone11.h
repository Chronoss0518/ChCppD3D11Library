#ifndef Ch_D3D11_CB_Bone_h
#define Ch_D3D11_CB_Bone_h

#include"../ChCBBase11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/BoneBlending.hlsli"

namespace ChD3D11
{
	namespace CB
	{
		class CBBone11 final :public CBBase11
		{
		public://Constructor Destructor//

			virtual ~CBBone11() { Release(); }

		public://Init And Release//

			void Init(ID3D11Device* _device);

			void Release()override;

		public://Set Functions//

			void SetBoneMatrix(const ChLMat& _offsetMat, const ChLMat& _mat,const unsigned long _no);

			void SetPSDrawData(ID3D11DeviceContext* _dc);

			void SetVSDrawData(ID3D11DeviceContext* _dc);

			void SetDrawData(ID3D11DeviceContext* _dc);

		public://Get Functions//



		private://Update Functions

			void Update(ID3D11DeviceContext* _dc);

		private://Member Values//

			ChBoneData bone;
			ConstantBuffer11<ChBoneData> buf;
			bool updateFlg = true;


		};

	}

}


#endif
