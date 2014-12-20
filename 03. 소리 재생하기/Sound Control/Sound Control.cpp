
#include <iostream>
#include <irrklang.h>
#include <string>
#include <math.h>
using namespace std;


int main()
{
	// 사운드 엔진을 생성합니다.
	irrklang::ISoundEngine *engine = 
		irrklang::createIrrKlangDevice();

	// 사운드를 재생하고 관리하기 위한 포인터를 받습니다.
	irrklang::ISound* sound = engine->play2D("../media/classroom_bgm.ogg", false, false, true);
	
	
	char command[80] = {0};

	while(true)
	{
		// 명령어를 입력받습니다.
		cout << "명령어를 입력해 주세요. list 명령을 통해 명령어 목록을 볼 수 있습니다." << endl;
		cin >> command;

		// "list"일 경우 명령어 목록을 출력합니다.
		if(0 == strcmp(command, "list"))
		{
			cout << "pause: 정지, stop: 중단, loop: 반복, notloop: 반복해제." << endl
				<< "play: 재생, quit: 끝내기, loudly/silently: 소리 키우기/줄이기, fastly/slowly: 속도를 빠르게/느리게. " << endl;
		}

		// "pause" 일 경우 setIsPause(true)를 통해 일시정지합니다.
		else if(0 == strcmp(command, "pause"))
		{
			sound->setIsPaused(true);
			cout << "재생이 중지되었습니다. " << endl;
		}

		// "stop"일 경우 재생을 완전히 중단합니다.
		// 
		else if(0 == strcmp(command, "stop"))
		{
			if(sound != NULL)
			{
				sound->stop();
				// drop() 메서드로 메모리에서 제거합니다.
				sound->drop();	
				sound = NULL;
			}

			cout << "재생이 중단되었습니다. " << endl;
		}

		// "loop" 일 경우 반복 재생을 활성화합니다.
		else if(0 == strcmp(command, "loop"))
		{
			sound->setIsLooped(true);
			cout << "반복재생됩니다." << endl;
		}
		
		// "notloop" 일 경우 반복 재생을 비활성화합니다.
		else if(0 == strcmp(command, "notloop"))
		{
			sound->setIsLooped(false);
			cout << "반복재생되지 않습니다." << endl;
		}

		// "play" 일 경우 사운드를 다시 재생합니다.
		else if(0 == strcmp(command, "play"))
		{
			// 일시정지된 상태일 경우엔 일시정지를 해재하고
			if(sound != NULL && sound->getIsPaused())
			{
				sound->setIsPaused(false);
			}
			// 그렇지 않다면 사운드를 다시 재생합니다.
			else
			{
				if(sound != NULL)
				{
					sound->stop();
					sound->drop();
				}
				sound = engine->play2D("../media/classroom_bgm.ogg", false, false, true);
			}
			cout << "재생을 시작합니다. " << endl;
		}

		// "quit" 일 경우 사운드 객체를 파괴하고 반복문을 빠져나옵니다.
		else if(0 == strcmp(command, "quit"))
		{
			if(sound != NULL)
			{
				sound->drop();
				sound = NULL;
			}
			break;
		}
		
		// 소리 키우기
		else if(0 == strcmp(command, "loudly"))
		{
			if(sound != NULL)
			{
				// volume + 0.1 이 1를 넘지 않게
				float volume = min<float>(sound->getVolume() + 0.1f, 1);
				sound->setVolume(volume);
				cout << "소리 크기: " << volume << endl;
			}
		}

		// 소리 줄이기
		else if(0 == strcmp(command, "silently"))
		{
			if(sound != NULL)
			{
				// volume - 0.1 이 0보다 낮지 않게
				float volume = max<float>(sound->getVolume() - 0.1f, 0);
				sound->setVolume(volume);
				cout << "소리 크기: " << volume << endl;
			}
		}

		// 재생 속도를 빠르게
		else if(0 == strcmp(command, "fastly"))
		{
			if(sound != NULL)
			{
				float speed = sound->getPlaybackSpeed() + 0.1f;
				sound->setPlaybackSpeed(speed);
				cout << "재생 속도: " << speed << endl;
			}
		}

		// 재생 속도를 느리게
		else if(0 == strcmp(command, "slowly"))
		{
			if(sound != NULL)
			{
				float speed = sound->getPlaybackSpeed() - 0.1f;
				sound->setPlaybackSpeed(speed);
				cout << "재생 속도: " << speed << endl;
			}
		}
		// 알 수 없는 명령어 처리
		else
			cout << "알 수 없는 명령입니다. " << endl;
	}

	engine->drop();

	return 0;
}