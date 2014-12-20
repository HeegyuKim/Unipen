
#ifndef _DodgeGame_h_
#define _DogdeGame_h_


#include "d2dutils.h"
#include "Enemy.h"
#include "Player.h"

#include <string>
#include <atlbase.h>
#include <vector>
#include <irrklang.h>

class DodgeGame
{
public:
	enum Stage 
	{
		MAIN_STAGE,
		GAME_STAGE,
		TYPE_COUNT,
	};

	// 비트맵 목록
	typedef std::vector<CComPtr<ID2D1Bitmap>> BitmapList;


	DodgeGame(HWND hwnd);


	~DodgeGame();

	void Update(float delta);

	void Draw();

private:

	// paths 배열의 경로들로부터 이미지를 읽어서
	// bitmaps에 추가하는 메서드
	void LoadImages(
		const std::wstring paths[],
		UINT len,
		BitmapList &bitmaps
		);

private:
	/*
		Start*** 메서드는 해당 스테이지가 시작했을 때 초기화 작업을 진행합니다.
		Update*** 메서드는 갱신을, Draw*** 메서드는 그리기 작업을 수행합니다.
	*/

	// 시작화면 초기화/갱신/그리기
	void StartMainStage();
	void UpdateOnMain(float delta);
	void DrawOnMain();

	// 게임중일 때 화면 초기화/갱신/그리기
	void StartGameStage();
	void UpdateOnGame(float delta);
	void DrawOnGame();

private:
	// 리소스들...

	HWND mWindow;
	Stage mStage;
	D2D1_RECT_F mWindowSize;

	CComPtr<ID2D1Factory>			mFac2d;	// Direct2D 팩토리
	CComPtr<IDWriteFactory>			mFacDw;	// DirectWrite 팩토리
	CComPtr<IWICImagingFactory>		mFacImg;// WIC 팩토리
	
	
	CComPtr<ID2D1HwndRenderTarget>	mRt;	// 윈도우 렌더타겟
	CComPtr<IDWriteTextFormat>		mFont, mFontLarge; // 글꼴
	CComPtr<ID2D1SolidColorBrush>	mSolidBrush;


	BitmapList	mEnemyBitmaps,		// 적 캐릭터 비트맵들
				mBackgroundBitmaps,	// 배경이미지 비트맵들
				mResultBitmaps;		// 결과 비트맵들

	CComPtr<ID2D1Bitmap> mPlayerBitmap;	// 플레이어 비트맵

private:
	// 메인 스테이지에서 쓰이는 변수들
	float mNotifyDelta;

private:
	// 게임 스테이지에서 쓰이는 변수들
	typedef std::vector<Enemy> EnemyList;

	bool mPaused, mEnded;
	float mPausingDelta,	// 마지막으로 일시정지하고 지난 시간
			mElapsedTime,	// 게임 진행 시간
			mEndedDelta;	// 플레이어가 죽은 뒤 지난 시간

	float mEnemyGenDelta,	// 마지막으로 적을 생성하고 지난 시간
			mEnemyGenCycle;	// 적을 생성하는 시간의 주기
	EnemyList mEnemyList;
	Player mPlayer;

	irrklang::ISoundEngine *engine;
	irrklang::ISound *mBgm;
};

#endif