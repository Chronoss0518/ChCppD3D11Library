
#include"../../BasePack/ChMath3D.h"

#include"ChVector3_11.h"



ChVector3_11& ChVector3_11::operator=(const DirectX::XMFLOAT3& _cm)
{
	if (this == &_cm)return *this;
	DirectX::XMFLOAT3::operator=(_cm);
	return *this;
}

ChVector3_11& ChVector3_11::operator+=(const DirectX::XMFLOAT3& _cm)
{
	x += _cm.x;
	y += _cm.y;
	z += _cm.z;
	return *this;
}

ChVector3_11 ChVector3_11::operator+(const DirectX::XMFLOAT3& _cm)const
{
	ChVector3_11 out = *this;
	out += _cm;
	return out;
}

ChVector3_11& ChVector3_11::operator-=(const DirectX::XMFLOAT3& _cm)
{
	x -= _cm.x;
	y -= _cm.y;
	z -= _cm.z;
	return *this;
}

ChVector3_11 ChVector3_11::operator-(const DirectX::XMFLOAT3& _cm)const
{
	ChVector3_11 out = *this;
	out -= _cm;
	return out;
}

ChVector3_11& ChVector3_11::operator*=(const DirectX::XMFLOAT3& _cm)
{
	x *= _cm.x;
	y *= _cm.y;
	z *= _cm.z;
	return *this;
}

ChVector3_11 ChVector3_11::operator*(const DirectX::XMFLOAT3& _cm)const
{
	ChVector3_11 out = *this;
	out *= _cm;
	return out;
}

ChVector3_11& ChVector3_11::operator/=(const DirectX::XMFLOAT3& _cm)
{
	x /= _cm.x != 0.0f ? _cm.x : 1.0f;
	y /= _cm.y != 0.0f ? _cm.y : 1.0f;
	z /= _cm.z != 0.0f ? _cm.z : 1.0f;
	return *this;
}

ChVector3_11 ChVector3_11::operator/(const DirectX::XMFLOAT3& _cm)const
{
	ChVector3_11 out = *this;
	out /= _cm;
	return out;
}

ChVector3_11& ChVector3_11::operator=(const float& _cm)
{
	x = _cm;
	y = _cm;
	z = _cm;
	return *this;
}

ChVector3_11& ChVector3_11::operator+=(const float& _num)
{
	x += _num;
	y += _num;
	z += _num;
	return *this;
}

ChVector3_11 ChVector3_11::operator+(const float& _num)const
{
	ChVector3_11 out = *this;
	out += _num;
	return out;
}

ChVector3_11& ChVector3_11::operator-=(const float& _num)
{
	x -= _num;
	y -= _num;
	z -= _num;
	return *this;
}

ChVector3_11 ChVector3_11::operator-(const float& _num)const
{
	ChVector3_11 out = *this;
	out -= _num;
	return out;
}

ChVector3_11& ChVector3_11::operator*=(const float& _num)
{
	x *= _num;
	y *= _num;
	z *= _num;
	return *this;
}

ChVector3_11 ChVector3_11::operator*(const float& _num)const
{
	ChVector3_11 out = *this;
	out *= _num;
	return out;
}

ChVector3_11& ChVector3_11::operator/=(const float& _num)
{
	if (_num == 0.0f)return *this;
	x /= _num;
	y /= _num;
	z /= _num;
	return *this;
}

ChVector3_11 ChVector3_11::operator/(const float& _num)const
{
	ChVector3_11 out = *this;
	out /= _num;
	return out;
}

ChVector3_11& ChVector3_11::operator=(const DirectX::XMVECTOR& _cm)
{
	DirectX::XMStoreFloat3(this, _cm);
	return *this;
}

ChVector3_11::operator DirectX::XMVECTOR()const
{
	DirectX::XMVECTOR tmp;
	tmp = DirectX::XMLoadFloat3(this);
	return tmp;
}

ChVector3_11& ChVector3_11::operator = (const DirectX::XMFLOAT4& _qua)
{
	DirectX::XMMATRIX tmpMat;
	DirectX::XMVECTOR tmpVec;
	tmpVec = DirectX::XMLoadFloat4(&_qua);
	tmpMat = DirectX::XMMatrixRotationQuaternion(tmpVec);
	*this = DirectX::XMVector3TransformNormal(ChVector3_11(0.0f, 0.0f, 1.0f), tmpMat);
	return *this;
}

ChVector3_11& ChVector3_11::operator =(const DirectX::XMFLOAT4X4& _mat)
{
	x = _mat._41;
	y = _mat._42;
	z = _mat._43;
	return *this;
}

float ChVector3_11::GetLen(const DirectX::XMFLOAT3& _vec)const
{
	DirectX::XMVECTOR tmpVec;
	tmpVec = *this - _vec;

	float tmp;
	tmpVec = DirectX::XMVector3Length(tmpVec);
	DirectX::XMStoreFloat(&tmp, DirectX::XMVector3Length(tmpVec));

	return tmp;
}

