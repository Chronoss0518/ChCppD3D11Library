
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChSprite11.h"

using namespace ChD3D11;

void Sprite11::Init()
{
	SetInitPosition();
	SetInitUV();
}

void Sprite11::SetPos(const unsigned char _posNames, const  ChVec2& _posData)
{
	if (_posNames >= vertexs.VERTEX_COUNT)return;
	vertexs.vertex[_posNames].pos = _posData;
}

void Sprite11::SetPosRect(const  ChVec4& _rect)
{
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftTop)].pos = ChVec2(_rect.left, _rect.top);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightTop)].pos = ChVec2(_rect.right, _rect.top);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightBottom)].pos = ChVec2(_rect.right, _rect.bottom);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftBottom)].pos = ChVec2(_rect.left, _rect.bottom);
}

void Sprite11::SetUVPos(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= vertexs.VERTEX_COUNT)return;
	vertexs.vertex[_posNames].uv = _posData;
}

void Sprite11::SetUVPosRect(const  ChVec4& _rect)
{
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftTop)].uv = ChVec2(_rect.left, _rect.top);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightTop)].uv = ChVec2(_rect.right, _rect.top);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightBottom)].uv = ChVec2(_rect.right, _rect.bottom);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftBottom)].uv = ChVec2(_rect.left, _rect.bottom);
}

void Sprite11::SetInitPosition()
{
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftTop)].pos = ChVec2(-1.0f, 1.0f);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightTop)].pos = ChVec2(1.0f, 1.0f);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightBottom)].pos = ChVec2(1.0f, -1.0f);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftBottom)].pos = ChVec2(-1.0f, -1.0f);
}

void Sprite11::SetInitUV()
{
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftTop)].uv = ChVec2(0.0f, 0.0f);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightTop)].uv = ChVec2(1.0f, 0.0f);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightBottom)].uv = ChVec2(1.0f, 1.0f);
	vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftBottom)].uv = ChVec2(0.0f, 1.0f);
}

void Sprite11::Move(const float _x, const float _y)
{
	for (unsigned char i = 0; i < vertexs.VERTEX_COUNT; i++)
	{
		vertexs.vertex[i].pos.x += _x;
		vertexs.vertex[i].pos.y += _y;
	}
}
