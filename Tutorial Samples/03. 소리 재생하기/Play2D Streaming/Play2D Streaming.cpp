
// irrKlang을 사용하기 위해서 irrKlang.h을 포함합니다.
#include <irrKlang.h>
#include <iostream>

using namespace std;


int main()
{
	// 사운드 엔진을 생성합니다.
	irrklang::ISoundEngine *engine = 
		irrklang::createIrrKlangDevice();
	
	cout << "Play from stream. " << endl;

	// play2D 메서드로 ogg 파일을 재생합니다.
	// 두번째 인자가 true면 재생이 끝나도 계속해서 반복 재생하게 됩니다.ㄴ
	engine->play2D("../media/classroom_bgm.ogg", true);
	system("pause");

	// 사운드 엔진 제거
	engine->drop();

	return 0;
}
