
#include "DodgeGame.h"
#include <sstream>
#include "utils.h"

using namespace d2d;
using namespace std;


// 결과값 hr이 실패면(FAILED로 검사)
// message를 담은 예외 객체를 던집니다.
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
	
	// COM 초기화
	CoInitialize(nullptr);

	// Direct2D 객체들 생성
	hr = Initialize(hwnd, &mFac2d.p, &mRt.p);
	ThrowIfFailed(hr, "Direct2D 초기화에 실패했습니다.");

	// DirectWrite 팩토리 생성
	hr = DWriteCreateFactory (
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&mFacDw.p);
	ThrowIfFailed(hr, "DirectWrite 팩토리를 생성할 수 없습니다.");

	// WIC팩토리 생성
	hr = CoCreateInstance (
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&mFacImg.p));
	ThrowIfFailed(hr, "WIC 이미지팩토리를 생성할 수 없습니다.");

	// 브러시 생성
	mRt->CreateSolidColorBrush (
		D2D1::ColorF(D2D1::ColorF::Black),
		&mSolidBrush.p );

	// 폰트 로딩
	mFacDw->CreateTextFormat (
			L"맑은 고딕",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			16.0f,
			L"ko-kr",
			&mFont.p );

	mFacDw->CreateTextFormat (
			L"맑은 고딕",
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
	ThrowIfFailed(hr, "images/airship.png 파일을 읽을 수 없습니다.");


	//
	// 사운드 관련 리소스 로딩

	engine = irrklang::createIrrKlangDevice();
	if(engine == nullptr)
		throw exception("Sound 엔진을 생성할 수 없습니다.");
	
	// 효과음 3개는 미리 로딩!
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
			ss << paths[i].c_str() << L"로부터 이미지를 읽을 수 없습니다. ";

			MessageBox(mWindow, ss.str().c_str(), L"이미지 로딩 실패", MB_ICONERROR);

			throw exception("이미지를 읽을 수 없습니다.");
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


// 시작화면 갱신/그리기
void DodgeGame::StartMainStage()
{
	mNotifyDelta = 0.0f;
	mStage = Stage::MAIN_STAGE;

	// 만약 BGM이 재생 중이면 종료
	if(mBgm)
	{
		mBgm->stop();
		mBgm = nullptr;
	}
}
void DodgeGame::UpdateOnMain(float delta)
{
	// mNotifyDelta 값을 흐른 시간(delta)만큼 계속해서 더해주고
	// 2를 넘어가면 0으로 초기화
	mNotifyDelta += delta;
	if(mNotifyDelta >= 2.0f)
		mNotifyDelta = 0.0f;

	// 스페이스 바를 누르면
	// 게임 스테이지로!
	if(IsKeyDown(VK_SPACE))
		StartGameStage();
}

void DodgeGame::DrawOnMain()
{
	mRt->DrawBitmap(mBackgroundBitmaps[Stage::MAIN_STAGE]);

	if(mNotifyDelta <= 1.0f)
	{
		D2D1_RECT_F dst = D2D1::RectF(300, 450, 800, 600);
		wstring text = L"스페이스 바를 누르면 시작합니다...";

		mRt->DrawTextW (
			text.c_str(),
			text.length(),
			mFont,
			dst,
			mSolidBrush
			);
	}
}


// 게임중일 때 화면 갱신/그리기
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

	// bgm 재생
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

	// ESC가 눌리면 일시정지 상태를 뒤바꿈(1초마다).
	if(IsKeyDown(VK_ESCAPE)
		&& mPausingDelta >= 1.0f)
	{
		mPausingDelta = 0.0f;
		mPaused = !mPaused;
	}
	
	// 일시정지 상태이면 더 이상의 처리는 없음!
	if(mPaused)
		return;
	
	mElapsedTime += delta;
	mEnemyGenDelta += delta;

	// 적을 새로 만들만큼 시간이 지났으면
	// 새로운 적을 만든다.
	if(mEnemyGenDelta >= mEnemyGenCycle)
	{
		mEnemyGenDelta = 0.0f;

		// 생성 주기를 줄이되, 최소 0.15초로 조절
		if(mEnemyGenCycle >= 0.15f)
			mEnemyGenCycle -= 0.01f;
		
		float wx = mWindowSize.right,
			wy = mWindowSize.bottom;
		float maxSpeed = 350.0f,
			minSpeed = 100.0f;

		// 무작위 타입의 적 생성
		Enemy e((Enemy::Type)RandomInt(0, Enemy::Type::TYPE_COUNT));
		
		e.SetSize(50, 50);
		
		int pattern = rand() % 4;

		// 패턴별 무작위 위치/속도 지정
		switch(pattern) 
		{
		case 0:	// 왼쪽에서 나타남
			e.SetPos(0.0f, RandomFloat() * wy);
			e.SetVel(RandomFloat(minSpeed, maxSpeed), 0);
			break;
		case 1: // 오른쪽에서 나타남
			e.SetPos(wx, RandomFloat() * wy);
			e.SetVel(RandomFloat(-maxSpeed, -minSpeed), 0);
			break;
		case 2: // 위에서 나타남
			e.SetPos(RandomFloat() * wx, 0);
			e.SetVel(0, RandomFloat(minSpeed, maxSpeed));
			break;
		case 3: // 아래에서 나타남
			e.SetPos(RandomFloat() * wx, wy);
			e.SetVel(0, RandomFloat(-maxSpeed, -minSpeed));
			break;
		};
		
		mEnemyList.push_back(e);

		// 타입에 따른 효과음 재생		
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

	// 플레이어의 입력을 처리한다.
	if(IsKeyDown(VK_LEFT))
		mPlayer.x -= mPlayer.dx * delta;
	if(IsKeyDown(VK_RIGHT))
		mPlayer.x += mPlayer.dx * delta;
	if(IsKeyDown(VK_UP))
		mPlayer.y -= mPlayer.dy * delta;
	if(IsKeyDown(VK_DOWN))
		mPlayer.y += mPlayer.dy * delta;
	
	// 범위를 넘어가지 않게 처리
	// Clamp(v, min, max) 는 v 가 min 이하일 경우 min을, max 이상일 경우 max를 반환합니다.
	// 즉 v가 min ~ max 사이의 값을 갖도록 합니다.
	mPlayer.x = Clamp(mPlayer.x, mWindowSize.left, mWindowSize.right);
	mPlayer.y = Clamp(mPlayer.y, mWindowSize.top, mWindowSize.bottom);
	
	
	// 적들을 갱신하고
	// 범위를 벗어갔는지 확인해 본다.
	EnemyList::iterator it = mEnemyList.begin();
	bool removed = false;

	D2D1_RECT_F pRect = mPlayer.GetCollisionRect();

	while(it != mEnemyList.end())
	{
		Enemy& enemy = *it;
		
		// 적 갱신
		enemy.Update(delta);

		// 범위 얻어오기
		D2D1_RECT_F eRect = enemy.GetRect();

		// 화면과 교차되지 않으면(화면을 벗어나면) 제거
		removed = !IsIntersect(eRect, mWindowSize);
		
		// 플레이어랑 겹쳤으면 게임 종료~
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
	
	// 사용자 캐릭터 그리기
	D2D1_RECT_F pRect = mPlayer.GetRect();
	mRt->DrawBitmap(mPlayerBitmap, pRect);

	// 일시정지 상태면 검투명하게 그리고
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
		
		wstring text = L"ESC키를 누르면 계속됩니다.";
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
	// 게임이 끝난 상태이면
	else if(mEnded)
	{
		D2D1_COLOR_F prevColor = mSolidBrush->GetColor();

		mSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black, 0.5f));

		mRt->FillRectangle (
			mWindowSize,
			mSolidBrush
			);

		mSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
		
		wstring text = L"꽥! ENTER키를 누르면 메인으로 이동합니다.";
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
	// 게임 진행된 시간 그리기
	D2D1_COLOR_F prevColor = mSolidBrush->GetColor();
	
	mSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	
	wstringstream elapsedTimeStream;
	elapsedTimeStream << (int)mElapsedTime << L"초";
	wstring elapsedTimeText = elapsedTimeStream.str();

	mRt->DrawTextW (
		elapsedTimeText.c_str(),
		elapsedTimeText.length(),
		mFontLarge,
		D2D1::RectF (
			0, 550,
			400, 600),
		mSolidBrush );

	// 게임이 시작된 지 5초가 되지 않았으면
	if(mElapsedTime < 5)
	{
		wstring howtoText = L"방향키로 움직여서 적들을 피하세요!";

		mRt->DrawTextW (
			howtoText.c_str(),
			howtoText.length(),
			mFontLarge,
			mWindowSize,
			mSolidBrush );
	}

	mSolidBrush->SetColor(prevColor);

}

