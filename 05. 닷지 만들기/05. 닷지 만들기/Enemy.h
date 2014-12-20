
#ifndef _Enemy_h_
#define _Enemy_h_

#include "d2dutils.h"

// 적 캐릭터를 나타내는 클래스
class Enemy
{
public:
	// 적 객체의 종류
	enum Type {
		ALIEN,
		DEVIL,
		DRAGON,
		ENVOY,
		GHOST,
		PIRATE,
		TYPE_COUNT
	};
	
	inline Enemy(Type type)
		: type(type), 
		x(0), y(0), hx(0), hy(0),
		dx(0), dy(0)
	{}

	// 객체의 위치를 지정합니다.
	inline void SetPos(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	// 객체의 속도를 지정합니다.
	inline void SetVel(float dx, float dy)
	{
		this->dx = dx;
		this->dy = dy;
	}

	// 객체의 크기를 지정합니다.
	inline void SetSize(float width, float height)
	{
		this->hx = width / 2.0f;
		this->hy = height / 2.0f;
	}

	// delta의 시간이 흐른 만큼 이동합니다.
	inline void Update(float delta)
	{
		x += dx * delta;
		y += dy * delta;
	}
	
	// 위치 정보를 갖는 Rect값을 반환합니다.
	inline D2D1_RECT_F GetRect() const
	{
		return D2D1::RectF (
			x - hx,
			y - hy,
			x + hx,
			y + hy
			);
	}

	// 타입을 반환합니다.
	inline Type GetType() const
	{
		return type;
	}


private:
	float x, y;		// 위치
	float hx, hy;	// 가로/세로 크기의 절반
	float dx, dy;	// 이동속도
	Type type;		// 타입
};

#endif