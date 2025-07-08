
#include<Windows.h>
#include"../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"

#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChDirectX11Controller/ChDirectX11Controller.h"
#include"../ChTexture/ChTexture11.h"
#include"ChMesh11.h"

using namespace Ch3D;
using namespace ChCpp;
using namespace ChD3D11;

///////////////////////////////////////////////////////////////////////////////////////
//ChMesh11 Method
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
ChD3D11::DrawPrimitiveData11<CharaType>::~DrawPrimitiveData11()
{
	vertexBuffer.Release();
	indexBuffer.Release();

}

template<typename CharaType>
void ChD3D11::FrameComponent11<CharaType>::CreateAll(ID3D11Device* _device, Mesh11<CharaType>& _rootObject)
{
	if (ChPtr::NullCheck(_device))return;

	auto&& frameBase = LookObj()->GetComponent<ChCpp::FrameComponent<CharaType>>();

	if (frameBase != nullptr)
	{
		frameCom = frameBase.get();

		for (auto&& material : frameBase->materialList)
		{
			auto&& primitive11 = ChPtr::Make_S<DrawPrimitiveData11<CharaType>>();
			primitive11->mate = material;

			for (unsigned char i = 0; i < ChStd::EnumCast(Ch3D::TextureType::None); i++)
			{
				Ch3D::TextureType type = static_cast<Ch3D::TextureType>(i);

				auto&& texPath = material->textures.find(type);
				if (texPath == material->textures.end())continue;
				if ((*texPath).second.empty())continue;

				auto texture = ChPtr::Make_S<Texture11>();
				texture->CreateTexture((*texPath).second, _device);

				if (!texture->IsTex())texture = nullptr;

				primitive11->textures[type] = texture;
			}

			primitives.push_back(primitive11);
		}

		for (auto&& primitive : frameBase->primitives)
		{
			auto&& primitive11 = primitives[primitive->mateNo];

			size_t firstIndex = primitive11->vertexArray.size();
			size_t indexCount = 0;

			for (auto&& vertex : primitive->vertexData)
			{
				size_t vertexNo = vertex->vertexNo;

				auto&& tmpVertex = *frameBase->vertexList[vertexNo];

				Ch3D::SkinMeshVertex<16> mVertex;
				Ch3D::SetPosition(&mVertex, tmpVertex.pos);
				Ch3D::SetUV(&mVertex, vertex->uv);
				Ch3D::SetColor(&mVertex, tmpVertex.color);
				Ch3D::SetNormal(&mVertex, tmpVertex.normal);
				Ch3D::SetFaceNormal(&mVertex, primitive->faceNormal);
				mVertex.boneNum = static_cast<unsigned long>(tmpVertex.blendPow.size());
				for (size_t i = 0; i < mVertex.boneNum; i++)
				{
					mVertex.blendPows[i] = tmpVertex.blendPow[i];
				}

				primitive11->vertexArray.push_back(mVertex);

				indexCount++;
			}

			for (unsigned long i = 1; i < indexCount - 1; i++)
			{
				primitive11->indexArray.push_back(static_cast<unsigned long>(firstIndex));
				primitive11->indexArray.push_back(static_cast<unsigned long>(firstIndex + i));
				primitive11->indexArray.push_back(static_cast<unsigned long>(firstIndex + i + 1));
			}
		}

		for (auto&& prim : primitives)
		{

			if (prim->indexArray.empty())continue;
			if (prim->vertexArray.empty())continue;

			prim->indexBuffer.CreateBuffer(
				_device,
				&prim->indexArray[0],
				static_cast<unsigned long>(prim->indexArray.size()));

			prim->vertexBuffer.CreateBuffer(
				_device,
				&prim->vertexArray[0],
				static_cast<unsigned long>(prim->vertexArray.size()));
		}

		for (auto boneData : frameBase->boneDatas)
		{
			auto bone = ChPtr::Make_S<TargetBoneData11<CharaType>>();
			bone->boneData = boneData;
			auto&& objectList = _rootObject.GetAllChildlenConstainsName<ChCpp::FrameObject<CharaType>>(boneData->boneObjectName);
			bone->targetObject = objectList.empty() ? nullptr : objectList[0].lock();
			boneList.push_back(bone);
		}
	}

	for (auto&& cbildObj : LookObj()->GetAllChildlen())
	{
		auto child = ChPtr::SharedSafeCast<ChCpp::FrameObject<CharaType>>(cbildObj);

		if (child == nullptr)continue;

		auto&& com = child->SetComponent<FrameComponent11<CharaType>>();

		com->CreateAll(_device, _rootObject);
	}
}

template<typename CharaType>
void ChD3D11::FrameComponent11<CharaType>::SetBoneData(CB::CBBone11& _bone)
{
	if (boneList.empty())return;

	boneList[boneList.size() - 1]->targetObject->UpdateAllDrawTransform();
	for (size_t i = 0; i < boneList.size(); i++)
	{
		size_t useNum = boneList.size() - 1 - i;

		_bone.SetBoneObjectDrawMatrix(boneList[useNum]->targetObject->GetDrawLHandMatrix(), static_cast<unsigned long>(i));
		_bone.SetBoneOffsetMatrix(boneList[useNum]->boneData->boneOffset, static_cast<unsigned long>(i));
	}
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Init(ID3D11Device* _device)
{
	if (_device == nullptr)return;

	Release();

	device = _device;

	ChCpp::ModelObject<CharaType>::Init();

}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Init()
{
	if (!D3D11API().IsInit())return;
	Init(D3D11Device());
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::CreateFrames()
{
	auto fCom11 = ChCpp::BasicObject::GetComponent<ChD3D11::FrameComponent11<CharaType>>();

	if (fCom11 != nullptr)return;

	auto frame = ChCpp::BasicObject::SetComponent<ChD3D11::FrameComponent11<CharaType>>();

	frame->CreateAll(device, *this);
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Release()
{
	ChCpp::ModelObject<CharaType>::Release();
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Create()
{
	if (!ChCpp::ModelObject<CharaType>::IsInit())return;
	CreateFrames();
}


CH_STRING_TYPE_USE_D3D11_MESH_EXPLICIT_DECLARATION(ChD3D11::Mesh11);
CH_STRING_TYPE_USE_D3D11_MESH_EXPLICIT_DECLARATION(ChD3D11::TargetBoneData11);
CH_STRING_TYPE_USE_D3D11_MESH_EXPLICIT_DECLARATION(ChD3D11::FrameComponent11);
