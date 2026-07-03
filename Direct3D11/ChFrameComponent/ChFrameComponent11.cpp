#include<Windows.h>
#include<array>

#include"../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"

#include"../ChTexture/ChTexture11.h"
#include"../ChCB/ChCBBone/ChCBBone11.h"

#include"ChFrameComponent11.h"


template<typename CharaType>
ChD3D11::FrameComponent11<CharaType>::DrawPrimitiveData11::~DrawPrimitiveData11()
{
	vertexBuffer.Release();
	indexBuffer.Release();
}

template<typename CharaType>
void ChD3D11::FrameComponent11<CharaType>::Create(ID3D11Device* _device, ChCpp::FrameComponent<CharaType>* _frameComponent, ChCpp::TransformObject<CharaType>& _rootObject)
{
	if (ChPtr::NullCheck(_device))return;

	frameCom = _frameComponent;

	for (auto&& material : _frameComponent->materialList)
	{
		auto&& primitive11 = ChPtr::Make_S<DrawPrimitiveData11>();
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

	for (auto&& primitive : _frameComponent->primitives)
	{
		auto&& primitive11 = primitives[primitive->mateNo];

		size_t firstIndex = primitive11->vertexArray.size();
		size_t indexCount = 0;

		for (auto&& vertex : primitive->vertexData)
		{
			size_t vertexNo = vertex->vertexNo;

			auto&& tmpVertex = *_frameComponent->vertexList[vertexNo];

			Ch3D::SkinMeshVertex<CH_BB_BONE_MAX_NUM> mVertex;
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

	for (auto boneData : _frameComponent->boneDatas)
	{
		auto bone = ChPtr::Make_S<TargetBoneData11>();
		bone->boneData = boneData;
		auto&& objectList = _rootObject.GetAllChildlenConstainsName<ChCpp::FrameObject<CharaType>>(boneData->boneObjectName);
		bone->targetObject = objectList.empty() ? nullptr : objectList[0].lock();
		boneList.push_back(bone);
	}
}

template<typename CharaType>
void ChD3D11::FrameComponent11<CharaType>::SetBoneData(CB::CBBone11& _bone)
{
	if (boneList.empty())return;

	for (size_t i = 0; i < boneList.size(); i++)
	{
		_bone.SetBoneMatrix(
			boneList[i]->targetObject->GetOffsetLMatrix(),
			boneList[i]->targetObject->GetDrawLHandMatrix(),
			static_cast<unsigned long>(i));
	}
}

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChD3D11::FrameComponent11);