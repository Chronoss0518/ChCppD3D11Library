#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBPolygon11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/5.0/Texture/BaseTexture.hlsli"
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
	drawBuf.CreateBuffer(GetDevice(), DRAW_DATA_REGISTERNO);
	charaBuf.CreateBuffer(GetDevice(), CHARACTOR_DATA_REGISTERNO);
	mateBuf.CreateBuffer(GetDevice(), MATERIAL_DATA_REGISTERNO);

	charaData.alphaTestValue = 0.1f;
	defaultBase = _defaultBase;
	defaultNormal = _defaultNormal;

	SetInitFlg(true);
}

void CBPolygon11::Release()
{
	if (!IsInit())return;

	drawBuf.Release();
	charaBuf.Release();
	mateBuf.Release();

	SetInitFlg(false);

	dUpdateFlg = true;
	cUpdateFlg = true;
	mUpdateFlg = true;
}

void CBPolygon11::SetFrameMatrix(const ChLMat& _mat)
{
	charaData.frameMatrix = _mat;
	cUpdateFlg = true;
}

void CBPolygon11::SetWorldMatrix(const ChLMat& _mat)
{
	charaData.worldMat = _mat;
	cUpdateFlg = true;
}

void CBPolygon11::SetMoveUV(const ChVec2& _move)
{
	charaData.moveUV = _move;
	cUpdateFlg = true;
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

void CBPolygon11::SetMateDiffuse(const ChVec4& _diffuseCol)
{
	mateData.dif = _diffuseCol;
	mUpdateFlg = true;
}

void CBPolygon11::SetMateSpecularColor(const ChVec3& _specularCol)
{
	mateData.speCol = _specularCol;
	mUpdateFlg = true;
}

void CBPolygon11::SetMateSpecularPower(const float _specularPow)
{
	mateData.spePow = _specularPow;
	mUpdateFlg = true;
}

void CBPolygon11::SetMateAmbientColor(const ChVec3& _ambientCol)
{
	mateData.ambient = _ambientCol;
	mUpdateFlg = true;
}

void CBPolygon11::SetDrawData(const ChP_DrawData& _data)
{
	drawData = _data;
	dUpdateFlg = true;
}

void CBPolygon11::SetCharaData(const ChP_CharaData& _data)
{
	charaData = _data;
	cUpdateFlg = true;
}

void CBPolygon11::SetMaterialData(const ChP_Material& _data)
{
	mateData = _data;
	mUpdateFlg = true;
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

void CBPolygon11::SetPSCharaData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateCD(_dc);
	charaBuf.SetToPixelShader(_dc);
}

void CBPolygon11::SetVSCharaData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateCD(_dc);
	charaBuf.SetToVertexShader(_dc);
}

void CBPolygon11::SetShaderCharaData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSCharaData(_dc);
	SetPSCharaData(_dc);
}

void CBPolygon11::SetPSMaterialData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMD(_dc);
	mateBuf.SetToPixelShader(_dc);
}

void CBPolygon11::SetVSMaterialData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMD(_dc);
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
	CBBase11::SetShaderTexture(_dc, normalTex, *defaultNormal, NORMAL_TEXTURE_REGISTER);
}

void CBPolygon11::UpdateDD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!dUpdateFlg)return;
	drawBuf.UpdateResouce(_dc, &drawData);
	dUpdateFlg = false;
}

void CBPolygon11::UpdateCD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!cUpdateFlg)return;
	charaBuf.UpdateResouce(_dc, &charaData);
	cUpdateFlg = false;
}

void CBPolygon11::UpdateMD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!mUpdateFlg)return;
	mateBuf.UpdateResouce(_dc, &mateData);
	mUpdateFlg = false;
}
