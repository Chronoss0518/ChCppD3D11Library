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
ChD3D11::Shader::BaseDrawMesh11<CharaType>::~BaseDrawMesh11()
{
	Release();
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SamplePolygonShaderBase11::Init(_device);

	{
		D3D11_BLEND_DESC desc;
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;
		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

		desc.RenderTarget[1].BlendEnable = true;
		desc.RenderTarget[1].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[1].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[1].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[1].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[1].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[1].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[1].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;

		CreateBlender(desc);
	}

	SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	polyData.Init(_device, &GetWhiteTexture(), &GetNormalTexture());
	boneData.Init(_device);
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::Release()
{
	SamplePolygonShaderBase11::Release();
	polyData.Release();
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
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::DrawStart(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (IsDraw())return;

	SamplePolygonShaderBase11::DrawStart(_dc);
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::Draw(
	Mesh11<CharaType>& _mesh,
	const ChLMat& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (ChPtr::NullCheck(GetDC()))return;

	worldMat = _mat;

	DrawUpdate(_mesh);
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
	ChLMat drawMatrix = _object.GetDrawLHandMatrix();

	auto&& frameCom = _object.GetComponent<ChD3D11::FrameComponent11<CharaType>>();

	if (frameCom == nullptr)return;

	auto&& primitives = frameCom->GetPrimitives();

	if (primitives.empty())return;

	auto&& frame = frameCom->GetFrameCom();

	auto drawData = ChPtr::Make_S<DrawData>();

	drawData->worldMatrix = worldMat;
	drawData->frameMatrix = drawMatrix;
	drawData->drawFrame = frameCom.get();

	drawDatas[frame].push_back(drawData);
}

template<typename CharaType>
void ChD3D11::Shader::BaseDrawMesh11<CharaType>::DrawEnd()
{
	unsigned int offsets = 0;

	if (alphaBlendFlg)
	{
		SamplePolygonShaderBase11::SetShaderBlender(GetDC());
	}

	for (auto&& drawData : drawDatas)
	{
		if (drawData.second.empty())continue;
		auto&& primitiveData = drawData.second[0]->drawFrame->GetPrimitives();

		for (auto&& prim : primitiveData)
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

			for (auto&& drawFrame : drawData.second)
			{

				polyData.SetWorldMatrix(drawFrame->worldMatrix);

				polyData.SetFrameMatrix(drawFrame->frameMatrix);

				polyData.SetVSCharaData(GetDC());

				drawFrame->drawFrame->SetBoneData(boneData);

				boneData.SetVSDrawData(GetDC());

				polyData.SetBaseTexture(prim->textures[Ch3D::TextureType::Diffuse].get());
				polyData.SetNormalTexture(prim->textures[Ch3D::TextureType::Normal].get());

				polyData.SetShaderTexture(GetDC());

				GetDC()->DrawIndexed(static_cast<unsigned int>(prim->indexArray.size()), 0, 0);
			}
		}
	}
	if (!drawDatas.empty())drawDatas.clear();
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

CH_STRING_TYPE_USE_D3D11_MESH_EXPLICIT_DECLARATION(ChD3D11::Shader::BaseDrawMesh11);