float ChVector3_11::GetRadian(
	const DirectX::XMFLOAT3& _vec1,
	const DirectX::XMFLOAT3& _vec2)const
{
	ChVector3_11 tmpVec1, tmpVec2;
	tmpVec1 = _vec1;
	tmpVec2 = _vec2;

	tmpVec1 = DirectX::XMVector3Normalize(tmpVec1);
	tmpVec2 = DirectX::XMVector3Normalize(tmpVec2);

	return ChMath::GetACos(GetDot(tmpVec1, tmpVec2));
}

float ChVector3_11::GetDegree(
	const DirectX::XMFLOAT3& _vec1,
	const DirectX::XMFLOAT3& _vec2)const
{
	ChVector3_11 tmpVec1, tmpVec2;
	tmpVec1 = _vec1;
	tmpVec2 = _vec2;

	tmpVec1 = DirectX::XMVector3Normalize(tmpVec1);
	tmpVec2 = DirectX::XMVector3Normalize(tmpVec2);

	return ChMath::ToDegree(acosf(GetDot(tmpVec1, tmpVec2)));
}

float ChVector3_11::GetDot(
	const DirectX::XMFLOAT3& _vec1,
	const DirectX::XMFLOAT3& _vec2)const
{
	ChVector3_11 tmpVec1, tmpVec2;
	tmpVec1 = _vec1;
	tmpVec2 = _vec2;

	float tmp;
	DirectX::XMStoreFloat(&tmp, DirectX::XMVector3Dot(tmpVec1, tmpVec2));

	return tmp;
}

void ChVector3_11::Set0Param() { *this = 0; }

void ChVector3_11::SetLerp(
	const DirectX::XMFLOAT3& _sVec,
	const DirectX::XMFLOAT3& _eVec,
	const float _nowTime)
{
	ChVector3_11 stmp = _sVec;
	ChVector3_11 tmp = _eVec;
	tmp = tmp - _sVec;
	tmp *= _nowTime;
	tmp = stmp + tmp;
	*this = tmp;
}

void ChVector3_11::SetCrossVec(const DirectX::XMFLOAT3& _vec1, const DirectX::XMFLOAT3& _vec2)
{
	ChVector3_11 tmpVec1, tmpVec2;
	tmpVec1 = _vec1;
	tmpVec2 = _vec2;
	auto tmp = DirectX::XMVector3Cross(tmpVec1, tmpVec2);
	*this = tmp;
}

bool ChVector3_11::IsNormals()const { return (GetLen() == 1.0f); }

bool ChVector3_11::IsAll0()const { return (x == 0.0f && y == 0.0f && z == 0.0f); }

void ChVector3_11::MatPos(
	const DirectX::XMMATRIX& _mat,
	const DirectX::XMFLOAT3& _vec)
{
	ChVector3_11 tmpVec;
	tmpVec = _vec;
	auto tmp = DirectX::XMVector3TransformCoord(tmpVec, _mat);
	*this = tmp;
}

void ChVector3_11::MatNormal(
	const DirectX::XMMATRIX& _mat,
	const DirectX::XMFLOAT3& _vec)
{
	ChVector3_11 tmpVec;
	tmpVec = _vec;
	auto tmp = DirectX::XMVector3TransformNormal(tmpVec, _mat);
	*this = tmp;
}

void ChVector3_11::Normalize()
{
	float tmpLen = GetLen();

	if (tmpLen <= 0.0f)
	{
		*this = ChVector3_11(0.0f, 0.0f, 1.0f);
		return;
	}

	if (IsNormals())return;

	DirectX::XMVECTOR tmpVec;
	tmpVec = *this;
	*this = DirectX::XMVector3Normalize(tmpVec);
}

///////////////////////////////////////////////////////////////////////////////////
//ChVector3Operator//
///////////////////////////////////////////////////////////////////////////////////

ChVec3::operator const DirectX::XMFLOAT3()const
{
	DirectX::XMFLOAT3 tmpVec;
	tmpVec.x = x;
	tmpVec.y = y;
	tmpVec.z = z;

	return tmpVec;
}

ChVec3::operator const DirectX::XMFLOAT3* ()const { return reinterpret_cast<DirectX::XMFLOAT3*>(const_cast<ChVec3*>(this)); }

ChVec3& ChVec3::operator= (const DirectX::XMFLOAT3& _vec)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;

	return *this;
}

ChVec3& ChVec3::operator= (const DirectX::XMFLOAT4& _qua)
{
	ChVector3_11 tmp;
	tmp = _qua;
	*this = tmp;
	return *this;
}

ChVec3& ChVec3::operator= (const DirectX::XMFLOAT4X4& _mat)
{
	ChVector3_11 tmp;
	tmp = _mat;
	*this = tmp;
	return *this;
}
