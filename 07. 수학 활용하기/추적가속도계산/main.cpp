
#include <iostream>
#include <math.h>

using namespace std;

struct Vector2D {
	float x, y;

	inline Vector2D(float x = 0, float y = 0)
		: x(x), y(y)
	{}

	// ������ ũ�⸦ ���ϴ� �Լ�
	inline float length() const {
		return sqrtf(x * x + y * y);
	}
};

// p1���� p2�� speed�ӷ����� ���� �ӵ� vel�� ����մϴ�.
void ComputeVelocity (
	Vector2D p1,
	Vector2D p2,
	float speed,
	Vector2D& vel
	)
{
	// ����(d) ���
	Vector2D d (
		p2.x - p1.x,
		p2.y - p1.y
		);

	// �Ÿ��� ���(���� ������ ���� = �Ÿ�)
	float distance = d.length();
	
	// �Ÿ��� �ӵ����� ũ�� �ʰ�
	if(distance < speed)
		speed = distance;

	// ����ȭ(���Ҹ� ���̷� ����)�ϰ�
	// �ӵ��� ���ϸ� ��
	vel.x = d.x / distance * speed;
	vel.y = d.y / distance * speed;
}

void ComputeAcceleration (
	Vector2D p1,	// �� ��ġ
	Vector2D p2,	// ��ǥ ��ġ
	float speed,	// �ӵ�
	float maxA,		// �ִ� ���ӷ�
	Vector2D vel,	// ���� �ӵ�
	Vector2D& acc	// ��� ���ӵ�
	)
{
	Vector2D velf;

	// ��ǥ������ �ӵ� ���
	ComputeVelocity(p1, p2, speed, velf);

	// �̻����� ���ӵ� ���
	acc.x = velf.x - vel.x;
	acc.y = velf.y - vel.y;

	// ���̰� ũ�� ���͸� �ڸ��ϴ�.
	float accLen = acc.length();

	if(accLen > maxA)
	{
		acc.x = acc.x / accLen * maxA;
		acc.y = acc.y / accLen * maxA;
	}
}

int main()
{
	Vector2D p1(100, 100), p2(150, -175), vel;
	float speed = 35;

	ComputeVelocity(p1, p2, speed, vel);
	
	printf("(%.2f, %.2f)���� (%.2f, %.2f)�� %.2fm/s�� �� ���� "
		"�ӵ��� (%.2f, %.2f)m/s�Դϴ�. \n", 
		p1.x, p1.y, p2.x, p2.y, speed, vel.x, vel.y);

	return 0;
}