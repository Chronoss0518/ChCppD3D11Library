#ifndef Ch_D3D11_Model_h
#define Ch_D3D11_Model_h

#include"../../../ChCppBaseLibrary/CPP/ChBaseObject/ChBaseComponent.h"
#include"../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"
#include"../ChShaderStructures11.h"

#include"../ChTexture/ChTexture11.h"

#include"../../../ChCppBaseLibrary/CPP/ChBaseObject/ChBaseObject.h"
#include"../ChCB/ChCBBone/ChCBBone11.h"

#include<string>
#include<vector>
#include<map>

namespace ChD3D11
{

	class Texture11;

	template<typename CharaType>
	class Mesh11 : public ChCpp::ModelObject<CharaType>
	{
	public://Init And Release//

		void Init(ID3D11Device* _device);

		void Init()override;

		void Release()override;

	public://Create Functions//

		void Create()override;

	protected://Create Functions//

		void CreateFrames();

	public://Get Functions//

		inline ID3D11Device* GetDevice() { return device; }

	private:

		ID3D11Device* device = nullptr;
	};


	template<typename CharaType>
	struct TargetBoneData11
	{
		ChPtr::Shared<ChCpp::TargetBoneData<CharaType>> boneData;
		ChPtr::Shared<ChCpp::FrameObject<CharaType>>targetObject;
	};

	template<typename CharaType>
	struct  DrawPrimitiveData11
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

	template<typename CharaType>
	class FrameComponent11 :public ChCpp::BaseComponent
	{
	public://Create Functions//

		//子オブジェクトすべてを作成する。//
		void CreateAll(ID3D11Device* _device, Mesh11<CharaType>& _rootObject);

	public://Set Functions//

		void SetBoneData(CB::CBBone11& _bone);

		void SetPrimitives(ChPtr::Shared<DrawPrimitiveData11<CharaType>> _primitive)
		{
			primitives.push_back(_primitive);
		}

		std::vector<ChPtr::Shared<DrawPrimitiveData11<CharaType>>>& GetPrimitives()
		{
			return primitives;
		}

		ChCpp::FrameComponent<CharaType>* GetFrameCom() { return frameCom; }

	private:
		ChCpp::FrameComponent<CharaType>* frameCom = nullptr;
		ChLMat boneLMats[16];

		std::vector<ChPtr::Shared<DrawPrimitiveData11<CharaType>>>primitives;
		std::vector<ChPtr::Shared<TargetBoneData11<CharaType>>>boneList;
	};
}

#endif