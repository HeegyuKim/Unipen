
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

//
// �̻��� ������ ��� Ŭ����
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

	// X, Y��ǥ�� �ӷ¸�ŭ �̵��ϴ� �Լ�
	void Move()
	{
		x += dx;
		y += dy;
	}

public:
	// x, y �� �̻����� X, Y��ǥ�� �ǹ��ϸ�
	// dx, dy�� �̻����� X��, Y�� �ӷ��� �ǹ��մϴ�.
	float x, y, dx, dy;

};

// �̻��� ��ü���� ��� ����Ʈ�� Ÿ��
typedef std::vector<Missile> MissileList;

// �̻����� ������ �Ѿ������ Ȯ���ϴ� �Լ��Դϴ�.
// �Ѿ�� true, �Ѿ�� �ʾ����� false�Դϴ�.
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
// minValue�� maxValue������ float Ÿ�� ������ �����մϴ�.
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
		// ���ο� �̻����� �����ؼ�
		Missile missile(Random(25, 75),
						Random(25, 75),
						Random(-10, 10),
						Random(-10, 10));
		// �߰��մϴ�.
		missiles.push_back(missile);

		//
		// �׸��� ��� �̻����� ��ȸ!
		MissileList::iterator it = missiles.begin();
		
		printf("\n\n%d. =========================\n", i);

		while(it != missiles.end())
		{
			bool removed = false;

			// �̻����� �����ڸ� ���´�.
			Missile& m = *it;

			// �̻����� ������ �Ѿ�� ��쿡�� �����ؾ� �ϰ�
			// ����: (-100, -100) ���� (100, 100)����
			if(OutOfBound(m, -100, -100, 100, 100))
				removed = true;

			// �׷��� ���� ��� �̵� ó���մϴ�.
			else
				m.Move();

			// ���� ���
			printf("(%.2f, %.2f) �̻��� %s.\n", 
				m.x, m.y, (removed)? "���ŵ�":"�̵���");


			// �����ؾ� �ϸ�, �����ϰ� ���ο� �ݺ��ڸ� �޾ƿ���
			if(removed)
				it = missiles.erase(it);
			// �׷��� �ʴٸ� ���� �̻��Ϸ� �Ѿ�ϴ�.
			else
				it ++;
		}

		// 1�ʰ� ����
		Sleep(1000);
	}

	return 0;
}