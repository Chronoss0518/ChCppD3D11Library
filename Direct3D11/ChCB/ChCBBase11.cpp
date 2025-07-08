#include<Windows.h>
#include"../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChTexture/ChTexture11.h"
#include"ChCBBase11.h"

using namespace ChD3D11;
using namespace CB;

void CBBase11::Init(ID3D11Device* _device)
{
	device = _device;
	SetInitFlg(true);
}

void CBBase11::SetShaderTexture(ID3D11DeviceContext* _dc, TextureBase11* _tex, TextureBase11& _defaultTex, const unsigned long _registerNo)
{
	if (ChPtr::NullCheck(_dc))return;

	TextureBase11* tmpTex = &_defaultTex;

	if (ChPtr::NotNullCheck(_tex))
	{
		if (_tex->IsTex())
		{
			tmpTex = _tex;
		}
	}

	tmpTex->SetDrawData(_dc, _registerNo);
}
