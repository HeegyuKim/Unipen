
#ifndef _Unipen_Entity_h_
#define _Unipen_Entity_h_

#include <exception>
#define _is(val) { return val; }
#define _do(exp) { exp; }
#define _do_me(exp) { exp; return *this; }

namespace unipen {


class Entity {
public:
	virtual ~Entity(){}

};

template <typename T>
inline void SafeRelease(T t) 
{
	if(t)
		t->Release();
}

}
#endif