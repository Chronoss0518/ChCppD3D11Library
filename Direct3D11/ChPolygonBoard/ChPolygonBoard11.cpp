
#include<Windows.h>
#include"../../BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D11I.h"

#include"ChPolygonBoard11.h"

using namespace ChD3D11;

void PolygonBoard11::Init()
{
	if (!D3D11API().IsInit())return;

	Init(D3D11Device());
}

void PolygonBoard11::Init(ID3D11Device* _device)
{
	SetInitSquare();

	material.diffuse = ChVec4(1.0f);
	material.specularColor = ChVec3(0.0f);
	material.specularPower = 1.0f;
	material.ambient = ChVec4(0.0f);
}

void ChD3D11::PolygonBoard11::Release()
{
	if (!vertexs.empty())vertexs.clear();
}

void ChD3D11::PolygonBoard11::SetInitTri()
{
	SetInitSquare();
	vertexs.pop_back();
}

void ChD3D11::PolygonBoard11::SetPos(const unsigned char _posNames, const  ChVec3& _posData)
{
	if (_posNames >= vertexs.size())return;
	vertexs[_posNames]->pos = _posData;
}

void ChD3D11::PolygonBoard11::SetUV(const unsigned char _posNames, const ChVec2& _posData)
{
	if (_posNames >= vertexs.size())return;
	vertexs[_posNames]->uv = _posData;
}

void ChD3D11::PolygonBoard11::SetInitSquare()
{
	if (!vertexs.empty())vertexs.clear();

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(-0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(0.5f, 0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 0.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();

		vertex->pos = ChVec3(0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(1.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexs.push_back(vertex);
	}

	{
		auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();


		vertex->pos = ChVec3(-0.5f, -0.5f, 0.0f);
		vertex->uv = ChVec2(0.0f, 1.0f);
		vertex->color = ChVec4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexs.push_back(vertex);
	}

}

Ch3D::PolyVertex ChD3D11::PolygonBoard11::GetVertex(size_t _num)const
{
	if (vertexs.size() <= _num)return Ch3D::PolyVertex();
	return *vertexs[_num];
}

size_t ChD3D11::PolygonBoard11::GetVertexSize()const
{
	return vertexs.size();
}

ChVec3 ChD3D11::PolygonBoard11::GetPos(const unsigned char _num)
{
	if (_num >= vertexs.size())return ChVec3();
	return vertexs[_num]->pos;
}

ChVec2 ChD3D11::PolygonBoard11::GetUVPos(const unsigned char _num)
{
	if (_num >= vertexs.size())return ChVec2();
	return vertexs[_num]->uv;
}

void ChD3D11::PolygonBoard11::AddVertex(const Ch3D::PolyVertex& _vertexs)
{
	auto vertex = ChPtr::Make_S<Ch3D::PolyVertex>();
	vertex->pos = _vertexs.pos;
	vertex->uv = _vertexs.uv;
	vertex->color = _vertexs.color;
	vertex->normal = _vertexs.normal;
	vertexs.push_back(vertex);
}
