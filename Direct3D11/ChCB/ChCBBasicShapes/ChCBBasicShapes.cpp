#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"ChCBBasicShapes11.h"

using namespace ChD3D11;
using namespace CB;

void CBBasicShapes11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	CBBase11::Init(_device);
	bsBuf.CreateBuffer(GetDevice(), BASIC_SHAPES_DATA_REGISTERNO);
	SetInitFlg(true);
}

void CBBasicShapes11::Release()
{
	if (!IsInit())return;

	bsBuf.Release();
	SetInitFlg(false);
	bsUpdateFlg = true;
}

void CBBasicShapes11::SetSpriteMatrix(const ChLMat& _mat)
{
	bsData.spriteMat = _mat;
	bsUpdateFlg = true;
}

void CBBasicShapes11::SetColor(const ChVec4& _color)
{
	bsData.color = _color;
	bsUpdateFlg = true;
}

void CBBasicShapes11::SetBasicShapesData(const BasicShapesData& _data)
{
	bsData = _data;
	bsUpdateFlg = true;
}

void CBBasicShapes11::SetPSBasicShapesData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	bsBuf.SetToPixelShader(_dc);
}

void CBBasicShapes11::SetVSBasicShapesData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	bsBuf.SetToVertexShader(_dc);
}

void CBBasicShapes11::SetShaderBasicShapesData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetPSBasicShapesData(_dc);
	SetVSBasicShapesData(_dc);
}

void CBBasicShapes11::UpdateSD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!bsUpdateFlg)return;
	bsBuf.UpdateResouce(_dc, &bsData);
	bsUpdateFlg = false;
}

void CBBasicShapesPosition11::Init(
	ID3D11Device* _device)
{
	if (IsInit())return;

	CBBase11::Init(_device);
	positionData.positions.usePositionCount = 0;
	positionBuf.CreateBuffer(GetDevice(), BASIC_SHAPES_POSITION_DATA_REGISTERNO);

	SetInitFlg(true);
}

void CBBasicShapesPosition11::Release()
{
	if (!IsInit())return;

	positionBuf.Release();
	positionData.positions.usePositionCount = 0;
	SetInitFlg(false);
	updateFlg = true;
}


void CBBasicShapesPosition11::SetPosition(const ChVec2& _position, uint _no)
{
	if (_no >= positionData.positions.usePositionCount)return;

	positionData.positions.positions[_no] = _position;
	updateFlg = true;
}

void CBBasicShapesPosition11::SetPSBasicShapesPositionData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	positionBuf.SetToPixelShader(_dc);
}

void CBBasicShapesPosition11::SetVSBasicShapesPositionData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	positionBuf.SetToVertexShader(_dc);
}

void CBBasicShapesPosition11::SetShaderBasicShapesPositionData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetPSBasicShapesPositionData(_dc);
	SetVSBasicShapesPositionData(_dc);
}

void CBBasicShapesPosition11::AddPosition(const ChVec2& _position)
{
	if (positionData.positions.usePositionCount >= MAX_POSITION_DATA)return;
	positionData.positions.positions[positionData.positions.usePositionCount] = _position;
	positionData.positions.usePositionCount++;
	updateFlg = true;
}

void CBBasicShapesPosition11::PopPosition()
{
	if (positionData.positions.usePositionCount <= 0)return;
	positionData.positions.usePositionCount--;
	updateFlg = true;
}

void CBBasicShapesPosition11::ClearPosition()
{
	if (positionData.positions.usePositionCount <= 0)return;
	positionData.positions.usePositionCount = 0;
	updateFlg = true;
}

void CBBasicShapesPosition11::UpdateSD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!updateFlg)return;
	positionBuf.UpdateResouce(_dc, &positionData);
	updateFlg = false;
}

void CBBasicShapesCircle11::Init(
	ID3D11Device* _device)
{
	if (IsInit())return;

	CBBase11::Init(_device);
	circleData.circleDatas.usePositionCount = 0;
	circleBuf.CreateBuffer(GetDevice(), BASIC_SHAPES_CIRCLE_DATA_REGISTERNO);

	SetInitFlg(true);
}

void CBBasicShapesCircle11::Release()
{
	if (!IsInit())return;

	circleBuf.Release();
	circleData.circleDatas.usePositionCount = 0;
	SetInitFlg(false);
	updateFlg = true;
}

void CBBasicShapesCircle11::SetCenterPosition(const ChVec2& _centerPos,int _no)
{
	if (circleData.circleDatas.usePositionCount <= _no)return;
	circleData.circleDatas.datas[_no].centerPosition = _centerPos;
	updateFlg = true;
}

void CBBasicShapesCircle11::SetSize(float _size, int _no)
{
	if (circleData.circleDatas.usePositionCount <= _no)return;
	circleData.circleDatas.datas[_no].size = _size;
	updateFlg = true;
}

void CBBasicShapesCircle11::SetPSBasicShapesCircleData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	circleBuf.SetToPixelShader(_dc);
}

void CBBasicShapesCircle11::SetVSBasicShapesCircleData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateSD(_dc);
	circleBuf.SetToVertexShader(_dc);
}

void CBBasicShapesCircle11::SetShaderBasicShapesCircleData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetPSBasicShapesCircleData(_dc);
	SetVSBasicShapesCircleData(_dc);
}

void CBBasicShapesCircle11::AddCircleData(const ChVec2& _centerPos, float _size)
{
	if (circleData.circleDatas.usePositionCount >= MAX_CIRCLE_DATA)return;
	circleData.circleDatas.datas[circleData.circleDatas.usePositionCount].centerPosition = _centerPos;
	circleData.circleDatas.datas[circleData.circleDatas.usePositionCount].size = _size;
	circleData.circleDatas.usePositionCount++;
	updateFlg = true;
}

void CBBasicShapesCircle11::PopCircleData()
{
	if (circleData.circleDatas.usePositionCount <= 0)return;
	circleData.circleDatas.usePositionCount--;
	updateFlg = true;
}

void CBBasicShapesCircle11::ClearCircleData()
{
	if (circleData.circleDatas.usePositionCount <= 0)return;
	circleData.circleDatas.usePositionCount = 0;
	updateFlg = true;
}

void CBBasicShapesCircle11::UpdateSD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!updateFlg)return;
	circleBuf.UpdateResouce(_dc, &circleData);
	updateFlg = false;
}

