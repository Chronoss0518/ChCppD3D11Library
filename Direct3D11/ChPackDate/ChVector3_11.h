#ifndef Ch_D3D11_Vec3_h
#define Ch_D3D11_Vec3_h

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#include<DirectXColors.h>
#include<DirectXMath.h>
#include<DirectXCollision.h>

//ƒpƒbƒN‰»‚µ‚½XFLOAT3(D3D11Vector)Œ^//
typedef class ChVector3_11 :public DirectX::XMFLOAT3
{
public://Operator Functions//

	ChVector3_11& operator=(const DirectX::XMFLOAT3& _cm);

	ChVector3_11& operator+=(const DirectX::XMFLOAT3& _cm);
	ChVector3_11 operator+(const DirectX::XMFLOAT3& _cm)const;
	ChVector3_11& operator-=(const DirectX::XMFLOAT3& _cm);
	ChVector3_11 operator-(const DirectX::XMFLOAT3& _cm)const;
	ChVector3_11& operator*=(const DirectX::XMFLOAT3& _cm);
	ChVector3_11 operator*(const DirectX::XMFLOAT3& _cm)const;
	ChVector3_11& operator/=(const DirectX::XMFLOAT3& _cm);
	ChVector3_11 operator/(const DirectX::XMFLOAT3& _cm)const;

	ChVector3_11& operator=(const float& _cm);
	ChVector3_11& operator+=(const float& _cm);
	ChVector3_11 operator+(const float& _cm)const;
	ChVector3_11& operator-=(const float& _cm);
	ChVector3_11 operator-(const float& _cm)const;
	ChVector3_11& operator*=(const float& _cm);
	ChVector3_11 operator*(const float& _cm)const;
	ChVector3_11& operator/=(const float& _cm);
	ChVector3_11 operator/(const float& _cm)const;

	ChVector3_11& operator=(const DirectX::XMVECTOR& _cm);

	operator DirectX::XMVECTOR()const;

	ChVector3_11& operator = (const DirectX::XMFLOAT4& _qua);
	ChVector3_11& operator = (const DirectX::XMFLOAT4X4& _mat);


public://Constructer Destructer//

	ChVector3_11(const DirectX::XMFLOAT3& _cm) :DirectX::XMFLOAT3(_cm) {}

	ChVector3_11()
	{
		Set0Param();
	}

	ChVector3_11(const DirectX::XMMATRIX& _mat)
	{
		*this = _mat;
	}

	ChVector3_11(const DirectX::XMFLOAT4& _qua)
	{
		*this = _qua;
	}

	ChVector3_11(const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	ChVector3_11(const float _num)
	{
		x = _num;
		y = _num;
		z = _num;
	}

public://Get Functions//

	float GetLen(const DirectX::XMFLOAT3& _Vec = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f))const;

	float GetRadian(
		const DirectX::XMFLOAT3& _vec1,
		const DirectX::XMFLOAT3& _vec2)const;

	float GetDegree(
		const DirectX::XMFLOAT3& _vec1,
		const DirectX::XMFLOAT3& _vec2)const;

	float GetDot(
		const DirectX::XMFLOAT3& _vec1,
		const DirectX::XMFLOAT3& _vec2)const;

public://Set Functions//

	void Set0Param();

	void SetLerp(
		const DirectX::XMFLOAT3& _sVec,
		const DirectX::XMFLOAT3& _eVec,
		const float _nowTime);

	void SetCrossVec(
		const DirectX::XMFLOAT3& _vec1,
		const DirectX::XMFLOAT3& _vec2);

public://Is Function//

	bool IsNormals()const;

	bool IsAll0()const;

public://Use Matrix Functions//

	void MatPos(
		const DirectX::XMMATRIX& _mat,
		const DirectX::XMFLOAT3& _vec = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));

	void MatNormal(
		const DirectX::XMMATRIX& _mat,
		const DirectX::XMFLOAT3& _vec = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f));

public://Other Functions//

	void Normalize();


}ChVec3_11;

#endif