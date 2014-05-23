#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

namespace unipen
{
	class Scene ;

	//!SceneManager��ü�� ������ ��ũ��
#define SceneMgr (SceneManager::GetInstance())

	/**
	 *@briefScene�� �ϳ� ���Ͽ� �������ش�.
	 *�޽��������� ������ ��ü�μ� FPS�� �����Ѵ�.
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
		//!�޽��� ������ ����.
		void Run() ;
		
		/**
		 *@brief ���� ���� ���´�.
		 *@return ���� ��
		 */
		Scene* GetNowScene() ;

		/**
		 *@brief ���� �ٲ۴�.
		 *@param _iNewScene ���ο� ��
		 */
		void ChangeScene(Scene* _iNewScene) ;
		/**
		 *@brief ���� FPS�� ���´�.
		 *@return ���� FPS��
		 */
		int GetFPS() ;

		/**
		 *@brief FPS���� �����Ѵ�.
		 *@param _iNewFPS ���ο� FPS��
		 */
		void SetFPS(int _iNewFPS) ;
	};
}
#endif