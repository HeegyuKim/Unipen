
#include "DodgeGame.h"
#include <sstream>
#include "utils.h"

using namespace d2d;
using namespace std;


// ����� hr�� ���и�(FAILED�� �˻�)
// message�� ���� ���� ��ü�� �����ϴ�.
void ThrowIfFailed(HRESULT hr, const char* message)
{
	if(FAILED(hr))
		throw exception(message);
}


DodgeGame::DodgeGame(HWND hwnd)
	: mWindow(hwnd), mStage(Stage::MAIN_STAGE),
	mPaused(false),
	mNotifyDelta(0)
{
	HRESULT hr = S_OK;
	
	// COM �ʱ�ȭ
	CoInitialize(nullptr);

	// Direct2D ��ü�� ����
	hr = Initialize(hwnd, &mFac2d.p, &mRt.p);
	ThrowIfFailed(hr, "Direct2D �ʱ�ȭ�� �����߽��ϴ�.");

	// DirectWrite ���丮 ����
	hr = DWriteCreateFactory (
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&mFacDw.p);
	ThrowIfFailed(hr, "DirectWrite ���丮�� ������ �� �����ϴ�.");

	// WIC���丮 ����
	hr = CoCreateInstance (
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&mFacImg.p));
	ThrowIfFailed(hr, "WIC �̹������丮�� ������ �� �����ϴ�.");

	// �귯�� ����
	mRt->CreateSolidColorBrush (
		D2D1::ColorF(D2D1::ColorF::Black),
		&mSolidBrush.p );

	// ��Ʈ �ε�
	mFacDw->CreateTextFormat (
			L"���� ���",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			16.0f,
			L"ko-kr",
			&mFont.p );

	mFacDw->CreateTextFormat (
			L"���� ���",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			48.0f,
			L"ko-kr",
			&mFontLarge.p );

	wstring enemyPaths[] = {
		L"images/alien.png",
		L"images/devil.png",
		L"images/dragon.png",
		L"images/envoy.png",
		L"images/ghost.png",
		L"images/pirate.png",
	};
	LoadImages(enemyPaths, Enemy::TYPE_COUNT, mEnemyBitmaps);

	wstring bgiPaths[] = {
		L"images/main_stage.jpg",
		L"images/game_stage.jpg",
	};
	LoadImages(bgiPaths, Stage::TYPE_COUNT, mBackgroundBitmaps);
	
	wstring resultPaths[] = {
		L"images/good.png",
		L"images/general.png",
		L"images/worse.png",
	};
	LoadImages(resultPaths, 3, mResultBitmaps);

	hr = LoadBitmap(L"images/airship.png", mFacImg, mRt, &mPlayerBitmap.p);
	ThrowIfFailed(hr, "images/airship.png ������ ���� �� �����ϴ�.");


	//
	// ���� ���� ���ҽ� �ε�

	engine = irrklang::createIrrKlangDevice();
	if(engine == nullptr)
		throw exception("Sound ������ ������ �� �����ϴ�.");
	
	// ȿ���� 3���� �̸� �ε�!
	engine->addSoundSourceFromFile("sounds/devil.wav");
	engine->addSoundSourceFromFile("sounds/envoy.wav");
	engine->addSoundSourceFromFile("sounds/pirate.wav");
}


void DodgeGame::LoadImages(
	const wstring paths[],
	UINT len,
	BitmapList &bitmaps
	)
{
	HRESULT hr = S_OK;

	for(int i = 0; i < len; ++i)
	{
		CComPtr<ID2D1Bitmap> bitmap;
		
		hr = LoadBitmap(
			paths[i].c_str(),
			mFacImg,
			mRt,
			&bitmap.p );

		if(FAILED(hr))
		{
			wstringstream ss;
			ss << paths[i].c_str() << L"�κ��� �̹����� ���� �� �����ϴ�. ";

			MessageBox(mWindow, ss.str().c_str(), L"�̹��� �ε� ����", MB_ICONERROR);

			throw exception("�̹����� ���� �� �����ϴ�.");
		}
		else
			bitmaps.push_back(bitmap);
	}
}

DodgeGame::~DodgeGame() 
{
	if(engine)
		engine->drop();
}


void DodgeGame::Update(float delta)
{
	RECT size;
	GetClientRect(mWindow, &size);
	
	mWindowSize.left = mWindowSize.top = 0.0f;
	mWindowSize.right = size.right - size.left;
	mWindowSize.bottom = size.bottom - size.top;

	switch(mStage)
	{
	case MAIN_STAGE:
		UpdateOnMain(delta);
		break;
	case GAME_STAGE:
		UpdateOnGame(delta);
		break;
	};
}


void DodgeGame::Draw()
{
	mRt->BeginDraw();
	mRt->Clear(D2D1::ColorF(D2D1::ColorF::White));
	
	switch(mStage)
	{
	case MAIN_STAGE:
		DrawOnMain();
		break;
	case GAME_STAGE:
		DrawOnGame();
		break;
	};

	mRt->EndDraw();
}


