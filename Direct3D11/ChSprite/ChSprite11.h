#ifndef Ch_D3D11_Sprite_h
#define Ch_D3D11_Sprite_h

#include"../ChShaderStructures11.h"

namespace ChD3D11
{
	enum class SpritePositionName : unsigned char
	{
		LeftTop,RightTop,RightBottom, LeftBottom
	};

	struct SpriteVertex
	{
		static constexpr unsigned char VERTEX_COUNT = 4;
		Ch3D::Vertex vertex[VERTEX_COUNT];
	};


	class Sprite11
	{

	public:

		Sprite11& operator=(const Sprite11& _sp)
		{
			for (unsigned char i = 0; i < vertexs.VERTEX_COUNT; i++)
			{
				vertexs.vertex[i].pos = _sp.vertexs.vertex[i].pos;
				vertexs.vertex[i].color = _sp.vertexs.vertex[i].color;
				vertexs.vertex[i].uv = _sp.vertexs.vertex[i].uv;
			}

			return *this;

		}

	public://Init And Release//

		void Init();

	public://Set Functions//

		inline void SetPos(const SpritePositionName _posNames, const  ChVec2& _posData)
		{
			SetPos(static_cast<unsigned char>(_posNames), _posData);
		}

		void SetPos(const unsigned char _posNames, const  ChVec2& _posData);

		void SetPosRect(const  ChVec4& _rect);

		inline void SetUVPos(const SpritePositionName _posNames, const ChVec2& _posData)
		{
			SetUVPos(static_cast<unsigned char>(_posNames), _posData);
		}

		//UVPosはスクリーン座標系で計算されます//
		void SetUVPos(const unsigned char _posNames, const  ChVec2& _posData);

		//UVPosはスクリーン座標系で計算されます//
		void SetUVPosRect(const  ChVec4& _rect);

		void SetInitPosition();

		void SetInitUV();

	public://Get Functions//

		inline const SpriteVertex& GetVertexs() { return vertexs; }

		inline ChVec2 GetPos(const SpritePositionName _posNames)const
		{
			return GetPos(static_cast<unsigned char>(_posNames));
		}

		inline ChVec2 GetPos(const unsigned char _num)const
		{
			if (_num >= vertexs.VERTEX_COUNT)return ChVec2();

			return vertexs.vertex[_num].pos;
		}

		inline ChVec4 GetPosRect()const
		{
			ChVec4 res;
			res.left = vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftTop)].pos.x;
			res.top = vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftTop)].pos.y;
			res.right = vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightBottom)].pos.x;
			res.bottom = vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightBottom)].pos.y;
			return res;
		}

		inline ChVec2 GetUV(const SpritePositionName _posNames)const
		{
			return GetUV(static_cast<unsigned char>(_posNames));
		}

		ChVec2 GetUV(const unsigned char _num)const
		{
			if (_num >= vertexs.VERTEX_COUNT)return ChVec2();

			return vertexs.vertex[_num].uv;
		}

		inline ChVec4 GetUVRect()const
		{
			ChVec4 res;
			res.left = vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftTop)].uv.x;
			res.top = vertexs.vertex[static_cast<unsigned char>(SpritePositionName::LeftTop)].uv.y;
			res.right = vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightBottom)].uv.x;
			res.bottom = vertexs.vertex[static_cast<unsigned char>(SpritePositionName::RightBottom)].uv.y;
			return res;
		}

	public:

		inline void Move(const ChVec2& _vec) { Move(_vec.x, _vec.y); }

		void Move(const float _x,const float _y);

		inline void MoveX(const float _x) { Move(_x, 0.0f); }

		inline void MoveY(const float _y) { Move(0.0f, _y); }

	protected:

		SpriteVertex vertexs;

	};

}

#endif