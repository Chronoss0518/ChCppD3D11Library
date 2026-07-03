#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBPolygon11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/Texture/BaseTexture.hlsli"
using namespace ChD3D11;
using namespace CB;

///////////////////////////////////////////////////////////////////////////////////
//LightHeader Method
///////////////////////////////////////////////////////////////////////////////////

void CBPolygon11::Init(
	ID3D11Device* _device,
	TextureBase11* _defaultBase,
	TextureBase11* _defaultNormal)
{
	if (IsInit())return;

	if (ChPtr::NullCheck(_defaultBase))return;
	if (!_defaultBase->IsTex())return;

	if (ChPtr::NullCheck(_defaultNormal))return;
	if (!_defaultNormal->IsTex())return;

	CBBase11::Init(_device);
	drawBuf.CreateBuffer(GetDevice(), CH_DP_DRAW_DATA_REGISTERNO);
	modelBuf.CreateBuffer(GetDevice(), CH_DP_MODEL_DATA_REGISTERNO);
	frameBuf.CreateBuffer(GetDevice(), CH_DP_FRAME_DATA_REGISTERNO);
	mateBuf.CreateBuffer(GetDevice(), CH_DP_MATERIAL_DATA_REGISTERNO);


	drawData.alphaTestValue = 0.1f;
	defaultBase = _defaultBase;
	defaultNormal = _defaultNormal;

	SetInitFlg(true);
}

void CBPolygon11::Release()
{
	if (!IsInit())return;

	drawBuf.Release();
	modelBuf.Release();
	frameBuf.Release();
	mateBuf.Release();

	SetInitFlg(false);

	dUpdateFlg = true;
	moUpdateFlg = true;
	fUpdateFlg = true;
	maUpdateFlg = true;
}

void CBPolygon11::SetViewMatrix(const ChLMat& _mat)
{
	drawData.viewMat = _mat;
	dUpdateFlg = true;
}

void CBPolygon11::SetProjectionMatrix(const ChLMat& _mat)
{
	drawData.proMat = _mat;
	dUpdateFlg = true;
}

void CBPolygon11::SetWorldMatrix(const ChLMat& _mat)
{
	modelData.worldMat = _mat;
	moUpdateFlg = true;
}

void CBPolygon11::SetFrameMatrix(const ChLMat& _mat)
{
	frameData.frameMatrix = _mat;
	fUpdateFlg = true;
}

void CBPolygon11::SetMoveUV(const ChVec2& _move)
{
	mateData.moveUV = _move;
	maUpdateFlg = true;
}

void CBPolygon11::SetMateDiffuse(const ChVec4& _diffuseCol)
{
	mateData.dif = _diffuseCol;
	maUpdateFlg = true;
}

void CBPolygon11::SetMateSpecularColor(const ChVec3& _specularCol)
{
	mateData.speCol = _specularCol;
	maUpdateFlg = true;
}

void CBPolygon11::SetMateSpecularPower(const float _specularPow)
{
	mateData.spePow = _specularPow;
	maUpdateFlg = true;
}

void CBPolygon11::SetMateAmbientColor(const ChVec3& _ambientCol)
{
	mateData.ambient = _ambientCol;
	maUpdateFlg = true;
}

void CBPolygon11::SetDrawData(const ChDrawData& _data)
{
	drawData = _data;
	dUpdateFlg = true;
}

void CBPolygon11::SetModelData(const ChModelData& _data)
{
	modelData = _data;
	moUpdateFlg = true;
}

void CBPolygon11::SetFrameData(const ChFrameData& _data)
{
	frameData = _data;
	fUpdateFlg = true;
}

void CBPolygon11::SetMaterialData(const ChMaterialData& _data)
{
	mateData = _data;
	maUpdateFlg = true;
}

void CBPolygon11::SetPSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateDD(_dc);
	drawBuf.SetToPixelShader(_dc);
}

void CBPolygon11::SetVSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateDD(_dc);
	drawBuf.SetToVertexShader(_dc);
}

void CBPolygon11::SetShaderDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSDrawData(_dc);
	SetPSDrawData(_dc);
}

void CBPolygon11::SetPSModelData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMoD(_dc);
	modelBuf.SetToPixelShader(_dc);
}

void CBPolygon11::SetVSModelData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMoD(_dc);
	modelBuf.SetToVertexShader(_dc);
}

void CBPolygon11::SetShaderModelData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSModelData(_dc);
	SetPSModelData(_dc);
}

void CBPolygon11::SetPSFrameData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateFD(_dc);
	frameBuf.SetToPixelShader(_dc);
}

void CBPolygon11::SetVSFrameData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateFD(_dc);
	frameBuf.SetToVertexShader(_dc);
}

void CBPolygon11::SetShaderFrameData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSFrameData(_dc);
	SetPSFrameData(_dc);
}

void CBPolygon11::SetPSMaterialData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMaD(_dc);
	mateBuf.SetToPixelShader(_dc);
}

void CBPolygon11::SetVSMaterialData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMaD(_dc);
	mateBuf.SetToVertexShader(_dc);
}

void CBPolygon11::SetShaderMaterialData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSMaterialData(_dc);
	SetPSMaterialData(_dc);
}

void CBPolygon11::SetShaderTexture(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	CBBase11::SetShaderTexture(_dc, baseTex, *defaultBase, BASE_TEXTURE_REGISTER);
	//CBBase11::SetShaderTexture(_dc, normalTex, *defaultNormal, NORMAL_TEXTURE_REGISTER);
}

void CBPolygon11::UpdateDD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!dUpdateFlg)return;
	drawBuf.UpdateResouce(_dc, &drawData);
	dUpdateFlg = false;
}

void CBPolygon11::UpdateMoD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!moUpdateFlg)return;
	modelBuf.UpdateResouce(_dc, &modelData);
	moUpdateFlg = false;
}

void CBPolygon11::UpdateFD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!fUpdateFlg)return;
	frameBuf.UpdateResouce(_dc, &frameData);
	fUpdateFlg = false;
}

void CBPolygon11::UpdateMaD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!maUpdateFlg)return;
	mateBuf.UpdateResouce(_dc, &mateData);
	maUpdateFlg = false;
}
