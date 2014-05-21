
#ifndef _Unipen_Maths_h_
#define _Unipen_Maths_h_


#include "Entity.h"

#include <math.h>
#include <limits>

namespace unipen {
namespace maths {

/*!
 * ���� ������ ���� ���̷� �����Ͽ� ��ȯ�Ѵ�.
 * @param val ������ ��
 * @param min �ּ� ��
 * @param max �ִ� ��
 * @return ���ѵ� ��
 */
inline float Clamp(float val, float min, float max);

/*!
 * ���� 0���� 1������ ������ �����Ͽ� ��ȯ�Ѵ�.
 * @param val ������ ��
 * @return ���ѵ� ���� ��ȯ�Ѵ�.
 */
inline float Saturate(float val);

/*!
 * �ε��Ҽ��� ���� �ּ� ���̸� ��Ÿ���°��� �ԽǷ� ���� ��ȯ�Ѵ�.
 */
inline float Epsilon() _is(std::numeric_limits<float>::epsilon());

/*!
 * �� ���� ���̰� �ԽǷк��� ������ ���Ѵ�.
 * @param a ���� ��
 * @param b ���� ��
 * @return �� ���� ���̰� Epsilon���� ������ true �ƴϸ� false�� ��ȯ�Ѵ�.
 */
inline bool IsSimilar(float a, float b) _is(fabsf(a - b) < Epsilon());

/*!
 * �� ���� ���̰� �ԽǷк��� ū�� ���Ѵ�.
 * @param a ���� ��
 * @param b ���� ��
 * @return �� ���� ���̰� Epsilon���� ũ�� true �ƴϸ� false�� ��ȯ�Ѵ�.
 */
inline bool IsNotSimilar(float a, float b) _is(fabsf(a - b) > Epsilon());


}
}

#endif