// ����ȭ�� ����/�׸���
void DodgeGame::StartMainStage()
{
	mNotifyDelta = 0.0f;
	mStage = Stage::MAIN_STAGE;

	// ���� BGM�� ��� ���̸� ����
	if(mBgm)
	{
		mBgm->stop();
		mBgm = nullptr;
	}
}
void DodgeGame::UpdateOnMain(float delta)
{
	// mNotifyDelta ���� �帥 �ð�(delta)��ŭ ����ؼ� �����ְ�
	// 2�� �Ѿ�� 0���� �ʱ�ȭ
	mNotifyDelta += delta;
	if(mNotifyDelta >= 2.0f)
		mNotifyDelta = 0.0f;

	// �����̽� �ٸ� ������
	// ���� ����������!
	if(IsKeyDown(VK_SPACE))
		StartGameStage();
}

void DodgeGame::DrawOnMain()
{
	mRt->DrawBitmap(mBackgroundBitmaps[Stage::MAIN_STAGE]);

	if(mNotifyDelta <= 1.0f)
	{
		D2D1_RECT_F dst = D2D1::RectF(300, 450, 800, 600);
		wstring text = L"�����̽� �ٸ� ������ �����մϴ�...";

		mRt->DrawTextW (
			text.c_str(),
			text.length(),
			mFont,
			dst,
			mSolidBrush
			);
	}
}


// �������� �� ȭ�� ����/�׸���
void DodgeGame::StartGameStage()
{
	mStage = Stage::GAME_STAGE;
	mEnemyGenDelta = 0.0f;
	mEnemyGenCycle = 1.0f;
	mPausingDelta = 0.0f;
	mElapsedTime = 0.0f;
	mEnded = false;
	mPaused = false;
	mEnemyList.clear();
	mEndedDelta = 0.0f;

	mPlayer.Set(400, 300, 50, 50, 400, 400);

	// bgm ���
	mBgm = engine->play2D("sounds/bgm.wav", true, false, true);
}

void DodgeGame::UpdateOnGame(float delta)
{
	if(mEnded)
	{
		mEndedDelta += delta;

		if(IsKeyDown(VK_RETURN) && mEndedDelta > 1) 
			StartMainStage();
		return;
	}
	


	mPausingDelta += delta;

	// ESC�� ������ �Ͻ����� ���¸� �ڹٲ�(1�ʸ���).
	if(IsKeyDown(VK_ESCAPE)
		&& mPausingDelta >= 1.0f)
	{
		mPausingDelta = 0.0f;
		mPaused = !mPaused;
	}
	
	// �Ͻ����� �����̸� �� �̻��� ó���� ����!
	if(mPaused)
		return;
	
	mElapsedTime += delta;
	mEnemyGenDelta += delta;

	// ���� ���� ���鸸ŭ �ð��� ��������
	// ���ο� ���� �����.
	if(mEnemyGenDelta >= mEnemyGenCycle)
	{
		mEnemyGenDelta = 0.0f;

		// ���� �ֱ⸦ ���̵�, �ּ� 0.15�ʷ� ����
		if(mEnemyGenCycle >= 0.15f)
			mEnemyGenCycle -= 0.01f;
		
		float wx = mWindowSize.right,
			wy = mWindowSize.bottom;
		float maxSpeed = 350.0f,
			minSpeed = 100.0f;

		// ������ Ÿ���� �� ����
		Enemy e((Enemy::Type)RandomInt(0, Enemy::Type::TYPE_COUNT));
		
		e.SetSize(50, 50);
		
		int pattern = rand() % 4;

		// ���Ϻ� ������ ��ġ/�ӵ� ����
		switch(pattern) 
		{
		case 0:	// ���ʿ��� ��Ÿ��
			e.SetPos(0.0f, RandomFloat() * wy);
			e.SetVel(RandomFloat(minSpeed, maxSpeed), 0);
			break;
		case 1: // �����ʿ��� ��Ÿ��
			e.SetPos(wx, RandomFloat() * wy);
			e.SetVel(RandomFloat(-maxSpeed, -minSpeed), 0);
			break;
		case 2: // ������ ��Ÿ��
			e.SetPos(RandomFloat() * wx, 0);
			e.SetVel(0, RandomFloat(minSpeed, maxSpeed));
			break;
		case 3: // �Ʒ����� ��Ÿ��
			e.SetPos(RandomFloat() * wx, wy);
			e.SetVel(0, RandomFloat(-maxSpeed, -minSpeed));
			break;
		};
		
		mEnemyList.push_back(e);

		// Ÿ�Կ� ���� ȿ���� ���		
		switch(e.GetType())
		{
		case Enemy::DEVIL:
			engine->play2D("sounds/devil.wav");
			break;
		case Enemy::ENVOY:
			engine->play2D("sounds/envoy.wav");
			break;
		case Enemy::PIRATE:
			engine->play2D("sounds/pirate.wav");
			break;
		}

	}

	// �÷��̾��� �Է��� ó���Ѵ�.
	if(IsKeyDown(VK_LEFT))
		mPlayer.x -= mPlayer.dx * delta;
	if(IsKeyDown(VK_RIGHT))
		mPlayer.x += mPlayer.dx * delta;
	if(IsKeyDown(VK_UP))
		mPlayer.y -= mPlayer.dy * delta;
	if(IsKeyDown(VK_DOWN))
		mPlayer.y += mPlayer.dy * delta;
	
	// ������ �Ѿ�� �ʰ� ó��
	// Clamp(v, min, max) �� v �� min ������ ��� min��, max �̻��� ��� max�� ��ȯ�մϴ�.
	// �� v�� min ~ max ������ ���� ������ �մϴ�.
	mPlayer.x = Clamp(mPlayer.x, mWindowSize.left, mWindowSize.right);
	mPlayer.y = Clamp(mPlayer.y, mWindowSize.top, mWindowSize.bottom);
	
	
	// ������ �����ϰ�
	// ������ ������� Ȯ���� ����.
	EnemyList::iterator it = mEnemyList.begin();
	bool removed = false;

	D2D1_RECT_F pRect = mPlayer.GetCollisionRect();

	while(it != mEnemyList.end())
	{
		Enemy& enemy = *it;
		
		// �� ����
		enemy.Update(delta);

		// ���� ������
		D2D1_RECT_F eRect = enemy.GetRect();

		// ȭ��� �������� ������(ȭ���� �����) ����
		removed = !IsIntersect(eRect, mWindowSize);
		
		// �÷��̾�� �������� ���� ����~
		if(IsIntersect(eRect, pRect))
		{
			mEnded = true;

			engine->play2D("sounds/gameover.wav");
		}

		if(removed)
		{
			it = mEnemyList.erase(it);
			removed = false;
		}
		else
			++it;
	}
}

