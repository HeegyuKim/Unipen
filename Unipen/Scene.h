#ifndef SCENE_H
#define SCENE_H
#include "Entity.h"
#include <map>

namespace unipen
{
	class Layer ;

	/**
	 *@brief ��鰳���� ������ Ŭ����
	 *�������� Layer�� �����Ѵ�.
	*/
	class Scene : public Entity
	{
	private:
		typedef std::map<std::string, Layer*> LAYERLIST ;
		typedef std::list<LAYERLIST::iterator> POPLAYERLIST ;
		LAYERLIST m_LayerList ;
		POPLAYERLIST m_PopLayerList ;
	public:
		Scene(void) ;
		virtual ~Scene(void) ;

	public:
		/**
		 *@brief �����մ� ��� Layer���� Update�Լ��� ȣ�����ش�.
		 *@param eTime ������ Update�κ��� ������ Update���� �ɸ� �ð�
		 */
		virtual void Update(float eTime) ;
		
		//!brief �����ִ� ��� Layer���� Render�Լ��� ȣ�����ش�.
		virtual void Render() ;

	public:
		/**
		 *@brief ���̾ �߰��Ѵ�.
		 *@param _iNewLayer ���ο� ���̾�
		 *@param _iLayerName ���ο� ���̾��� �̸�, �̴� ã�ų� ������ �� ���δ�.
		 */
		void AddLayer(Layer* _iNewLayer, std::string _iLayerName) ;
		/**
		 *@brief ���̾� �̸����� ���̾ ���´�.
		 *@param _iLayerName ���� ���̾��� �̸�
		 *@return �̸��� �ش��ϴ� ���̾�, �̸��� �ش��ϴ� ���̾ ���ٸ� nullptr ����
		 */
		Layer* GetLayer(std::string _iLayerName) ;
		/**
		 *@brief ���̾� �̸����� ���̾ ������.
		 *@param _iLayerName ���� ���̾��� �̸�
		 *@return ���� ���̾�, �̸��� �ش��ϴ� ���̾ ���ٸ� nullptr ����
		 */
		Layer* PopLayer(std::string _iLayerName) ;

	private:
		/**
		 *@brief Update���� Layer�� ������ ��ȸ���� ������ �� ���ɼ��� �ֱ� ������
		 ��ȸ�� ��� ��ģ �� �ѹ��� ���Ƽ� ���ش�.
		 */
		void ProcessPopLayer() ;
	} ;
}

#endif