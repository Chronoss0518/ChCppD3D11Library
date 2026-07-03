#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBMultiplePolygon11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/Texture/BaseTexture.hlsli"
using namespace ChD3D11;
using namespace CB;

///////////////////////////////////////////////////////////////////////////////////
//LightHeader Method
///////////////////////////////////////////////////////////////////////////////////

void CBMultiplePolygon11::Init(
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

	drawData.alphaTestValue = 0.1f;
	defaultBase = _defaultBase;
	defaultNormal = _defaultNormal;

	SetInitFlg(true);
}

void CBMultiplePolygon11::Release()
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

void CBMultiplePolygon11::SetFrameMatrix(const ChLMat& _mat, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	charaData.datas[_num].frameMatrix = _mat;
	cUpdateFlg = true;
}

void CBMultiplePolygon11::SetWorldMatrix(const ChLMat& _mat, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	charaData.datas[_num].worldMat = _mat;
	cUpdateFlg = true;
}

void CBMultiplePolygon11::SetMoveUV(const ChVec2& _move, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	charaData.datas[_num].moveUV = _move;
	cUpdateFlg = true;
}

void CBMultiplePolygon11::SetViewMatrix(const ChLMat& _mat)
{
	drawData.viewMat = _mat;
	dUpdateFlg = true;
}

void CBMultiplePolygon11::SetProjectionMatrix(const ChLMat& _mat)
{
	drawData.proMat = _mat;
	dUpdateFlg = true;
}

void CBMultiplePolygon11::SetMateDiffuse(const ChVec4& _diffuseCol, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	mateData.datas[_num].dif = _diffuseCol;
	mUpdateFlg = true;
}

void CBMultiplePolygon11::SetMateSpecularColor(const ChVec3& _specularCol, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	mateData.datas[_num].speCol = _specularCol;
	mUpdateFlg = true;
}

void CBMultiplePolygon11::SetMateSpecularPower(const float _specularPow, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	mateData.datas[_num].spePow = _specularPow;
	mUpdateFlg = true;
}

void CBMultiplePolygon11::SetMateAmbientColor(const ChVec3& _ambientCol, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	mateData.datas[_num].ambient = _ambientCol;
	mUpdateFlg = true;
}

void CBMultiplePolygon11::SetBaseTexture(TextureBase11* _tex, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	baseTex[_num] = _tex;
}

void CBMultiplePolygon11::SetNormalTexture(TextureBase11* _tex, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	normalTex[_num] = _tex;
}

void CBMultiplePolygon11::SetDrawData(const ChDrawData& _data)
{
	drawData = _data;
	dUpdateFlg = true;
}

void CBMultiplePolygon11::SetCharaData(const ChCharaData& _data, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	charaData.datas[_num] = _data;
	cUpdateFlg = true;
}

void CBMultiplePolygon11::SetMaterialData(const ChMaterial& _data, unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return;
	mateData.datas[_num] = _data;
	mUpdateFlg = true;
}

void CBMultiplePolygon11::SetPSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateDD(_dc);
	drawBuf.SetToPixelShader(_dc);
}

void CBMultiplePolygon11::SetVSDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateDD(_dc);
	drawBuf.SetToVertexShader(_dc);
}

void CBMultiplePolygon11::SetShaderDrawData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSDrawData(_dc);
	SetPSDrawData(_dc);
}

void CBMultiplePolygon11::SetPSCharaData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateCD(_dc);
	charaBuf.SetToPixelShader(_dc);
}

void CBMultiplePolygon11::SetVSCharaData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateCD(_dc);
	charaBuf.SetToVertexShader(_dc);
}

void CBMultiplePolygon11::SetShaderCharaData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSCharaData(_dc);
	SetPSCharaData(_dc);
}

void CBMultiplePolygon11::SetPSMaterialData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMD(_dc);
	mateBuf.SetToPixelShader(_dc);
}

void CBMultiplePolygon11::SetVSMaterialData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMD(_dc);
	mateBuf.SetToVertexShader(_dc);
}

void CBMultiplePolygon11::SetShaderMaterialData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSMaterialData(_dc);
	SetPSMaterialData(_dc);
}

void CBMultiplePolygon11::SetShaderTexture(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	CBBase11::SetShaderTextures(_dc, baseTex, *defaultBase, BASE_TEXTURE_REGISTER);
	//CBBase11::SetShaderTexture(_dc, normalTex, *defaultNormal, NORMAL_TEXTURE_REGISTER);
}

ChLMat CBMultiplePolygon11::GetWorldMatrix(unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return ChLMat();
	return charaData.datas[_num].worldMat;
}

ChLMat CBMultiplePolygon11::GetFrameMatrix(unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return ChLMat();
	return charaData.datas[_num].frameMatrix;
}

ChVec2 CBMultiplePolygon11::GetMoveUV(unsigned int _num)
{
	if (_num < 0 || _num >= MAX_FRAME_COUNT)return ChVec2();
	return charaData.datas[_num].moveUV;
}

void CBMultiplePolygon11::UpdateDD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!dUpdateFlg)return;
	drawBuf.UpdateResouce(_dc, &drawData);
	dUpdateFlg = false;
}

void CBMultiplePolygon11::UpdateCD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!cUpdateFlg)return;
	charaBuf.UpdateResouce(_dc, &charaData);
	cUpdateFlg = false;
}

void CBMultiplePolygon11::UpdateMD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!mUpdateFlg)return;
	mateBuf.UpdateResouce(_dc, &mateData);
	mUpdateFlg = false;
}
