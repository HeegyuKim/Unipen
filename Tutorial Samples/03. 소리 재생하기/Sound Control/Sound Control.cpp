
#include <iostream>
#include <irrklang.h>
#include <string>
#include <math.h>
using namespace std;


int main()
{
	// ���� ������ �����մϴ�.
	irrklang::ISoundEngine *engine = 
		irrklang::createIrrKlangDevice();

	// ���带 ����ϰ� �����ϱ� ���� �����͸� �޽��ϴ�.
	irrklang::ISound* sound = engine->play2D("../media/classroom_bgm.ogg", false, false, true);
	
	
	char command[80] = {0};

	while(true)
	{
		// ��ɾ �Է¹޽��ϴ�.
		cout << "��ɾ �Է��� �ּ���. list ����� ���� ��ɾ� ����� �� �� �ֽ��ϴ�." << endl;
		cin >> command;

		// "list"�� ��� ��ɾ� ����� ����մϴ�.
		if(0 == strcmp(command, "list"))
		{
			cout << "pause: ����, stop: �ߴ�, loop: �ݺ�, notloop: �ݺ�����." << endl
				<< "play: ���, quit: ������, loudly/silently: �Ҹ� Ű���/���̱�, fastly/slowly: �ӵ��� ������/������. " << endl;
		}

		// "pause" �� ��� setIsPause(true)�� ���� �Ͻ������մϴ�.
		else if(0 == strcmp(command, "pause"))
		{
			sound->setIsPaused(true);
			cout << "����� �����Ǿ����ϴ�. " << endl;
		}

		// "stop"�� ��� ����� ������ �ߴ��մϴ�.
		// 
		else if(0 == strcmp(command, "stop"))
		{
			if(sound != NULL)
			{
				sound->stop();
				// drop() �޼���� �޸𸮿��� �����մϴ�.
				sound->drop();	
				sound = NULL;
			}

			cout << "����� �ߴܵǾ����ϴ�. " << endl;
		}

		// "loop" �� ��� �ݺ� ����� Ȱ��ȭ�մϴ�.
		else if(0 == strcmp(command, "loop"))
		{
			sound->setIsLooped(true);
			cout << "�ݺ�����˴ϴ�." << endl;
		}
		
		// "notloop" �� ��� �ݺ� ����� ��Ȱ��ȭ�մϴ�.
		else if(0 == strcmp(command, "notloop"))
		{
			sound->setIsLooped(false);
			cout << "�ݺ�������� �ʽ��ϴ�." << endl;
		}

		// "play" �� ��� ���带 �ٽ� ����մϴ�.
		else if(0 == strcmp(command, "play"))
		{
			// �Ͻ������� ������ ��쿣 �Ͻ������� �����ϰ�
			if(sound != NULL && sound->getIsPaused())
			{
				sound->setIsPaused(false);
			}
			// �׷��� �ʴٸ� ���带 �ٽ� ����մϴ�.
			else
			{
				if(sound != NULL)
				{
					sound->stop();
					sound->drop();
				}
				sound = engine->play2D("../media/classroom_bgm.ogg", false, false, true);
			}
			cout << "����� �����մϴ�. " << endl;
		}

		// "quit" �� ��� ���� ��ü�� �ı��ϰ� �ݺ����� �������ɴϴ�.
		else if(0 == strcmp(command, "quit"))
		{
			if(sound != NULL)
			{
				sound->drop();
				sound = NULL;
			}
			break;
		}
		
		// �Ҹ� Ű���
		else if(0 == strcmp(command, "loudly"))
		{
			if(sound != NULL)
			{
				// volume + 0.1 �� 1�� ���� �ʰ�
				float volume = min<float>(sound->getVolume() + 0.1f, 1);
				sound->setVolume(volume);
				cout << "�Ҹ� ũ��: " << volume << endl;
			}
		}

		// �Ҹ� ���̱�
		else if(0 == strcmp(command, "silently"))
		{
			if(sound != NULL)
			{
				// volume - 0.1 �� 0���� ���� �ʰ�
				float volume = max<float>(sound->getVolume() - 0.1f, 0);
				sound->setVolume(volume);
				cout << "�Ҹ� ũ��: " << volume << endl;
			}
		}

		// ��� �ӵ��� ������
		else if(0 == strcmp(command, "fastly"))
		{
			if(sound != NULL)
			{
				float speed = sound->getPlaybackSpeed() + 0.1f;
				sound->setPlaybackSpeed(speed);
				cout << "��� �ӵ�: " << speed << endl;
			}
		}

		// ��� �ӵ��� ������
		else if(0 == strcmp(command, "slowly"))
		{
			if(sound != NULL)
			{
				float speed = sound->getPlaybackSpeed() - 0.1f;
				sound->setPlaybackSpeed(speed);
				cout << "��� �ӵ�: " << speed << endl;
			}
		}
		// �� �� ���� ��ɾ� ó��
		else
			cout << "�� �� ���� ����Դϴ�. " << endl;
	}

	engine->drop();

	return 0;
}