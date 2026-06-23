
#include<Windows.h>
#include"../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"

#include"../../BaseIncluder/ChD3D11I.h"

#include"../ChDirectX11Controller/ChDirectX11Controller.h"
#include"../ChTexture/ChTexture11.h"
#include"ChMesh11.h"

#include"../../../ChCppDirect3DLibrary/ShaderHeaderFiles/BoneBlending.hlsli"

using namespace Ch3D;
using namespace ChCpp;
using namespace ChD3D11;

///////////////////////////////////////////////////////////////////////////////////////
//ChMesh11 Method
///////////////////////////////////////////////////////////////////////////////////////

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Init(ID3D11Device* _device)
{
	if (_device == nullptr)return;

	Release();

	device = _device;

	ChCpp::ModelObject<CharaType>::Init();

}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Init()
{
	if (!D3D11API().IsInit())return;
	Init(D3D11Device());
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::CreateFrames()
{
#if 0
	auto fCom11 = ChCpp::BasicObject::GetComponent<ChD3D11::FrameComponent11<CharaType>>();

	if (fCom11 != nullptr)return;

	auto frame = ChCpp::BasicObject::SetComponent<ChD3D11::FrameComponent11<CharaType>>();

	frame->CreateAll(device, *this);
#endif
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Release()
{
	ChCpp::ModelObject<CharaType>::Release();
}

template<typename CharaType>
void ChD3D11::Mesh11<CharaType>::Create()
{
	if (!ChCpp::ModelObject<CharaType>::IsInit())return;
	CreateFrames();
}


CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChD3D11::Mesh11);
