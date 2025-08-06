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

void SamplePolygonShaderBase11_2::Init(
	ID3D11Device* _device,
	size_t _drawMaxCount)
{
	if (maxDrawCount() > 0)return;

	SampleShaderBase11_2::Init(_device, _drawMaxCount);

	polyData.Init(_device, &GetWhiteTexture(), maxDrawCount());
}

void SamplePolygonShaderBase11_2::Release()
{
	if (maxDrawCount() > 0)return;

	SampleShaderBase11_2::Release();
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

void SamplePolygonShaderBase11_2::SetMoveUV(const ChVec2& _move, size_t _no)
{
	polyData.SetMoveUV(_move, _no);
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
	if (maxDrawCount() <= 0)return;
	polyData.SetVSDrawData(_dc);
}

void SamplePolygonShaderBase11_2::SetShaderCharaData(ID3D11DeviceContext* _dc)
{
	if (maxDrawCount() <= 0)return;
	polyData.SetVSCharaData(_dc);
}

void SamplePolygonShaderBase11_2::DrawStart(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (maxDrawCount() <= 0)return;
	if (IsDraw())return;

	SampleShaderBase11_2::DrawStart(_dc);
	SetShaderDrawData(_dc);
}

void SamplePolygonShaderBase11_2::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;

	//•`‰æ•û–@//
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

	SampleShaderBase11_2::CreateRasteriser(desc);
	updateFlg = false;
}
