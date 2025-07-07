#ifndef Ch_D3D11_Qua_h
#define Ch_D3D11_Qua_h

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#include<DirectXColors.h>
#include<DirectXMath.h>
#include<DirectXCollision.h>

//D3DXQUATERNIONをパック化したクラス//
typedef class ChQuaternion_11 :public DirectX::XMFLOAT4
{
public:

	ChQuaternion_11&operator=(const DirectX::XMFLOAT4& _cm);

	ChQuaternion_11&operator+=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator+(const DirectX::XMFLOAT4& _cm)const;
	ChQuaternion_11&operator-=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator-(const DirectX::XMFLOAT4& _cm)const;
	ChQuaternion_11&operator*=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator*(const DirectX::XMFLOAT4& _cm)const;
	ChQuaternion_11&operator/=(const DirectX::XMFLOAT4& _cm);
	ChQuaternion_11 operator/(const DirectX::XMFLOAT4& _cm)const;

	ChQuaternion_11&operator=(const DirectX::XMVECTOR& _cm);

	operator DirectX::XMVECTOR()const;

	ChQuaternion_11&operator = (const DirectX::XMFLOAT3& _vec);

	ChQuaternion_11&operator =(const DirectX::XMFLOAT4X4& _mat);

	///////////////////////////////////////////////////////////////////////////////////
	//ConstructerDestructer

	ChQuaternion_11()
	{
		Identity();
	}

	ChQuaternion_11(const DirectX::XMFLOAT4& _cm) :DirectX::XMFLOAT4(_cm) {}

	ChQuaternion_11(const DirectX::XMFLOAT4X4& _cm)
	{
		*this = _cm;

	}

	ChQuaternion_11(const  DirectX::XMFLOAT3& _cm)
	{
		*this = _cm;

	}

	ChQuaternion_11(
		const float _x,
		const float _y,
		const float _z,
		const float _w = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	///////////////////////////////////////////////////////////////////////////////////
	
	void RotYPR(const float _x, const float _y, const float _z);

	inline void RotYPR(const ChVec3& _vec)
	{
		RotYPR(_vec.x, _vec.y, _vec.z);
	}

	inline void RotYPR(const DirectX::XMFLOAT3& _vec)
	{
		RotYPR(_vec.x, _vec.y, _vec.z);
	}

	///////////////////////////////////////////////////////////////////////////////////

	void RotLookAt(
		const DirectX::XMFLOAT3& _pos
		, const DirectX::XMFLOAT3& _basePos);

	///////////////////////////////////////////////////////////////////////////////////

	void RotAxis(const DirectX::XMFLOAT3& _vec, const float _ang);

	///////////////////////////////////////////////////////////////////////////////////

	void RotMat(const DirectX::XMFLOAT4X4& _mat);

	///////////////////////////////////////////////////////////////////////////////////

	void Lerp(
		const ChQuaternion_11& _sQua,
		const ChQuaternion_11& _eQua,
		const float _NowTime);

	///////////////////////////////////////////////////////////////////////////////////

	void Identity();

	///////////////////////////////////////////////////////////////////////////////////

	void Inverse()
	{
		Inverse(*this);
	}

	void Inverse(const DirectX::XMFLOAT4& _qua)
	{
		ChQuaternion_11 tmpQua;
		tmpQua = _qua;
		Inverse(tmpQua);
	}

	void Inverse(const ChQuaternion_11& _qua);

private:

}ChQua_11;

#endif