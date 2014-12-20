
#include <iostream>
#include <math.h>

using namespace std;

// (x1, y1)���� (y1, y2)�� �ִ�ӷ� speed��
// ���� �ӵ� (v1, v2)�� ����ϴ� �Լ�.
void ComputeVelocity (
	float x1, float y1,
	float x2, float y2,
	float speed,
	float& v1, float& v2
	)
{
	float dx = x2 - x1,
		dy = y2 - y1;
	// ���� ����ϰ�.
	float angle = atan2f(dy, dx);

	// �Ÿ��� ����ؼ�
	float distance = sqrtf(dx * dx + dy * dy);

	// �Ÿ����� �ӷ��� ũ�� �ӷ��� ���Դϴ�.
	if(distance < speed)
		speed = distance;

	printf("�� ���� ���� %.2f�� �Դϴ�.\n", angle * 180 / 3.141592f);

	// �ﰢ�Լ��� ���� �ӵ��� ����մϴ�.
	v1 = speed * cos(angle);
	v2 = speed * sin(angle);
}



int main()
{
	float x1 = 100, y1 = 100,
		x2 = 150, y2 = -175,
		speed = 35,
		v1 = 0, v2 = 0;

	ComputeVelocity(x1, y1, x2, y2, speed, v1, v2);

	printf("(%.2f, %.2f)���� (%.2f, %.2f)�� %.2fm/s�� �� ���� "
		"�ӵ��� (%.2f, %.2f)m/s�Դϴ�. \n", x1, y1, x2, y2, speed, v1, v2);

	return 0;
}