
#ifndef _Player_h_
#define _Player_h_


#include "d2dutils.h"


class Player
{
public:
	inline void Set(float x, float y, 
		float width, float height,
		float dx, float dy)
	{
		this->x = x;
		this->y = y;
		this->hx = width / 2.0f;
		this->hy = height / 2.0f;
		this->dx = dx;
		this->dy = dy;
	}

	inline D2D1_RECT_F GetRect() const
	{
		return D2D1::RectF (
			x - hx, y - hy,
			x + hx, y + hy );
	}

	// 이 함수는 충돌 영역의 경계 상자를 반환합니다.
	// 충돌 영역은 실제로 그려지는 영역보다 작게 했습니다.
	inline D2D1_RECT_F GetCollisionRect() const
	{
		float hhx = hx / 2,
			hhy = hy / 2;
		return D2D1::RectF (
			x - hhx, y - hhy,
			x + hhx, y + hhy
			);
	}
public:
	float x, y,
		hx, hy,
		dx, dy;

};
#endif