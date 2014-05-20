
#ifndef _Unipen_Entity_h_
#define _Unipen_Entity_h_


#define _is(val) { return val; }
#define _do_me(exp) { exp; return *this; }

namespace unipen {


class Entity {
public:
	virtual ~Entity(){}

};

}
#endif