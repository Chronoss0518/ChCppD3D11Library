#ifndef Ch_D3D11_SS_BasicOLM_h
#define Ch_D3D11_SS_BasicOLM_h

#include"ChSamplePolygonShaderBase11.h"

#include"../../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChMesh/ChMesh11.h"

#include"../../ChCB/ChCBBone/ChCBBone11.h"
#include"../../ChCB/ChCBOutLine/ChCBOutLine11.h"


namespace ChD3D11
{
	namespace Shader
	{
		template<typename CharaType>
		class BasicOutLineMesh11 final :public SamplePolygonShaderBase11
		{
		public://Constructor Destructor//

			virtual ~BasicOutLineMesh11();

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public:

			void SetOutLineWidth(const float _width);

			void SetOutLineColor(const ChVec4& _color);

		public:

			float GetOutLineWidth();

			ChVec4 GetOutLineColor();

		public://Other Functions//

			void DrawStart(ID3D11DeviceContext* _dc)override;

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
			CB::CBOutLine11 outLineData;
		};
	}
}

#endif