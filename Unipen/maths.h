
#ifndef _Unipen_Maths_h_
#define _Unipen_Maths_h_


#include "Entity.h"

#include <math.h>
#include <limits>

namespace unipen {
namespace maths {

/*!
 * 값을 지정된 범위 사이로 제한하여 반환한다.
 * @param val 제한한 값
 * @param min 최소 값
 * @param max 최대 값
 * @return 제한된 값
 */
inline float Clamp(float val, float min, float max);

/*!
 * 값은 0부터 1사이의 값으로 제한하여 반환한다.
 * @param val 제한한 값
 * @return 제한된 값을 반환한다.
 */
inline float Saturate(float val);

/*!
 * 부동소수점 값의 최소 차이를 나타내는값인 입실론 값을 반환한다.
 */
inline float Epsilon() _is(std::numeric_limits<float>::epsilon());

/*!
 * 두 수의 차이가 입실론보다 작은지 비교한다.
 * @param a 비교할 값
 * @param b 비교할 값
 * @return 두 값의 차이가 Epsilon보다 작으면 true 아니면 false를 반환한다.
 */
inline bool IsSimilar(float a, float b) _is(fabsf(a - b) < Epsilon());

/*!
 * 두 수의 차이가 입실론보다 큰지 비교한다.
 * @param a 비교할 값
 * @param b 비교할 값
 * @return 두 값의 차이가 Epsilon보다 크면 true 아니면 false를 반환한다.
 */
inline bool IsNotSimilar(float a, float b) _is(fabsf(a - b) > Epsilon());


}
}

#endif