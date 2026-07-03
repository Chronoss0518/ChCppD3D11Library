#ifndef Ch_D3D11_SS_MultipleMesh_h
#define Ch_D3D11_SS_MultipleMesh_h

#include"ChSamplePolygonShaderBase11.h"

#include"../../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"

#include"../../ChTexture/ChTexture11.h"

#include"../../ChCB/ChCBMultiplePolygon/ChCBMultiplePolygon11.h"


namespace ChD3D11
{
	namespace Shader
	{
		template<typename CharaType>
		class BasicDrawMultipleMesh11 final :public SamplePolygonShaderBase11
		{
		public:

			struct UseVertexs : public Ch3D::MeshVertex
			{
				int frameNo = 0;
			};

			class MeshComponent :public ChCpp::BaseComponent
			{
			public:

				VertexBuffer11<UseVertexs> vertexBuffer;
				IndexBuffer11 indexBuffer;

				unsigned long indexNum = 0;
			};

			class FrameComponent :public ChCpp::BaseComponent
			{
			public:

				struct PrimitiveData
				{
					unsigned long frameNo = 1;
					bool drawFlg = true;

					ChPtr::Shared<Ch3D::MaterialData<CharaType>> mate;
					std::map<Ch3D::TextureType, ChPtr::Shared<Texture11>>textures;
				};

			public:

				ChPtr::Shared<ChCpp::FrameComponent<CharaType>> frameCom;

				std::vector<ChPtr::Shared<PrimitiveData>>primitives;
			};

		public://Constructor Destructor//

			virtual ~BasicDrawMultipleMesh11();

		public://Init And Release//

			void Init(ID3D11Device* _device)override;

			void Release()override;

		protected://Init And Release//

			void InitVertexShader()override;

			void InitGeometryShader()override;

			void InitPixelShader()override;

		public:

			void CreateFrameMesh(ChPtr::Shared<ChCpp::FrameObject<CharaType>>_model);

		private:

			void CreateFrameMesh(
				ChPtr::Shared<ChCpp::FrameObject<CharaType>>_model,
				std::vector<UseVertexs>& _vertexs,
				std::vector<unsigned long>& _indexs,
				unsigned long _maxFrameNo);

			void CreateFrameData(
				ChPtr::Shared<ChCpp::FrameObject<CharaType>>_model,
				std::vector<UseVertexs>& _vertexs,
				std::vector<unsigned long>& _indexs,
				unsigned long _maxFrameNo);

		public://Set Functions//

			void SetProjectionMatrix(const ChLMat& _mat);

			void SetViewMatrix(const ChLMat& _mat);

			void SetMoveUV(const ChVec2& _move, unsigned int _num);

			virtual void SetShaderDrawData(ID3D11DeviceContext* _dc);

			virtual void SetShaderModelData(ID3D11DeviceContext* _dc);

			virtual void SetShaderFrameData(ID3D11DeviceContext* _dc);

		public://Get Functions//

			inline ChVec2 GetMoveUV(unsigned int _num) { return multiplePolygon.GetMoveUV(_num); }

			inline ChLMat GetViewMatrix() { return multiplePolygon.GetViewMatrix(); }

			inline ChLMat GetProjectionMatrix() { return multiplePolygon.GetProjectionMatrix(); }

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
			
			CB::CBMultiplePolygon11 multiplePolygon;
		};
	}
}

#endif