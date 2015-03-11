
#ifndef _Enemy_h_
#define _Enemy_h_

#include "d2dutils.h"

// �� ĳ���͸� ��Ÿ���� Ŭ����
class Enemy
{
public:
	// �� ��ü�� ����
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

	// ��ü�� ��ġ�� �����մϴ�.
	inline void SetPos(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	// ��ü�� �ӵ��� �����մϴ�.
	inline void SetVel(float dx, float dy)
	{
		this->dx = dx;
		this->dy = dy;
	}

	// ��ü�� ũ�⸦ �����մϴ�.
	inline void SetSize(float width, float height)
	{
		this->hx = width / 2.0f;
		this->hy = height / 2.0f;
	}

	// delta�� �ð��� �帥 ��ŭ �̵��մϴ�.
	inline void Update(float delta)
	{
		x += dx * delta;
		y += dy * delta;
	}
	
	// ��ġ ������ ���� Rect���� ��ȯ�մϴ�.
	inline D2D1_RECT_F GetRect() const
	{
		return D2D1::RectF (
			x - hx,
			y - hy,
			x + hx,
			y + hy
			);
	}

	// Ÿ���� ��ȯ�մϴ�.
	inline Type GetType() const
	{
		return type;
	}


private:
	float x, y;		// ��ġ
	float hx, hy;	// ����/���� ũ���� ����
	float dx, dy;	// �̵��ӵ�
	Type type;		// Ÿ��
};

#endif