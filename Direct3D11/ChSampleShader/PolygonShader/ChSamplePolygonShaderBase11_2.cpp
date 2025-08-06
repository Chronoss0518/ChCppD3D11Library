#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChPolygonBoard/ChPolygonBoard11.h"

#include"../../ChCB/ChCBPolygon11_2/ChCBPolygon11_2.h"

#include"ChSamplePolygonShaderBase11_2.h"

using namespace ChCpp;
using namespace ChD3D11;
using namespace Shader;

#define DEBUG 0

void SamplePolygonShaderBase11_2::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleShaderBase11::Init(_device);
	polyData.Init(_device, &GetWhiteTexture(), &GetNormalTexture());
}

void SamplePolygonShaderBase11_2::Release()
{
	if (!IsInit())return;

	SampleShaderBase11::Release();
	polyData.Release();
}

void SamplePolygonShaderBase11_2::SetProjectionMatrix(const ChLMat& _mat)
{
	polyData.SetProjectionMatrix(_mat);
}

void SamplePolygonShaderBase11_2::SetViewMatrix(const ChLMat& _mat)
{
	polyData.SetViewMatrix(_mat);
}

void SamplePolygonShaderBase11_2::SetMoveUV(const ChVec2& _move)
{
	polyData.SetMoveUV(_move);
}

void SamplePolygonShaderBase11_2::SetFillMode(const D3D11_FILL_MODE _fill)
{
	fill = _fill;
	updateFlg = true;
}

void SamplePolygonShaderBase11_2::SetCullMode(const D3D11_CULL_MODE _cull)
{
	cull = _cull;
	updateFlg = true;
}

void SamplePolygonShaderBase11_2::SetShaderDrawData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	polyData.SetVSDrawData(_dc);
}

void SamplePolygonShaderBase11_2::SetShaderCharaData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	polyData.SetVSCharaData(_dc);
}

void SamplePolygonShaderBase11_2::DrawStart(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!IsInit())return;
	if (IsDraw())return;

	SampleShaderBase11::DrawStart(_dc);
	SetShaderDrawData(_dc);
}

void SamplePolygonShaderBase11_2::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;

	//�`����@//
	D3D11_RASTERIZER_DESC desc
	{
		fill,
		cull,
		false,
		0,
		0.0f,
		0.0f,
		false,
		false,
		false,
		true
	};

	SampleShaderBase11::CreateRasteriser(desc);
	updateFlg = false;
}
