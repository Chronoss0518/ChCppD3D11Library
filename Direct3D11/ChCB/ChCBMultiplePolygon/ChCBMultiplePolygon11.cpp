#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"ChCBMultiplePolygon11.h"
#include"../../../../ChCppDirect3DLibrary/ShaderHeaderFiles/Texture/BaseTexture.hlsli"
using namespace ChD3D11;
using namespace CB;

#define FLAG_CHECKER(_flg) _flg ? 1 : 0

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

	for (unsigned char i = 0; i < CH_DMP_MAX_FRAME_COUNT; i++)
	{
		frameData.drawFlgs[i] = 1;
	}

	drawBuf.CreateBuffer(GetDevice(), CH_DP_DRAW_DATA_REGISTERNO);
	modelBuf.CreateBuffer(GetDevice(), CH_DP_MODEL_DATA_REGISTERNO);
	frameBuf.CreateBuffer(GetDevice(), CH_DP_FRAME_DATA_REGISTERNO);
	mateBuf.CreateBuffer(GetDevice(), CH_DP_MATERIAL_DATA_REGISTERNO);

	drawData.alphaTestValue = 0.1f;
	defaultBase = _defaultBase;
	defaultNormal = _defaultNormal;

	SetInitFlg(true);
}

void CBMultiplePolygon11::Release()
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

void CBMultiplePolygon11::SetWorldMatrix(const ChLMat& _mat)
{
	modelData.worldMat = _mat;
	moUpdateFlg = true;
}

void CBMultiplePolygon11::SetFrameMatrix(const ChLMat& _mat, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	frameData.datas[_num].frameMatrix = _mat;
	fUpdateFlg = true;
}

void CBMultiplePolygon11::SetDrwaFlags(const bool _flg, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	frameData.drawFlgs[_num] = FLAG_CHECKER(_flg);
	fUpdateFlg = true;
}

void CBMultiplePolygon11::SetMoveUV(const ChVec2& _move, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	mateData.datas[_num].moveUV = _move;
	maUpdateFlg = true;
}

void CBMultiplePolygon11::SetMateDiffuse(const ChVec4& _diffuseCol, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	mateData.datas[_num].dif = _diffuseCol;
	maUpdateFlg = true;
}

void CBMultiplePolygon11::SetMateSpecularColor(const ChVec3& _specularCol, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	mateData.datas[_num].speCol = _specularCol;
	maUpdateFlg = true;
}

void CBMultiplePolygon11::SetMateSpecularPower(const float _specularPow, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	mateData.datas[_num].spePow = _specularPow;
	maUpdateFlg = true;
}

void CBMultiplePolygon11::SetMateAmbientColor(const ChVec3& _ambientCol, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	mateData.datas[_num].ambient = _ambientCol;
	maUpdateFlg = true;
}

void CBMultiplePolygon11::SetBaseTexture(TextureBase11* _tex, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	baseTex[_num] = _tex;
}

void CBMultiplePolygon11::SetNormalTexture(TextureBase11* _tex, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	normalTex[_num] = _tex;
}

void CBMultiplePolygon11::SetDrawData(const ChDrawData& _data)
{
	drawData = _data;
	dUpdateFlg = true;
}

void CBMultiplePolygon11::SetModelData(const ChModelData& _data)
{
	modelData = _data;
	moUpdateFlg = true;
}

void CBMultiplePolygon11::SetCharaData(const ChFrameData& _data, const bool _flg, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	frameData.datas[_num] = _data;
	frameData.drawFlgs[_num] = FLAG_CHECKER(_flg);
	fUpdateFlg = true;
}

void CBMultiplePolygon11::SetMaterialData(const ChMaterialData& _data, unsigned long _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return;
	mateData.datas[_num] = _data;
	maUpdateFlg = true;
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

void CBMultiplePolygon11::SetPSModelData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMoD(_dc);
	modelBuf.SetToPixelShader(_dc);
}

void CBMultiplePolygon11::SetVSModelData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMoD(_dc);
	modelBuf.SetToVertexShader(_dc);
}

void CBMultiplePolygon11::SetShaderModelData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSModelData(_dc);
	SetPSModelData(_dc);
}

void CBMultiplePolygon11::SetPSFrameData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateFD(_dc);
	frameBuf.SetToPixelShader(_dc);
}

void CBMultiplePolygon11::SetVSFrameData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateFD(_dc);
	frameBuf.SetToVertexShader(_dc);
}

void CBMultiplePolygon11::SetShaderFrameData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	SetVSFrameData(_dc);
	SetPSFrameData(_dc);
}

void CBMultiplePolygon11::SetPSMaterialData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMaD(_dc);
	mateBuf.SetToPixelShader(_dc);
}

void CBMultiplePolygon11::SetVSMaterialData(ID3D11DeviceContext* _dc)
{
	if (!*this)return;

	UpdateMaD(_dc);
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

ChLMat CBMultiplePolygon11::GetWorldMatrix()
{
	return modelData.worldMat;
}

ChLMat CBMultiplePolygon11::GetFrameMatrix(unsigned int _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return ChLMat();
	return frameData.datas[_num].frameMatrix;
}

ChVec2 CBMultiplePolygon11::GetMoveUV(unsigned int _num)
{
	if (_num < 0 || _num >= CH_DMP_MAX_FRAME_COUNT)return ChVec2();
	return mateData.datas[_num].moveUV;
}

void CBMultiplePolygon11::UpdateDD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!dUpdateFlg)return;
	drawBuf.UpdateResouce(_dc, &drawData);
	dUpdateFlg = false;
}

void CBMultiplePolygon11::UpdateMoD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!moUpdateFlg)return;
	modelBuf.UpdateResouce(_dc, &modelData);
	moUpdateFlg = false;
}

void CBMultiplePolygon11::UpdateFD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!fUpdateFlg)return;
	frameBuf.UpdateResouce(_dc, &frameData);
	fUpdateFlg = false;
}

void CBMultiplePolygon11::UpdateMaD(ID3D11DeviceContext* _dc)
{
	if (!IsInit())return;
	if (!maUpdateFlg)return;
	mateBuf.UpdateResouce(_dc, &mateData);
	maUpdateFlg = false;
}
