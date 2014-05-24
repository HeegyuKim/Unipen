#ifndef LAYER_H
#define LAYER_H

#include "SceneEntity.h"
#include <list>
#include <map>

namespace unipen
{
	/**
	 *@brief SceneEntity들을 관리하는 클래스
	 *렌더링 순서나 회전, 이동등을 일괄적으로 적용한다.
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
		 *@brief 갖고잇는 모든 Entity들의 Update함수를 호출해준다.
		 *@param eTime 이전의 Update로부터 현재의 Update까지 걸린 시간
		 */
		virtual void Update(float eTime) ;
		
		//!brief 갖고있는 모든 Entity들의 Render함수를 호출해준다.
		virtual void Render() ;

	public:
		/**
		 *@brief Entity를 추가한다.
		 *@param _iNewEntity 새로운 Entity
		 *@param _iEntityName 새로운 Entity의 이름, 이는 찾거나 삭제할 때 쓰인다.
		 */
		void AddEntity(SceneEntity* _iNewEntity, std::string _iEntityName) ;
		/**
		 *@brief Entity 이름으로 레이어를 얻어온다.
		 *@param _iEntityName 얻어올 레이어의 이름
		 *@return 이름에 해당하는 Entity, 이름에 해당하는 Entity가 없다면 nullptr 리턴
		 */
		SceneEntity* GetEntity(std::string _iEntityName) ;
		/**
		 *@brief Entity 이름으로 Entity를 빼낸다.
		 *@param _iEntityName 빼낼 레이어의 이름
		 *@return 빼낸 Entity, 이름에 해당하는 Entity가 없다면 nullptr 리턴
		 */
		SceneEntity* PopEntity(std::string _iEntityName) ;

	private:
		/**
		 *@brief Update도중 Entity가 빠지면 순회도중 오류가 날 가능성이 있기 때문에
		 순회를 모두 마친 후 한번에 몰아서 빼준다.
		 */
		void ProcessPopEntity() ;
	} ;
}
#endif