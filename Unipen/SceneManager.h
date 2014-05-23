#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

namespace unipen
{
	class Scene ;

	//!SceneManager객체를 얻어오는 매크로
#define SceneMgr (SceneManager::GetInstance())

	/**
	 *@briefScene을 하나 정하여 관리해준다.
	 *메시지루프를 돌리는 주체로서 FPS를 관리한다.
	 */
	class SceneManager
	{
	private:
		Scene* m_NowScene ;
		Scene* m_NewScene ;
		int m_FPS ;
	private:
		SceneManager() ;
		~SceneManager() ;
	public:
		SceneManager& GetInstance() ;

	public:
		//!메시지 루프를 돈다.
		void Run() ;
		
		/**
		 *@brief 현재 씬을 얻어온다.
		 *@return 현재 씬
		 */
		Scene* GetNowScene() ;

		/**
		 *@brief 씬을 바꾼다.
		 *@param _iNewScene 새로운 씬
		 */
		void ChangeScene(Scene* _iNewScene) ;
		/**
		 *@brief 현재 FPS를 얻어온다.
		 *@return 현재 FPS값
		 */
		int GetFPS() ;

		/**
		 *@brief FPS값을 설정한다.
		 *@param _iNewFPS 새로운 FPS값
		 */
		void SetFPS(int _iNewFPS) ;
	};
}
#endif