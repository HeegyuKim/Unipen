
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
	
// 벡터의 처음에 배열의 모든 값을 추가합니다.
v.insert(v.begin(), values, values + 10);

// 벡터의 특정 위치에 값 추가
v.insert(v.begin() + 5, 55);
v.insert(v.end(), 111);
v.insert(v.end(), 11122);

v.pop_back();	// 마지막 값 제거하기
v.erase(v.begin() + 3); // 4번째 값 제거

// 특정 범위의 값 제거(3번째 ~ 7번째)
v.erase(v.begin() + 2, v.begin() + 7);

Iterator it = v.begin();
int i = 0;
while(it != v.end())
{
	int a = *it;
	printf("[%d] = %d \n", ++i, a);

	/*
		순회 중 값을 제거할 때에는 반환되는 반복자를 저장해 두어야 합니다.
		왜냐하면 값을 제거할 경우 그 반복자는 잘못된 원소를 가리키기 때문에
		제거한 값의 다음 원소를 가리키는 반복자를 저장해야 합니다.
		따라서 제거할 경우에는 it++ 도 하지 않아야 합니다.
	*/

	//	홀수이면 제거합니다.
	if(a % 2)
		it = v.erase(it);
	else 
		++it;
}

	return 0;
}