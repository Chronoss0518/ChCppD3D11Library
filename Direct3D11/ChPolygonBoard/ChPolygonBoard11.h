#ifndef Ch_D3D11_PolyBoard_h
#define Ch_D3D11_PolyBoard_h

#include"../ChShaderStructures11.h"

#include"../../BasePack/Ch3D.h"
#include"../../BasePack/ChPtr.h"

#include<vector>

namespace ChD3D11
{
	class PolygonBoard11
	{
	public://InitAndRelease//

		void Init();

		void Init(ID3D11Device* _device);

		void Release();

	public://Set Functions//

		void SetVertexList(const std::vector<ChPtr::Shared<Ch3D::PolyVertex>>& _vertexList)
		{
			if (!vertexs.empty())vertexs.clear();

			for (auto ver : _vertexList)
			{
				vertexs.push_back(ver);
			}
		}

		void SetPos(const unsigned char _posNo, const ChVec3& _posData);

		void SetUV(const unsigned char _posNo, const ChVec2& _posData);

		void SetInitTri();

		void SetInitSquare();

	public://Get Functions//

		inline const std::vector<ChPtr::Shared<Ch3D::PolyVertex>>& GetVertexs()
		{
			return vertexs;
		}

		Ch3D::PolyVertex GetVertex(size_t _num)const;

		size_t GetVertexSize()const;

		inline Ch3D::Material GetMaterial()const { return material; }

		ChVec3 GetPos(const unsigned char _num);

		ChVec2 GetUVPos(const unsigned char _num);

	public://Add Functions//

		inline void AddVertex()
		{
			Ch3D::PolyVertex vertex;
			AddVertex(vertex);
		}

		void AddVertex(const Ch3D::PolyVertex& _vertexs);

	protected:

		Ch3D::Material material;

		std::vector<ChPtr::Shared<Ch3D::PolyVertex>> vertexs;

	};
}

#endif
