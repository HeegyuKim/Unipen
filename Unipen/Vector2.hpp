

#ifndef _Unipen_Vector2_hpp_
#define _Unipen_Vector2_hpp_


#include "Vector2.hpp"


namespace unipen {
	

inline Vector2& Vector2::operator+= (const Vector2& that) {
	x += that.x;
	y += that.y;
	return *this;
}
inline Vector2& Vector2::operator-= (const Vector2& that) {
	x -= that.x;
	y -= that.y;
	return *this;
}
inline Vector2& Vector2::operator*= (const Vector2& that) {
	x *= that.x;
	y *= that.y;
	return *this;
}

inline Vector2& Vector2::operator*= (float that) {
	x *= that;
	y *= that;
	return *this;
}
inline Vector2& Vector2::operator/= (float that) {
	x /= that;
	y /= that;
	return *this;
}

/**
	�ݻ� ���͸� ����Ѵ�.
*/
inline Vector2 Vector2::reflect(const Vector2& normal) const { 
	Vector2 ref = normal;
	ref *= 2 * dot(ref);
	ref += *this;
	return ref;
}


/**
	���� ���͸� ����Ѵ�.
	�� �������� �ʾ���.
*/
inline Vector2 Vector2::refract(const Vector2& normal, float coeffcient) {
	Vector2 ref = normal;
	ref *= coeffcient * dot(ref);
	ref += *this;
	return ref;
}

/**
	�� ���͸� ����ȭ�Ѵ�.
*/
inline Vector2& Vector2::normalize() {
	float len = length();
	*this /= len;
	return *this;
}


/**
	�� ���͸� �����Ѵ�.
	@param length ������ ����
*/
inline Vector2& Vector2::truncate(float length) {
	float mylen = this->length();
	if(mylen > length) {
		normalize();
		*this *= length;
	}
	return *this;
}

/**
* ������ ���̸� �ִ� ���̷� �����Ѵ�.
* @param v ���̸� ������ ����
* @param length ������ �ִ� ����
* @return ���̰� ���ѵ� ����
*/
inline Vector2 Truncate(const Vector2& v, float length) {
	float vlen = v.length();

	if(vlen > length) {
		Vector2 n = Normalize(v);
		return n * length;
	}
	else
		return v;
}

/**
* ���͸� ����ȭ�ؼ� ��ȯ�Ѵ�.
* @param v ����ȭ�� ����
* @return ����ȭ�� ����
*/
inline Vector2 Normalize(const Vector2& v) {
	float length = v.length();
	return Vector2(v.x / length, v.y / length);
}



}



#endif