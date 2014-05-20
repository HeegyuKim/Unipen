
#ifndef _Unipen_Maths_hpp_
#define _Unipen_Maths_hpp_


namespace unipen {
namespace maths {


inline float Clamp(float val, float min, float max) {
	if(val < min) return min;
	if(val > max) return max;
	else return val;
}
inline float Saturate(float val) {
	if(val < 0) return 0;
	if(val > 1) return 1;
	else return val;
}

}
}


#endif