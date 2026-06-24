#ifndef Ch_D3D11_SS_BaseMesh_h
#define Ch_D3D11_SS_BaseMesh_h

#include"ChSamplePolygonShaderBase11.h"

#include"../../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChMesh/ChMesh11.h"

#include"../../ChCB/ChCBBone/ChCBBone11.h"


namespace ChD3D11
{
	namespace Shader
	{
		template<typename CharaType>
		class BaseDrawMesh11 final :public SamplePolygonShaderBase11
		{
		public:

			struct TargetBoneData11
			{
				ChPtr::Shared<ChCpp::TargetBoneData<CharaType>> boneData;
				ChPtr::Shared<ChCpp::FrameObject<CharaType>>targetObject;
			};

			struct DrawPrimitiveData11
			{

				~DrawPrimitiveData11();

				ChLMat drawMat;
				IndexBuffer11 indexBuffer;
				VertexBuffer11<Ch3D::SkinMeshVertex<BONE_MAX_NUM>> vertexBuffer;

				std::vector<Ch3D::SkinMeshVertex<BONE_MAX_NUM>> vertexArray;
				std::vector<unsigned long> indexArray;

				ChPtr::Shared<Ch3D::MaterialData<CharaType>> mate;
				std::map<Ch3D::TextureType, ChPtr::Shared<Texture11>>textures;
			};

			class FrameComponent11 :public ChCpp::BaseComponent
			{
			public://Create Functions//

				//子オブジェクトすべてを作成する。//
				void Create(ID3D11Device* _device, ChCpp::FrameComponent<CharaType>* _frameComponent, ChCpp::TransformObject<CharaType>& _rootObject);

			public://Set Functions//

				void SetBoneData(CB::CBBone11& _bone);

				void SetPrimitives(ChPtr::Shared<DrawPrimitiveData11> _primitive)
				{
					primitives.push_back(_primitive);
				}

				std::vector<ChPtr::Shared<DrawPrimitiveData11>>& GetPrimitives()
				{
					return primitives;
				}

				ChCpp::FrameComponent<CharaType>* GetFrameCom() { return frameCom; }

			private:
				ChCpp::FrameComponent<CharaType>* frameCom = nullptr;
				ChLMat boneLMats[16];

				std::vector<ChPtr::Shared<DrawPrimitiveData11>>primitives;
				std::vector<ChPtr::Shared<TargetBoneData11>>boneList;
			};

		public://Constructor Destructor//

			virtual ~BaseDrawMesh11();

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitVertexShader()override;

			void InitPixelShader()override;

		public:

			void AddFrameComponent11(ChPtr::Shared<ChCpp::TransformObject<CharaType>>_model);

		public://Other Functions//

			void DrawStart(ID3D11DeviceContext* _dc)override;

			void Draw(
				ChCpp::FrameObject<CharaType>& _mesh,
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