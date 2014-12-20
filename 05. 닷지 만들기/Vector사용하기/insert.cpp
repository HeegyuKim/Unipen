
#include <iostream>
#include <vector>

using namespace std;



int main()
{
typedef vector<int>::iterator Iterator;
	
vector<int> v;
int values[] = {
	1, 2, 3, 4, 5,
	6, 7, 8, 9, 10,
};
	
// ������ ó���� �迭�� ��� ���� �߰��մϴ�.
v.insert(v.begin(), values, values + 10);

// ������ Ư�� ��ġ�� �� �߰�
v.insert(v.begin() + 5, 55);
v.insert(v.end(), 111);
v.insert(v.end(), 11122);

v.pop_back();	// ������ �� �����ϱ�
v.erase(v.begin() + 3); // 4��° �� ����

// Ư�� ������ �� ����(3��° ~ 7��°)
v.erase(v.begin() + 2, v.begin() + 7);

Iterator it = v.begin();
int i = 0;
while(it != v.end())
{
	int a = *it;
	printf("[%d] = %d \n", ++i, a);

	/*
		��ȸ �� ���� ������ ������ ��ȯ�Ǵ� �ݺ��ڸ� ������ �ξ�� �մϴ�.
		�ֳ��ϸ� ���� ������ ��� �� �ݺ��ڴ� �߸��� ���Ҹ� ����Ű�� ������
		������ ���� ���� ���Ҹ� ����Ű�� �ݺ��ڸ� �����ؾ� �մϴ�.
		���� ������ ��쿡�� it++ �� ���� �ʾƾ� �մϴ�.
	*/

	//	Ȧ���̸� �����մϴ�.
	if(a % 2)
		it = v.erase(it);
	else 
		++it;
}

	return 0;
}