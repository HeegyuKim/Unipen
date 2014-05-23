

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
	반사 벡터를 계산한다.
*/
inline Vector2 Vector2::reflect(const Vector2& normal) const { 
	Vector2 ref = normal;
	ref *= 2 * dot(ref);
	ref += *this;
	return ref;
}


/**
	굴절 벡터를 계산한다.
	다 구현되지 않았음.
*/
inline Vector2 Vector2::refract(const Vector2& normal, float coeffcient) {
	Vector2 ref = normal;
	ref *= coeffcient * dot(ref);
	ref += *this;
	return ref;
}

/**
	이 벡터를 정규화한다.
*/
inline Vector2& Vector2::normalize() {
	float len = length();
	*this /= len;
	return *this;
}


/**
	이 벡터를 절단한다.
	@param length 절단할 길이
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
* 벡터의 길이를 최대 길이로 제한한다.
* @param v 길이를 제한할 벡터
* @param length 제한할 최대 길이
* @return 길이가 제한된 벡터
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
* 벡터를 정규화해서 반환한다.
* @param v 정규화할 벡터
* @return 정규화된 벡터
*/
inline Vector2 Normalize(const Vector2& v) {
	float length = v.length();
	return Vector2(v.x / length, v.y / length);
}



}



#endif