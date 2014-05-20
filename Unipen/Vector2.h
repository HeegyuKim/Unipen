
#ifndef _Unipen_Vector2_h_
#define _Unipen_Vector2_h_

#include "Entity.h"
#include "Polar.h"
#include "Units.h"
#include "Maths.h"


#include <D2D1.h>

namespace unipen {

/**
	2���� ���͸� ��Ÿ���� Ŭ�����̴�.
	���Ͱ��� ��Ģ����� ��Į�� ����, �׸��� ����, ����,
	�ݻ�, ���� ���, ����ȭ�� ���� ������ �����Ѵ�.
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
		�⺻ ������, � �ʱ�ȭ�� �������� �ʴ´�.
	*/
	inline Vector2(){}
	
	/**
		x�� y�� ���ڷ� �޴� ������
	*/
	inline Vector2(float x, float y) : x(x), y(y){}

	/**
		�迭�� ���ڷ� �޴� ������.
	*/
	inline Vector2(float *arr) : x(arr[0]), y(arr[1]){}

	/**
		���Ϳ� ���͸� ���� ����� ��ȯ�Ѵ�.
	*/
	inline Vector2 operator+ (const Vector2& that) const _is(Vector2(x + that.x, y + that.y));

	/**
		���Ϳ� ���͸� �� ����� ��ȯ�Ѵ�.
	*/
	inline Vector2 operator- (const Vector2& that) const _is(Vector2(x - that.x, y - that.y));;

	/**
		���Ϳ� ������ �� ���Ҹ� ���� ���͸� ��ȯ�Ѵ�.
	*/
	inline Vector2 operator* (const Vector2& that) const _is(Vector2(x * that.x, y * that.y));;

	/**
		���Ϳ� ��Į�� ������ �� ����� ��ȯ�Ѵ�.
	*/
	inline Vector2 operator* (float that) const _is(Vector2(x * that, y * that));

	/**
		���Ϳ� ��Į�� �������� �� ����� ��ȯ�Ѵ�.
	*/
	inline Vector2 operator/ (float that) const _is(Vector2(x / that, y / that));
	



	/**
		���Ϳ� ���͸� ���Ѵ�.
	*/
	inline Vector2& operator+= (const Vector2& that);
	
	/**
		���Ϳ� ���͸� ����.
	*/
	inline Vector2& operator-= (const Vector2& that);
	
	/**
		���Ϳ� ������ �� ���Ҹ� ���Ѵ�.
	*/
	inline Vector2& operator*= (const Vector2& that);

	inline Vector2& operator*= (float that);
	inline Vector2& operator/= (float that);

	
	/**
		�ݴ������ ���͸� ����Ѵ�.
	*/
	inline Vector2 operator- () const _is(Vector2(-x, -y))


	/**
		������ @index��°�� ��Ҹ� ����Ѵ�.
	*/
	inline float operator[](int index) const _is(e[index])

	/**
		������ @index��°�� ����� �����ڸ� ��ȯ�Ѵ�.
	*/
	inline float& operator[](int index) _is(e[index])



	/**
		������ ���̸� ��ȯ�Ѵ�.
	*/
	inline float length() const _is(sqrtf(x * x + y * y))
	
	/**
		������ ������ ������ ��ȯ�Ѵ�.
	*/
	inline float sqrlen() const _is(x * x + y * y)


	/**
		������ ������ ����Ѵ�.
	*/
	inline float dot(const Vector2& that) const _is(x * that.x + y * that.y)


	/**
		�ݻ� ���͸� ����Ѵ�.
	*/
	inline Vector2 reflect(const Vector2& normal) const;


	/**
		���� ���͸� ����Ѵ�.
	*/
	inline Vector2 refract(const Vector2& normal, float coeffcient);


	/**
		������ ������ ����Ѵ�.
	*/
	inline Vector2 cross() const _is(Vector2(y, -x));

