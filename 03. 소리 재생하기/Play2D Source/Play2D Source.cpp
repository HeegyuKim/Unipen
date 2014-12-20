
#include <irrKlang.h>
#include <iostream>

using namespace std;


int main()
{
	// ���� ������ �����մϴ�.
	irrklang::ISoundEngine *engine = 
		irrklang::createIrrKlangDevice();

	cout << "Play from source. " << endl;

	irrklang::ISoundSource *source = 
		engine->addSoundSourceFromFile("../media/classroom_bgm.ogg");
	
	engine->addSoundSourceAlias(source, "ClassRoom");
	
	// �Ʒ� 3���� ��� �Ȱ��� �����մϴ�.
	//engine->play2D(source, true);
	//engine->play2D("../media/classroom_bgm.ogg");
	//engine->play2D("ClassRoom");

	int abc;
	cout << "�ƹ� Ű�� ������ ����!" << endl;
	cin >> abc;


	// ���� ������ ���ְ� �ʹٸ�?
	engine->removeSoundSource("ClassRoom");
	engine->removeSoundSource("../media/classroom_bgm.ogg");
	engine->removeSoundSource(source);

	// ������ ���� ��������!
	engine->removeAllSoundSources();

	// ���� ���� ����
	engine->drop();

	return 0;
}
