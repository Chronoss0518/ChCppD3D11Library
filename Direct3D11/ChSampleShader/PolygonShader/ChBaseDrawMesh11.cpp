#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChMesh/ChMesh11.h"

#include"../../ChCB/ChCBLight/ChCBLight11.h"
#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"
#include"../../ChCB/ChCBBone/ChCBBone11.h"

#include"ChBaseDrawMesh11.h"

template<typename CharaType>
ChD3D11::Shader::BaseDrawMesh11<CharaType>::DrawPrimitiveData11::~DrawPrimitiveData11()
{
	vertexBuffer.Release();
	indexBuffer.Release();
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::FrameComponent11::Create(ID3D11Device* _device, ChCpp::FrameComponent<CharaType>* _frameComponent, ChCpp::TransformObject<CharaType>& _rootObject)
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

			Ch3D::SkinMeshVertex<BONE_MAX_NUM> mVertex;
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
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::FrameComponent11::SetBoneData(CB::CBBone11& _bone)
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

template<typename CharaType>
ChD3D11::Shader::BaseDrawMesh11<CharaType>::~BaseDrawMesh11()
{
	Release();
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SamplePolygonShaderBase11::Init(_device);


	SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	polyData.Init(_device, &GetWhiteTexture(), &GetNormalTexture());
	boneData.Init(_device);
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::Release()
{
	SamplePolygonShaderBase11::Release();
	polyData.Release();
	boneData.Release();
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::InitVertexShader()
{

#include"../PolygonShader/BaseMeshVertex.inc"

	D3D11_INPUT_ELEMENT_DESC decl[10];

	decl[0] = { "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0, D3D11_INPUT_PER_VERTEX_DATA };
	decl[1] = { "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[2] = { "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[3] = { "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[4] = { "NORMAL",  1, DXGI_FORMAT_R32G32B32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[5] = { "BLENDINDEX",  0, DXGI_FORMAT_R32_UINT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[6] = { "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[7] = { "BLENDWEIGHT",  1, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[8] = { "BLENDWEIGHT",  2, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };
	decl[9] = { "BLENDWEIGHT",  3, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA };

	SamplePolygonShaderBase11::CreateVertexShader(decl, sizeof(decl) / sizeof(D3D11_INPUT_ELEMENT_DESC), main, sizeof(main));
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::InitPixelShader()
{
#include"../PolygonShader/BasePolygonPixcel.inc"

	SamplePolygonShaderBase11::CreatePixelShader(main, sizeof(main));
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::AddFrameComponent11(ChPtr::Shared<ChCpp::TransformObject<CharaType>>_model)
{
	auto&& frameBase = _model->GetComponent<ChCpp::FrameComponent<CharaType>>();

	if (frameBase != nullptr)
	{
		auto&& com = _model->SetComponent<FrameComponent11>();

		com->Create(GetDevice(), frameBase.get(), *_model);
	}

	for (auto&& cbildObj : _model->GetAllChildlen())
	{
		auto child = ChPtr::SharedSafeCast<ChCpp::TransformObject<CharaType>>(cbildObj);

		if (child == nullptr)continue;

		AddFrameComponent11(child);
	}
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::DrawStart(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (IsDraw())return;

	SamplePolygonShaderBase11::DrawStart(_dc);
	if (alphaBlendFlg)
		SamplePolygonShaderBase11::SetShaderBlender(GetDC());

}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::Draw(
	ChCpp::FrameObject<CharaType>& _mesh,
	const ChLMat& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (ChPtr::NullCheck(GetDC()))return;

	polyData.SetWorldMatrix(_mat);

	ChCpp::FrameObject<CharaType>& frame = _mesh;
	frame.UpdateFunction();
	DrawUpdate(frame);

}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::DrawUpdate(ChCpp::FrameObject<CharaType>& _object)
{
#if DEBUG
	unsigned long start, end;

	std::string debug;

	debug = "Draw Start:" + _object->GetMyName() + "\n";

	OutputDebugString(debug.c_str());

	start = timeGetTime();
#endif

	DrawMain(_object);

#if DEBUG
	end = timeGetTime();
	debug = "Draw End Time:" + std::to_string(end - start) + "\n";
	OutputDebugString(debug.c_str());
	OutputDebugString(">\n");
	OutputDebugString(">\n");
#endif

	auto&& childlen = _object.GetChildlen<ChCpp::FrameObject<CharaType>>();

	for (auto&& child : childlen)
	{
		if (child.expired())continue;
		DrawUpdate(*child.lock());
	}

}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::DrawMain(ChCpp::FrameObject<CharaType>& _object)
{
	_object.UpdateDrawTransform();
	auto&& frameCom = _object.GetComponent<FrameComponent11>();

	if (frameCom == nullptr)return;

	auto&& primitives = frameCom->GetPrimitives();

	if (primitives.empty())return;

	ChLMat drawMatrix = _object.GetDrawLHandMatrix();

	auto&& frame = frameCom->GetFrameCom();

	unsigned int offsets = 0;

	for (auto&& prim : primitives)
	{
		if (prim == nullptr)continue;

		auto&& mate11 = *prim->mate;

		polyData.SetMateDiffuse(mate11.mate.diffuse);
		polyData.SetMateSpecularColor(mate11.mate.specularColor);
		polyData.SetMateSpecularPower(mate11.mate.specularPower);
		polyData.SetMateAmbientColor(mate11.mate.ambient);

		polyData.SetShaderMaterialData(GetDC());

		prim->vertexBuffer.SetVertexBuffer(GetDC(), offsets);
		prim->indexBuffer.SetIndexBuffer(GetDC());

		polyData.SetFrameMatrix(drawMatrix);

		polyData.SetVSCharaData(GetDC());

		frameCom->SetBoneData(boneData);

		boneData.SetVSDrawData(GetDC());

		polyData.SetBaseTexture(prim->textures[Ch3D::TextureType::Diffuse].get());
		polyData.SetNormalTexture(prim->textures[Ch3D::TextureType::Normal].get());

		polyData.SetShaderTexture(GetDC());

		GetDC()->DrawIndexedInstanced(static_cast<unsigned int>(prim->indexArray.size()), 1, 0, 0, 0);

	}
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::DrawEnd()
{
	SamplePolygonShaderBase11::SetShaderDefaultBlender(GetDC());
	SamplePolygonShaderBase11::DrawEnd();
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;
	SamplePolygonShaderBase11::Update(_dc);
	updateFlg = false;
}

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChD3D11::Shader::BaseDrawMesh11);
