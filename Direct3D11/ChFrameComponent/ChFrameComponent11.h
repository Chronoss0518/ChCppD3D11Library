#ifndef	Ch_D3D11_FrameCom_h
#define	Ch_D3D11_FrameCom_h

#include"../ChCB/ChCBBone/ChCBBone11.h"

namespace ChD3D11
{

	template<typename CharaType>
	class FrameComponent11 :public ChCpp::BaseComponent
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

			IndexBuffer11 indexBuffer;
			VertexBuffer11<Ch3D::SkinMeshVertex<BONE_MAX_NUM>> vertexBuffer;

			std::vector<Ch3D::SkinMeshVertex<BONE_MAX_NUM>> vertexArray;
			std::vector<unsigned long> indexArray;

			ChPtr::Shared<Ch3D::MaterialData<CharaType>> mate;
			std::map<Ch3D::TextureType, ChPtr::Shared<Texture11>>textures;
		};


	public://Create Functions//

		//子オブジェクトすべてを作成する。//
		void Create(ID3D11Device* _device, ChCpp::FrameComponent<CharaType>* _frameComponent, ChCpp::TransformObject<CharaType>& _rootObject);
		
		template<unsigned long _ElementSize>
		static void CreateInputElements(std::array<D3D11_INPUT_ELEMENT_DESC, _ElementSize>& _inputElements)
		{
			if (_ElementSize > 0)
				_inputElements[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };

			if (_ElementSize > 1)
				_inputElements[1] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

			if (_ElementSize > 2)
				_inputElements[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

			if (_ElementSize > 3)
				_inputElements[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

			if (_ElementSize > 4)
				_inputElements[4] = { "NORMAL",  1, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

			if (_ElementSize > 5)
				_inputElements[5] = { "BLENDINDEX",  0, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

			if (_ElementSize > 6)
				_inputElements[6] = { "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

			if (_ElementSize > 7)
				_inputElements[7] = { "BLENDWEIGHT",  1, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

			if (_ElementSize > 8)
				_inputElements[8] = { "BLENDWEIGHT",  2, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

			if (_ElementSize > 9)
				_inputElements[9] = { "BLENDWEIGHT",  3, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

		}

		static void CreateFrameMesh(ID3D11Device* _device, ChPtr::Shared<ChCpp::TransformObject<CharaType>>_model)
		{
			auto&& frameBase = _model->GetComponent<ChCpp::FrameComponent<CharaType>>();

			if (frameBase != nullptr)
			{
				auto com = _model->GetComponent<FrameComponent11<CharaType>>();

				if (com == nullptr)
				{
					com = _model->SetComponent<FrameComponent11<CharaType>>();

					com->Create(_device, frameBase.get(), *_model);
				}

			}

			for (auto&& cbildObj : _model->GetAllChildlen())
			{
				auto child = ChPtr::SharedSafeCast<ChCpp::TransformObject<CharaType>>(cbildObj);

				if (child == nullptr)continue;

				CreateFrameMesh(_device,child);
			}
		}

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
}

#endif
