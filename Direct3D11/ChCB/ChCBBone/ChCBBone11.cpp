#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBBone11.h"

using namespace ChD3D11;
using namespace CB;

void CBBone11::Init(ID3D11Device* _device)
{
	Release();

	CBBase11::Init(_device);
	buf.CreateBuffer(_device, BONE_DATA_REGISTERNO);
	SetInitFlg(true);
}

void CBBone11::Release()
{
	if (!*this)return;

	buf.Release();
	SetInitFlg(false);
}

void CBBone11::SetBoneOffsetMatrix(const ChLMat& _mat, const unsigned long _no)
{
	if (!*this)return;
	if (_no >= BONE_MAX_NUM)return;
	if (bone.boneOffsetMat[_no] == _mat)return;

	bone.boneOffsetMat[_no] = _mat;
	updateFlg = true;
}

void CBBone11::SetFrameInverseMatrix(const ChLMat& _frameMat)
{
	if (!*this)return;

	bone.frameInverseMatrix = _frameMat;
	bone.frameInverseMatrix.Inverse();
	updateFlg = true;
}

void CBBone11::SetPSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	Update(_dc);
	buf.SetToPixelShader(_dc);
}

void CBBone11::SetVSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	Update(_dc);
	buf.SetToVertexShader(_dc);
}

void CBBone11::SetDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	Update(_dc);

	buf.SetToVertexShader(_dc);
	buf.SetToPixelShader(_dc);
}

void CBBone11::Update(ID3D11DeviceContext* _dc)
{
	if (!updateFlg)return;

	buf.UpdateResouce(_dc, &bone);
	updateFlg = false;
}