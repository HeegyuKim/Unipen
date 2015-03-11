
#include <iostream>
#include <math.h>

using namespace std;

// (x1, y1)에서 (y1, y2)로 최대속력 speed로
// 가는 속도 (v1, v2)를 계산하는 함수.
void ComputeVelocity (
	float x1, float y1,
	float x2, float y2,
	float speed,
	float& v1, float& v2
	)
{
	float dx = x2 - x1,
		dy = y2 - y1;
	// 각을 계산하고.
	float angle = atan2f(dy, dx);

	// 거리를 계산해서
	float distance = sqrtf(dx * dx + dy * dy);

	// 거리보다 속력이 크면 속력을 줄입니다.
	if(distance < speed)
		speed = distance;

	printf("두 점의 각은 %.2f도 입니다.\n", angle * 180 / 3.141592f);

	// 삼각함수를 통해 속도를 계산합니다.
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

	printf("(%.2f, %.2f)에서 (%.2f, %.2f)로 %.2fm/s로 갈 때의 "
		"속도는 (%.2f, %.2f)m/s입니다. \n", x1, y1, x2, y2, speed, v1, v2);

	return 0;
}