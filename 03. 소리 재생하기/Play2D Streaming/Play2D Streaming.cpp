
// irrKlang�� ����ϱ� ���ؼ� irrKlang.h�� �����մϴ�.
#include <irrKlang.h>
#include <iostream>

using namespace std;


int main()
{
	// ���� ������ �����մϴ�.
	irrklang::ISoundEngine *engine = 
		irrklang::createIrrKlangDevice();
	
	cout << "Play from stream. " << endl;

	// play2D �޼���� ogg ������ ����մϴ�.
	// �ι�° ���ڰ� true�� ����� ������ ����ؼ� �ݺ� ����ϰ� �˴ϴ�.��
	engine->play2D("../media/classroom_bgm.ogg", true);
	system("pause");

	// ���� ���� ����
	engine->drop();

	return 0;
}
