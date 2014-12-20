
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

	// ��Ʈ�� ���
	typedef std::vector<CComPtr<ID2D1Bitmap>> BitmapList;


	DodgeGame(HWND hwnd);


	~DodgeGame();

	void Update(float delta);

	void Draw();

private:

	// paths �迭�� ��ε�κ��� �̹����� �о
	// bitmaps�� �߰��ϴ� �޼���
	void LoadImages(
		const std::wstring paths[],
		UINT len,
		BitmapList &bitmaps
		);

private:
	/*
		Start*** �޼���� �ش� ���������� �������� �� �ʱ�ȭ �۾��� �����մϴ�.
		Update*** �޼���� ������, Draw*** �޼���� �׸��� �۾��� �����մϴ�.
	*/

	// ����ȭ�� �ʱ�ȭ/����/�׸���
	void StartMainStage();
	void UpdateOnMain(float delta);
	void DrawOnMain();

	// �������� �� ȭ�� �ʱ�ȭ/����/�׸���
	void StartGameStage();
	void UpdateOnGame(float delta);
	void DrawOnGame();

private:
	// ���ҽ���...

	HWND mWindow;
	Stage mStage;
	D2D1_RECT_F mWindowSize;

	CComPtr<ID2D1Factory>			mFac2d;	// Direct2D ���丮
	CComPtr<IDWriteFactory>			mFacDw;	// DirectWrite ���丮
	CComPtr<IWICImagingFactory>		mFacImg;// WIC ���丮
	
	
	CComPtr<ID2D1HwndRenderTarget>	mRt;	// ������ ����Ÿ��
	CComPtr<IDWriteTextFormat>		mFont, mFontLarge; // �۲�
	CComPtr<ID2D1SolidColorBrush>	mSolidBrush;


	BitmapList	mEnemyBitmaps,		// �� ĳ���� ��Ʈ�ʵ�
				mBackgroundBitmaps,	// ����̹��� ��Ʈ�ʵ�
				mResultBitmaps;		// ��� ��Ʈ�ʵ�

	CComPtr<ID2D1Bitmap> mPlayerBitmap;	// �÷��̾� ��Ʈ��

private:
	// ���� ������������ ���̴� ������
	float mNotifyDelta;

private:
	// ���� ������������ ���̴� ������
	typedef std::vector<Enemy> EnemyList;

	bool mPaused, mEnded;
	float mPausingDelta,	// ���������� �Ͻ������ϰ� ���� �ð�
			mElapsedTime,	// ���� ���� �ð�
			mEndedDelta;	// �÷��̾ ���� �� ���� �ð�

	float mEnemyGenDelta,	// ���������� ���� �����ϰ� ���� �ð�
			mEnemyGenCycle;	// ���� �����ϴ� �ð��� �ֱ�
	EnemyList mEnemyList;
	Player mPlayer;

	irrklang::ISoundEngine *engine;
	irrklang::ISound *mBgm;
};

#endif