#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChPolygonBoard/ChPolygonBoard11.h"

#include"../../ChCB/ChCBPolygon/ChCBPolygon11.h"

#include"ChSamplePolygonShaderUseDrawPolygonBase11.h"

using namespace ChCpp;
using namespace ChD3D11;
using namespace Shader;

#define DEBUG 0

void SamplePolygonShaderUseDrawPolygonBase11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SamplePolygonShaderBase11::Init(_device);
	polyData.Init(_device, &GetWhiteTexture(), &GetNormalTexture());
}

void SamplePolygonShaderUseDrawPolygonBase11::Release()
{
	if (!IsInit())return;

	SamplePolygonShaderBase11::Release();
	polyData.Release();
}

void SamplePolygonShaderUseDrawPolygonBase11::SetProjectionMatrix(const ChLMat& _mat)
{
	if (!IsInit())return;
	if (IsDraw())return;
	polyData.SetProjectionMatrix(_mat);
}

void SamplePolygonShaderUseDrawPolygonBase11::SetViewMatrix(const ChLMat& _mat)
{
	if (!IsInit())return;
	if (IsDraw())return;
	polyData.SetViewMatrix(_mat);
}

void SamplePolygonShaderUseDrawPolygonBase11::SetMoveUV(const ChVec2& _move)
{
	if (!IsInit())return;
	polyData.SetMoveUV(_move);
}

void SamplePolygonShaderUseDrawPolygonBase11::SetShaderDrawData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	polyData.SetVSDrawData(_dc);
	polyData.SetPSDrawData(_dc);
}

void SamplePolygonShaderUseDrawPolygonBase11::SetShaderModelData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	polyData.SetVSModelData(_dc);
	polyData.SetPSModelData(_dc);
}

void SamplePolygonShaderUseDrawPolygonBase11::SetShaderFrameData(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	polyData.SetVSFrameData(_dc);
	polyData.SetPSFrameData(_dc);
}

void SamplePolygonShaderUseDrawPolygonBase11::DrawStart(ID3D11DeviceContext* _dc)
{
	if (ChPtr::NullCheck(_dc))return;
	if (!IsInit())return;
	if (IsDraw())return;

	SamplePolygonShaderBase11::DrawStart(_dc);
	SetShaderDrawData(_dc);
}
