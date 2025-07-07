#ifndef Ch_D3D11_ChMat_h
#define Ch_D3D11_ChMat_h

#ifndef _XM_NO_INTRINSICS_
#define _XM_NO_INTRINSICS_
#endif

#include<DirectXColors.h>
#include<DirectXMath.h>
#include<DirectXCollision.h>

//D3DXMATRIXをパック化したクラス//
typedef class ChMatrix_11 :public DirectX::XMFLOAT4X4
{
public://Operator Functions//

	ChMatrix_11&operator=(const DirectX::XMFLOAT4X4& _cm);

	ChMatrix_11&operator+=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator+(const DirectX::XMFLOAT4X4& _cm)const;
	ChMatrix_11&operator-=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator-(const DirectX::XMFLOAT4X4& _cm)const;
	ChMatrix_11&operator*=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator*(const DirectX::XMFLOAT4X4& _cm)const;
	ChMatrix_11&operator/=(const DirectX::XMFLOAT4X4& _cm);
	ChMatrix_11 operator/(const DirectX::XMFLOAT4X4& _cm)const;

	ChMatrix_11&operator=(const float& _cm);
	ChMatrix_11&operator*=(const float& _cm);
	ChMatrix_11 operator*(const float& _cm)const;
	ChMatrix_11&operator/=(const float& _cm);
	ChMatrix_11 operator/(const float& _cm)const;

	ChMatrix_11&operator=(const DirectX::XMMATRIX& _cm);

	operator DirectX::XMMATRIX()const;

	operator DirectX::XMFLOAT4X4()const;

	ChMatrix_11&operator = (const DirectX::XMFLOAT3& _vec);

	ChMatrix_11&operator =(const DirectX::XMFLOAT4& _qua);

public://Constructer Destructer//

	inline ChMatrix_11(const DirectX::XMFLOAT4X4& _cm) : DirectX::XMFLOAT4X4(_cm) {}

	inline ChMatrix_11(const DirectX::XMMATRIX& _cm) { *this = _cm; }

	inline ChMatrix_11() { Identity(); }

	inline ChMatrix_11(const DirectX::XMFLOAT3& _vec) { *this = _vec; }

	inline ChMatrix_11(const DirectX::XMFLOAT4& _qua) { *this = _qua; }

public://Set Functions//

	void SetPosition(const DirectX::XMFLOAT3& _pos);
	
	void SetRotation(const DirectX::XMFLOAT3& _rot);
	
	void SetScaleSize(const DirectX::XMFLOAT3& _sca);

public://Get Functions//

	DirectX::XMFLOAT3 GetPosition()const;

	DirectX::XMFLOAT4 GetRotation()const;

	DirectX::XMFLOAT3 GetScaleSize()const;

public://Other Functions//

	inline void Identity() { *this = DirectX::XMMatrixIdentity(); }

	inline void Inverse() { Inverse(*this); }

	void Inverse(const DirectX::XMFLOAT4X4& _mat);

	void RotYPR(const float _x, const float _y, const float _z);

	void RotYPR(const DirectX::XMFLOAT3& _vec);

	void RotQua(const DirectX::XMFLOAT4& _qua);

	void RotQua(const float _x, const float _y, const float _z);

	void RotVec(const DirectX::XMFLOAT3& _vec);

	void RotAxis(const DirectX::XMFLOAT3& _vec, const float _Ang);

	inline void Trans(const float _x, const float _y, const float _z) { *this = DirectX::XMMatrixTranslation(_x, _y, _z); }

	inline void Trans(const DirectX::XMFLOAT3& _vec) { *this = DirectX::XMMatrixTranslation(_vec.x, _vec.y, _vec.z); }

	inline void VectorMove(const DirectX::XMFLOAT3& _vec)
	{
		this->_41 += _vec.x;
		this->_42 += _vec.y;
		this->_43 += _vec.z;
	}

	inline void Move(const float _x, const float _y, const float _z)
	{
		ChMatrix_11 tmpMat;
		tmpMat.Trans(_x, _y, _z);
		*this = tmpMat * *this;
	}

	void Scaling(
		const float _x,
		const float _y,
		const float _z);

	inline void Scaling(const DirectX::XMFLOAT3& _tmpVec) { Scaling(_tmpVec.x, _tmpVec.y, _tmpVec.z); }

	inline void Scaling(const float _scl) { Scaling(_scl, _scl, _scl); }

	void CreateViewMat(const ChVec3& _pos,const ChVec3& _dir,const ChVec3& _up);

	void CreateViewMatLookTarget(const ChVec3& _pos, const ChVec3& _targetPos, const ChVec3& _up);

	//透視投影射影行列を作成//
	inline void CreateProjectionMat(
		const float _lookAngleRadian,
		const float _windWidth,
		const float _windHeight,
		const float _nearZ,
		const float _farZ)
	{
		*this = DirectX::XMMatrixPerspectiveFovLH(
			_lookAngleRadian
			, _windWidth/ _windHeight
			, _nearZ
			, _farZ);
	}

	//直交射影行列を作成//
	inline void CreateProjectionMat(
		const float _windWidth,
		const float _windHeight,
		const float _nearZ,
		const float _farZ)
	{
		*this = DirectX::XMMatrixOrthographicLH(
			_windWidth,
			_windHeight,
			_nearZ,
			_farZ);
	}

	//座標系変換//
	inline ChMatrix_11 Transpose() const
	{
		ChMatrix_11 tmp;

		tmp = DirectX::XMMatrixTranspose(*this);

		return tmp;
	}

private:

}ChMat_11;


#endif