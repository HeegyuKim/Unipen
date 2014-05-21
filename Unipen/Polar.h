
#ifndef _Unipen_Polar_h_
#define _Unipen_Polar_h_

#include "Entity.h"
#include "Vector2.h"
#include "Units.h"

namespace unipen {

class Polar {
public:
	float length;
	float radians;


	inline Polar& rotate(float angle) _do_me(radians += angle; radians = units::RefineRadians(radians));
	inline Polar& scale(float ratio) _do_me(length *= ratio);
};

}


#endif