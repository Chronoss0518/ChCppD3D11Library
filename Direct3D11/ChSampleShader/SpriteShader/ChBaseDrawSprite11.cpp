#include<Windows.h>
#include"../../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../../BaseIncluder/ChD3D11I.h"

#include"../../ChTexture/ChTexture11.h"
#include"../../ChSprite/ChSprite11.h"

#include"../../ChCB/ChCBSprite/ChCBSprite11.h"

#include"ChBaseDrawSprite11.h"

using namespace ChD3D11;
using namespace Shader;

void BaseDrawSprite11::Init(ID3D11Device* _device)
{
	if (IsInit())return;

	SampleSpriteShaderBase11::Init(_device);
}

void BaseDrawSprite11::Release()
{
	if (!IsInit())return;

	SampleSpriteShaderBase11::Release();
}

void BaseDrawSprite11::InitPixelShader()
{
#include"../SpriteShader/BaseSpritePixel.inc"

	SampleSpriteShaderBase11::CreatePixelShader(main, sizeof(main));
}

void BaseDrawSprite11::Draw(
	TextureBase11& _tex,
	Sprite11& _sprite,
	const ChLMat& _mat)
{
	Draw(_tex, _sprite, ChVec4(1.0f), _mat);
}

void BaseDrawSprite11::Draw(
	TextureBase11& _tex,
	Sprite11& _sprite,
	const ChVec4& _baseColor,
	const ChLMat& _mat)
{
	if (!IsInit())return;
	if (!IsDraw())return;
	if (!_tex.IsTex())return;

	spriteData.SetSpriteMatrix(_mat);

	spriteData.SetBaseColor(_baseColor);

	spriteData.SetShaderSpriteData(GetDC());

	spriteData.SetBaseTexture(&_tex);

	spriteData.SetShaderTexture(GetDC());

	if (alphaBlendFlg)
		SampleSpriteShaderBase11::SetShaderBlender(GetDC());

	unsigned int offsets = 0;

	auto&& vertexs = _sprite.GetVertexs();

	vertexBuffer.UpdateResouce(GetDC(), &vertexs.vertex[0]);

	vertexBuffer.SetVertexBuffer(GetDC(), offsets);

	indexBuffer.SetIndexBuffer(GetDC());

	GetDC()->DrawIndexed(6, 0, 0);

	if (alphaBlendFlg)
		SampleSpriteShaderBase11::SetShaderDefaultBlender(GetDC());
}