void DodgeGame::DrawOnGame()
{
	mRt->DrawBitmap(mBackgroundBitmaps[Stage::GAME_STAGE]);

	EnemyList::iterator it = mEnemyList.begin();

	while(it != mEnemyList.end())
	{
		const Enemy& e = *it;
		D2D1_RECT_F eRect = e.GetRect();
		Enemy::Type type = e.GetType();
		ID2D1Bitmap* bitmap = mEnemyBitmaps[type];

		mRt->DrawBitmap(bitmap, eRect);

		++it;
	}
	
	// ����� ĳ���� �׸���
	D2D1_RECT_F pRect = mPlayer.GetRect();
	mRt->DrawBitmap(mPlayerBitmap, pRect);

	// �Ͻ����� ���¸� �������ϰ� �׸���
	// 
	if(mPaused)
	{
		D2D1_COLOR_F prevColor = mSolidBrush->GetColor();

		mSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, 0.5f));

		mRt->FillRectangle (
			mWindowSize,
			mSolidBrush
			);

		mSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
		
		wstring text = L"ESCŰ�� ������ ��ӵ˴ϴ�.";
		mRt->DrawTextW (
			text.c_str(),
			text.length(),
			mFontLarge,
			D2D1::RectF (
				150, 250,
				650, 600
			),
			mSolidBrush);

		mSolidBrush->SetColor(prevColor);
	}
	// ������ ���� �����̸�
	else if(mEnded)
	{
		D2D1_COLOR_F prevColor = mSolidBrush->GetColor();

		mSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, 0.5f));

		mRt->FillRectangle (
			mWindowSize,
			mSolidBrush
			);

		mSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
		
		wstring text = L"��! ENTERŰ�� ������ �������� �̵��մϴ�.";
		mRt->DrawTextW (
			text.c_str(),
			text.length(),
			mFontLarge,
			D2D1::RectF (
				150, 450,
				650, 600
			),
			mSolidBrush);

		mSolidBrush->SetColor(prevColor);

		ID2D1Bitmap *bitmap = nullptr;

		if(mElapsedTime < 30)
			bitmap = mResultBitmaps[2];
		else if(mElapsedTime < 60)
			bitmap = mResultBitmaps[1];
		else
			bitmap = mResultBitmaps[0];

		mRt->DrawBitmap ( bitmap,
			D2D1::RectF (
				150, 50,
				650, 450
			));
	}
	// ���� ����� �ð� �׸���
	D2D1_COLOR_F prevColor = mSolidBrush->GetColor();
	
	mSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	
	wstringstream elapsedTimeStream;
	elapsedTimeStream << (int)mElapsedTime << L"��";
	wstring elapsedTimeText = elapsedTimeStream.str();

	mRt->DrawTextW (
		elapsedTimeText.c_str(),
		elapsedTimeText.length(),
		mFontLarge,
		D2D1::RectF (
			0, 550,
			400, 600),
		mSolidBrush );

	// ������ ���۵� �� 5�ʰ� ���� �ʾ�����
	if(mElapsedTime < 5)
	{
		wstring howtoText = L"����Ű�� �������� ������ ���ϼ���!";

		mRt->DrawTextW (
			howtoText.c_str(),
			howtoText.length(),
			mFontLarge,
			mWindowSize,
			mSolidBrush );
	}

	mSolidBrush->SetColor(prevColor);

}

