#ifndef LAYER_H
#define LAYER_H

#include "SceneEntity.h"
#include <list>
#include <map>

namespace unipen
{
	/**
	 *@brief SceneEntity���� �����ϴ� Ŭ����
	 *������ ������ ȸ��, �̵����� �ϰ������� �����Ѵ�.
	 */
	class Layer : public SceneEntity
	{
	private:
		typedef std::map<std::string, SceneEntity*> ENTITYLIST ;
		typedef std::list<ENTITYLIST::iterator> POPENTITYLIST ;
		ENTITYLIST m_EntityList ;
		POPENTITYLIST m_PopEntityList ;
	public:
		Layer(void);
		virtual ~Layer(void);

	public:
		/**
		 *@brief �����մ� ��� Entity���� Update�Լ��� ȣ�����ش�.
		 *@param eTime ������ Update�κ��� ������ Update���� �ɸ� �ð�
		 */
		virtual void Update(float eTime) ;
		
		//!brief �����ִ� ��� Entity���� Render�Լ��� ȣ�����ش�.
		virtual void Render() ;

	public:
		/**
		 *@brief Entity�� �߰��Ѵ�.
		 *@param _iNewEntity ���ο� Entity
		 *@param _iEntityName ���ο� Entity�� �̸�, �̴� ã�ų� ������ �� ���δ�.
		 */
		void AddEntity(SceneEntity* _iNewEntity, std::string _iEntityName) ;
		/**
		 *@brief Entity �̸����� ���̾ ���´�.
		 *@param _iEntityName ���� ���̾��� �̸�
		 *@return �̸��� �ش��ϴ� Entity, �̸��� �ش��ϴ� Entity�� ���ٸ� nullptr ����
		 */
		SceneEntity* GetEntity(std::string _iEntityName) ;
		/**
		 *@brief Entity �̸����� Entity�� ������.
		 *@param _iEntityName ���� ���̾��� �̸�
		 *@return ���� Entity, �̸��� �ش��ϴ� Entity�� ���ٸ� nullptr ����
		 */
		SceneEntity* PopEntity(std::string _iEntityName) ;

	private:
		/**
		 *@brief Update���� Entity�� ������ ��ȸ���� ������ �� ���ɼ��� �ֱ� ������
		 ��ȸ�� ��� ��ģ �� �ѹ��� ���Ƽ� ���ش�.
		 */
		void ProcessPopEntity() ;
	} ;
}
#endif