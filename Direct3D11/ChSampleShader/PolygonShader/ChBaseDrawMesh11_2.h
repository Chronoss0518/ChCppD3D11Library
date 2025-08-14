#ifndef Ch_D3D11_SS_BaseMesh_h
#define Ch_D3D11_SS_BaseMesh_h

#include"ChSamplePolygonShaderBase11_2.h"

#include"../../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChMesh/ChMesh11.h"

#include"../../ChCB/ChCBBone/ChCBBone11.h"


namespace ChD3D11
{
	namespace Shader
	{
		template<typename CharaType>
		class BaseDrawMesh11_2 final :public SamplePolygonShaderBase11_2
		{
		public://Constructor Destructor//

			virtual ~BaseDrawMesh11_2();

		public://Init And Release//

			void Init(ID3D11Device* _device,
				size_t _drawMaxCount)override;

			void Release()override;

		private:

			void InitVertexShader();

			void InitPixelShader();

		public://Other Functions//

			void DrawStart(ID3D11DeviceContext* _dc)override;

			void Draw(
				Mesh11<CharaType>& _mesh,
				std::vector<ChLMat>& _worldMats);

			void Draw(
				Mesh11<CharaType>& _mesh,
				const ChLMat& _mat = ChLMat());

			void DrawEnd()override;

		private://Other Functions//

			void DrawUpdate(ChCpp::FrameObject<CharaType>& _object);

			void DrawMain(ChCpp::FrameObject<CharaType>& _object);

			void Update(ID3D11DeviceContext* _dc)override;

		private://Member Value//

			CB::CBBone11 boneData;

		};
	}
}

#endif