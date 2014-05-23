#include "SceneManager.h"
#include <windows.h>

namespace unipen
{
	
		SceneManager::SceneManager()
		{
			m_NowScene = nullptr ;
			m_NewScene = nullptr ;
			m_FPS = 60 ;
		}
		SceneManager::~SceneManager()
		{
		}
		SceneManager& SceneManager::GetInstance()
		{
			static SceneManager Instance ;
			return Instance ;
		}

		void SceneManager::Run()
		{
			int OldTime = timeGetTime() ;
			MSG msg ;
			ZeroMemory(&msg, sizeof(msg)) ;
			while( msg.message != WM_QUIT )
			{
				if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg) ;
					DispatchMessage(&msg) ;
				}
				else
				{
					while(timeGetTime() - OldTime > 1000 / GetFPS())
					{
						m_NowScene->Update(1000/GetFPS()) ;
						OldTime += 1000 / GetFPS() ;
					}
					m_NowScene->Render() ;
				}
			}
		}
		
		Scene* SceneManager::GetNowScene()
		{
			return m_NowScene ;
		}

		void SceneManager::ChangeScene(Scene* _iNewScene)
		{
			m_NewScene = _iNewScene ;
		}

		int SceneManager::GetFPS()
		{
			return m_FPS ;
		}
		
		void SceneManager::SetFPS(int _iNewFPS)
		{
			m_FPS = _iNewFPS ;
		}