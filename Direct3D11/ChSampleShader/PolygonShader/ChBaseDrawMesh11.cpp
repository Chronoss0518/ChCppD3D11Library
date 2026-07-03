#include<Windows.h>
#include<array>

#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"

#include"../../ChTexture/ChTexture11.h"

#include"../../ChCB/ChCBLight/ChCBLight11.h"
#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"
#include"../../ChCB/ChCBBone/ChCBBone11.h"

#include"../../ChFrameComponent/ChFrameComponent11.h"

#include"ChBaseDrawMesh11.h"

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

	std::array<D3D11_INPUT_ELEMENT_DESC, 10>decl;

	FrameComponent11<CharaType>::CreateInputElements(decl);

	SamplePolygonShaderBase11::CreateVertexShader(&decl[0], decl.size(), main, sizeof(main));
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::InitPixelShader()
{
#include"../PolygonShader/BasePolygonPixcel.inc"

	SamplePolygonShaderBase11::CreatePixelShader(main, sizeof(main));
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::CreateFrameMesh(ChPtr::Shared<ChCpp::TransformObject<CharaType>>_model)
{
	FrameComponent11<CharaType>::CreateFrameMesh(GetDevice(),_model);
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
	auto&& frameCom = _object.GetComponent<FrameComponent11<CharaType>>();

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
