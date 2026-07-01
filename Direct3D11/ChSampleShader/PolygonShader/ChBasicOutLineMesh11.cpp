#include<Windows.h>
#include<array>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../../../ChCppBaseLibrary/CPP/ChModel/ChModelObject.h"

#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"
#include"../../ChCB/ChCBBone/ChCBBone11.h"

#include"../../ChFrameComponent/ChFrameComponent11.h"

#include"ChBasicOutLineMesh11.h"

#define MIN_WIDTH 0.01f

template<typename CharaType>
ChD3D11::Shader::BasicOutLineMesh11<CharaType>::~BasicOutLineMesh11()
{
	Release();
}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SamplePolygonShaderBase11::Init(_device);

	SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	SetCullMode(D3D11_CULL_FRONT);

	polyData.Init(_device, &GetWhiteTexture(), &GetNormalTexture());
	boneData.Init(_device);
	outLineData.Init(_device);
}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::Release()
{
	SamplePolygonShaderBase11::Release();
	polyData.Release();
	boneData.Release();
	outLineData.Release();
}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::InitVertexShader()
{

#include"../PolygonShader/BasicOutLineMeshVertex.inc"

	std::array<D3D11_INPUT_ELEMENT_DESC, 10>decl;

	FrameComponent11<CharaType>::CreateInputElements<10>(decl);

	SamplePolygonShaderBase11::CreateVertexShader(&decl[0], decl.size(), main, sizeof(main));
}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::InitPixelShader()
{
#include"../PolygonShader/BasicOutLineMeshPixcel.inc"

	SamplePolygonShaderBase11::CreatePixelShader(main, sizeof(main));
}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::CreateFrameMesh(ChPtr::Shared<ChCpp::TransformObject<CharaType>>_model)
{
	FrameComponent11<CharaType>::CreateFrameMesh(GetDevice(), _model);
}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::SetOutLineWidth(const float _width)
{
	outLineData.SetWidth(_width);
}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::SetOutLineColor(const ChVec4& _color)
{
	outLineData.SetOutLineColor(_color);
}

template<typename CharaType>
float ChD3D11::Shader::BasicOutLineMesh11<CharaType>::GetOutLineWidth()
{
	return outLineData.GetWidth();
}

template<typename CharaType>
ChVec4 ChD3D11::Shader::BasicOutLineMesh11<CharaType>::GetOutLineColor()
{
	return outLineData.GetOutLineColor();
}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::DrawStart(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (IsDraw())return;

	SamplePolygonShaderBase11::DrawStart(_dc);
	if (alphaBlendFlg)
		SamplePolygonShaderBase11::SetShaderBlender(GetDC());

}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::Draw(
	Mesh11<CharaType>& _mesh,
	const ChLMat& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (ChPtr::NullCheck(GetDC()))return;

	if (outLineData.GetOutLineColor().a <= polyData.GetCharaData().alphaTestValue)return;
	if (outLineData.GetWidth() <= MIN_WIDTH)return;

	polyData.SetWorldMatrix(_mat);
	outLineData.SetShaderDrawData(GetDC());

	ChCpp::FrameObject<CharaType>& frame = _mesh;
	frame.UpdateFunction();
	DrawUpdate(frame);

}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::DrawUpdate(ChCpp::FrameObject<CharaType>& _object)
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
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::DrawMain(ChCpp::FrameObject<CharaType>& _object)
{
	auto&& frameCom = _object.GetComponent<ChD3D11::FrameComponent11<CharaType>>();

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
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::DrawEnd()
{
	SamplePolygonShaderBase11::SetShaderDefaultBlender(GetDC());
	SamplePolygonShaderBase11::DrawEnd();
}

template<typename CharaType>
void ChD3D11::Shader::BasicOutLineMesh11<CharaType>::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;
	SamplePolygonShaderBase11::Update(_dc);
	updateFlg = false;
}

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChD3D11::Shader::BasicOutLineMesh11);
