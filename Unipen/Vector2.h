
#ifndef _Unipen_Vector2_h_
#define _Unipen_Vector2_h_

#include "Entity.h"
#include "Polar.h"
#include "Units.h"
#include "Maths.h"


#include <D2D1.h>

namespace unipen {

/**
	2차원 벡터를 나타내는 클래스이다.
	벡터간의 사칙연산과 스칼라 곱셈, 그리고 내적, 외적,
	반사, 길이 계산, 정규화와 같은 연산을 수행한다.
*/
class Vector2 : public Entity {
public:
	union {
		
		D2D1_POINT_2F p;
		
		float e[2];
		
		struct {
			float x;
			float y;
		};
	};



public:
	/**
		기본 생성자, 어떤 초기화도 수행하지 않는다.
	*/
	inline Vector2(){}
	
	/**
		x와 y를 인자로 받는 생성자
	*/
	inline Vector2(float x, float y) : x(x), y(y){}

	/**
		배열을 인자로 받는 생성자.
	*/
	inline Vector2(float *arr) : x(arr[0]), y(arr[1]){}

	/**
		벡터에 벡터를 더한 결과를 반환한다.
	*/
	inline Vector2 operator+ (const Vector2& that) const _is(Vector2(x + that.x, y + that.y));

	/**
		벡터에 벡터를 뺀 결과를 반환한다.
	*/
	inline Vector2 operator- (const Vector2& that) const _is(Vector2(x - that.x, y - that.y));;

	/**
		벡터에 벡터의 각 원소를 곱한 벡터를 반환한다.
	*/
	inline Vector2 operator* (const Vector2& that) const _is(Vector2(x * that.x, y * that.y));;

	/**
		벡터에 스칼라 곱셈을 한 결과를 반환한다.
	*/
	inline Vector2 operator* (float that) const _is(Vector2(x * that, y * that));

	/**
		벡터에 스칼라 나눗셈을 한 결과를 반환한다.
	*/
	inline Vector2 operator/ (float that) const _is(Vector2(x / that, y / that));
	



	/**
		벡터에 벡터를 더한다.
	*/
	inline Vector2& operator+= (const Vector2& that);
	
	/**
		벡터에 벡터를 뺀다.
	*/
	inline Vector2& operator-= (const Vector2& that);
	
	/**
		벡터에 벡터의 각 원소를 곱한다.
	*/
	inline Vector2& operator*= (const Vector2& that);

	inline Vector2& operator*= (float that);
	inline Vector2& operator/= (float that);

	
	/**
		반대방향의 벡터를 계산한다.
	*/
	inline Vector2 operator- () const _is(Vector2(-x, -y))


	/**
		벡터의 @index번째의 요소를 계산한다.
	*/
	inline float operator[](int index) const _is(e[index])

	/**
		벡터의 @index번째의 요소의 참조자를 반환한다.
	*/
	inline float& operator[](int index) _is(e[index])



	/**
		벡터의 길이를 반환한다.
	*/
	inline float length() const _is(sqrtf(x * x + y * y))
	
	/**
		벡터의 길이의 제곱을 반환한다.
	*/
	inline float sqrlen() const _is(x * x + y * y)


	/**
		벡터의 내적을 계산한다.
	*/
	inline float dot(const Vector2& that) const _is(x * that.x + y * that.y)


	/**
		반사 벡터를 계산한다.
	*/
	inline Vector2 reflect(const Vector2& normal) const;


	/**
		굴절 벡터를 계산한다.
	*/
	inline Vector2 refract(const Vector2& normal, float coeffcient);


	/**
		벡터의 외적을 계산한다.
	*/
	inline Vector2 cross() const _is(Vector2(y, -x));

	/**
		이 벡터를 정규화한다.
	*/
	inline Vector2& normalize();

	/**
		이 벡터를 절단한다.
		@param length 절단할 길이
	*/
	inline Vector2& truncate(float length);

	/**
	 * 벡터의 값을 지정된 범위로 제한한다.
	 * @param min 제한할 최소값
	 * @param max 제한할 최대값
	 * @return 값이 제한된 자기자신
	 */
	inline Vector2& clamp(float min, float max)
		_do_me(x = maths::Clamp(x, min, max);
				y = maths::Clamp(y, min, max));

	
	/**
	 * 벡터의 값을 0부터 1사이의 값으로 제한한다.
	 * @return 값이 제한된 자기자신
	 */
	inline Vector2& saturate()
		_do_me(x = maths::Saturate(x);
				y = maths::Saturate(y));

	/**
		float* 타입으로 캐스팅한다.
	*/
	inline operator float*() _is(e)

	/**
		const float* 타입으로 캐스팅한다.
	*/
	inline operator const float*() const _is(e)

	/**
		D2D1_POINT_2F 타입으로 캐스팅한다.
	*/
	inline operator D2D1_POINT_2F&() _is(p)

	/**
		const D2D1_POINT_2F& 타입으로 캐스팅한다.
	*/
	inline operator const D2D1_POINT_2F&() const _is(p)

	/**
	 * 두 벡터의 값이 유사한지 확인한다.
	 * @param that 비교할 벡터
	 * @return 두 벡터가 유사하면 true를, 그렇지 않으면 false를 반환한다.
	 */
	inline bool operator== (const Vector2& that) _is(maths::IsSimilar(x, that.x) && maths::IsSimilar(y, that.y));

	/**
	 * 두 벡터의 값이 유사하지 않은지 확인한다.
	 * @param that 비교할 벡터
	 * @return 두 벡터가 유사하지 않으면 true를, 그렇지 않으면 false를 반환한다.
	 */
	inline bool operator!= (const Vector2& that) _is(maths::IsNotSimilar(x, that.x) || maths::IsNotSimilar(y, that.y));
};

/**
	* 벡터의 길이를 최대 길이로 제한한다.
	* @param v 길이를 제한할 벡터
	* @param length 제한할 최대 길이
	* @return 길이가 제한된 벡터
	*/
inline Vector2 Truncate(const Vector2& v, float length);

/**
	* 벡터를 정규화해서 반환한다.
	* @param v 정규화할 벡터
	* @return 정규화된 벡터
	*/
inline Vector2 Normalize(const Vector2& v);
	
/**
	* 벡터의 값을 제한한 결과를 반환한다.
	* @param min 제한할 가장 작은 값.
	* @param max 제한할 가장 큰 값.
	* @return 값이 제한된 벡터
	*/
inline Vector2 Clamp(const Vector2& v, float min, float max)
	_is(Vector2(maths::Clamp(v.x, min, max),
				maths::Clamp(v.y, min, max)));

/**
	* 벡터의 값을 0부터 1사이로 제한한 결과를 반환한다.
	* @return 값이 제한된 벡터
	*/
inline Vector2 Saturate(const Vector2& v)
	_is(Vector2(maths::Saturate(v.x),
				maths::Saturate(v.y)));
}
/**
	벡터와 스칼라 곱셈을 수행한다.
*/
inline unipen::Vector2 operator* (float that, const unipen::Vector2& v) _is(v * that)


/**
	벡터와 스칼라 나눗셈을 수행한다.
*/
inline unipen::Vector2 operator/ (float that, const unipen::Vector2& v) _is(v / that)
	

#include "Vector2.hpp"

#endif