
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

//
// 미사일 정보를 담는 클래스
struct Missile
{
public:
	Missile()
		: x(0), y(0), dx(0), dy(0)
	{
	}

	Missile(float x, float y, float dx, float dy)
		: x(x), y(y), dx(dx), dy(dy)
	{
	}

	// X, Y좌표를 속력만큼 이동하는 함수
	void Move()
	{
		x += dx;
		y += dy;
	}

public:
	// x, y 는 미사일의 X, Y좌표를 의미하며
	// dx, dy는 미사일의 X축, Y축 속력을 의미합니다.
	float x, y, dx, dy;

};

// 미사일 객체들을 담는 리스트의 타입
typedef std::vector<Missile> MissileList;

// 미사일이 범위를 넘어갔는지를 확인하는 함수입니다.
// 넘어가면 true, 넘어가지 않았으면 false입니다.
bool OutOfBound(Missile& m, 
				float left, 
				float top, 
				float right, 
				float bottom
				)
{
	return m.x < left || m.x > right
		&& m.y < top || m.y > bottom;
}

//
// minValue와 maxValue사이의 float 타입 난수를 생성합니다.
float Random(float minValue, float maxValue)
{
	return (rand() / (float)RAND_MAX) * (maxValue - minValue) + minValue;
}

int main()
{
	MissileList missiles;

	int i = 0;
	while(i++ <= 50)
	{
		// 새로운 미사일을 생성해서
		Missile missile(Random(25, 75),
						Random(25, 75),
						Random(-10, 10),
						Random(-10, 10));
		// 추가합니다.
		missiles.push_back(missile);

		//
		// 그리고 모든 미사일을 순회!
		MissileList::iterator it = missiles.begin();
		
		printf("\n\n%d. =========================\n", i);

		while(it != missiles.end())
		{
			bool removed = false;

			// 미사일의 참조자를 얻어온다.
			Missile& m = *it;

			// 미사일이 범위를 넘어갔을 경우에는 제거해야 하고
			// 범위: (-100, -100) 부터 (100, 100)까지
			if(OutOfBound(m, -100, -100, 100, 100))
				removed = true;

			// 그렇지 않은 경우 이동 처리합니다.
			else
				m.Move();

			// 정보 출력
			printf("(%.2f, %.2f) 미사일 %s.\n", 
				m.x, m.y, (removed)? "제거됨":"이동함");


			// 제거해야 하면, 제거하고 새로운 반복자를 받아오고
			if(removed)
				it = missiles.erase(it);
			// 그렇지 않다면 다음 미사일로 넘어갑니다.
			else
				it ++;
		}

		// 1초간 정지
		Sleep(1000);
	}

	return 0;
}