	/**
		�� ���͸� ����ȭ�Ѵ�.
	*/
	inline Vector2& normalize();

	/**
		�� ���͸� �����Ѵ�.
		@param length ������ ����
	*/
	inline Vector2& truncate(float length);

	/**
	 * ������ ���� ������ ������ �����Ѵ�.
	 * @param min ������ �ּҰ�
	 * @param max ������ �ִ밪
	 * @return ���� ���ѵ� �ڱ��ڽ�
	 */
	inline Vector2& clamp(float min, float max)
		_do_me(x = maths::Clamp(x, min, max);
				y = maths::Clamp(y, min, max));

	
	/**
	 * ������ ���� 0���� 1������ ������ �����Ѵ�.
	 * @return ���� ���ѵ� �ڱ��ڽ�
	 */
	inline Vector2& saturate()
		_do_me(x = maths::Saturate(x);
				y = maths::Saturate(y));

	/**
		float* Ÿ������ ĳ�����Ѵ�.
	*/
	inline operator float*() _is(e)

	/**
		const float* Ÿ������ ĳ�����Ѵ�.
	*/
	inline operator const float*() const _is(e)

	/**
		D2D1_POINT_2F Ÿ������ ĳ�����Ѵ�.
	*/
	inline operator D2D1_POINT_2F&() _is(p)

	/**
		const D2D1_POINT_2F& Ÿ������ ĳ�����Ѵ�.
	*/
	inline operator const D2D1_POINT_2F&() const _is(p)

	/**
	 * �� ������ ���� �������� Ȯ���Ѵ�.
	 * @param that ���� ����
	 * @return �� ���Ͱ� �����ϸ� true��, �׷��� ������ false�� ��ȯ�Ѵ�.
	 */
	inline bool operator== (const Vector2& that) _is(maths::IsSimilar(x, that.x) && maths::IsSimilar(y, that.y));

	/**
	 * �� ������ ���� �������� ������ Ȯ���Ѵ�.
	 * @param that ���� ����
	 * @return �� ���Ͱ� �������� ������ true��, �׷��� ������ false�� ��ȯ�Ѵ�.
	 */
	inline bool operator!= (const Vector2& that) _is(maths::IsNotSimilar(x, that.x) || maths::IsNotSimilar(y, that.y));
};

/**
	* ������ ���̸� �ִ� ���̷� �����Ѵ�.
	* @param v ���̸� ������ ����
	* @param length ������ �ִ� ����
	* @return ���̰� ���ѵ� ����
	*/
inline Vector2 Truncate(const Vector2& v, float length);

/**
	* ���͸� ����ȭ�ؼ� ��ȯ�Ѵ�.
	* @param v ����ȭ�� ����
	* @return ����ȭ�� ����
	*/
inline Vector2 Normalize(const Vector2& v);
	
/**
	* ������ ���� ������ ����� ��ȯ�Ѵ�.
	* @param min ������ ���� ���� ��.
	* @param max ������ ���� ū ��.
	* @return ���� ���ѵ� ����
	*/
inline Vector2 Clamp(const Vector2& v, float min, float max)
	_is(Vector2(maths::Clamp(v.x, min, max),
				maths::Clamp(v.y, min, max)));

/**
	* ������ ���� 0���� 1���̷� ������ ����� ��ȯ�Ѵ�.
	* @return ���� ���ѵ� ����
	*/
inline Vector2 Saturate(const Vector2& v)
	_is(Vector2(maths::Saturate(v.x),
				maths::Saturate(v.y)));
}
/**
	���Ϳ� ��Į�� ������ �����Ѵ�.
*/
inline unipen::Vector2 operator* (float that, const unipen::Vector2& v) _is(v * that)


/**
	���Ϳ� ��Į�� �������� �����Ѵ�.
*/
inline unipen::Vector2 operator/ (float that, const unipen::Vector2& v) _is(v / that)
	

#include "Vector2.hpp"

#endif