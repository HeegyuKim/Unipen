
#include <iostream>
#include <math.h>

using namespace std;


// 2���� ���͸� ��Ÿ���� ���� Vector2D ����ü
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