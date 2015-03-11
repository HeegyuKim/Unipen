
#include <irrKlang.h>
#include <iostream>

using namespace std;


int main()
{
	// 사운드 엔진을 생성합니다.
	irrklang::ISoundEngine *engine = 
		irrklang::createIrrKlangDevice();

	cout << "Play from source. " << endl;

	irrklang::ISoundSource *source = 
		engine->addSoundSourceFromFile("../media/classroom_bgm.ogg");
	
	engine->addSoundSourceAlias(source, "ClassRoom");
	
	// 아래 3개는 모두 똑같이 동작합니다.
	//engine->play2D(source, true);
	//engine->play2D("../media/classroom_bgm.ogg");
	//engine->play2D("ClassRoom");

	int abc;
	cout << "아무 키나 누르고 엔터!" << endl;
	cin >> abc;


	// 만약 음원을 없애고 싶다면?
	engine->removeSoundSource("ClassRoom");
	engine->removeSoundSource("../media/classroom_bgm.ogg");
	engine->removeSoundSource(source);

	// 음원을 전부 지워버려!
	engine->removeAllSoundSources();

	// 사운드 엔진 제거
	engine->drop();

	return 0;
}
