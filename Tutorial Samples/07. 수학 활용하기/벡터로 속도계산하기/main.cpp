
#include <iostream>
#include <math.h>

using namespace std;


// 2차원 벡터를 나타내기 위한 Vector2D 구조체
struct Vector2D {
	float x, y;

	inline Vector2D(float x = 0, float y = 0)
		: x(x), y(y)
	{}

	// 벡터의 크기를 구하는 함수
	inline float length() const {
		return sqrtf(x * x + y * y);
	}
};

// p1에서 p2로 speed속력으로 가는 속도 vel을 계산합니다.
void ComputeVelocity (
	Vector2D p1,
	Vector2D p2,
	float speed,
	Vector2D& vel
	)
{
	// 변위(d) 계산
	Vector2D d (
		p2.x - p1.x,
		p2.y - p1.y
		);

	// 거리를 계산(변위 벡터의 길이 = 거리)
	float distance = d.length();
	
	// 거리가 속도보다 크지 않게
	if(distance < speed)
		speed = distance;

	// 정규화(원소를 길이로 나눔)하고
	// 속도를 곱하면 끝
	vel.x = d.x / distance * speed;
	vel.y = d.y / distance * speed;
}



int main()
{
	Vector2D p1(100, 100), p2(150, -175), vel;
	float speed = 35;

	ComputeVelocity(p1, p2, speed, vel);
	
	printf("(%.2f, %.2f)에서 (%.2f, %.2f)로 %.2fm/s로 갈 때의 "
		"속도는 (%.2f, %.2f)m/s입니다. \n", 
		p1.x, p1.y, p2.x, p2.y, speed, vel.x, vel.y);

	return 0;
}