#include "Layer.h"
#include "SceneEntity.h"
#include <string>


namespace unipen
{
	Layer::Layer(void)
		:SceneEntity()
	{
	}


	Layer::~Layer(void)
	{
		m_EntityList.clear() ;
	}

	void Layer::Update(float eTime)
	{
		for(auto iter : m_EntityList)
			iter.second->Update(eTime) ;

		ProcessPopEntity() ;
	}
	void Layer::Render()
	{
		for(auto iter : m_EntityList)
			iter.second->Render() ;
	}

	void Layer::AddEntity(SceneEntity* _iNewEntity, std::string _iEntityName)
	{
		m_EntityList[_iEntityName] = _iNewEntity ;
	}
	SceneEntity* Layer::GetEntity(std::string _iEntityName) ;
	{
			ENTITYLIST::iterator FindingEntity = m_EntityList.find(_iEntityName) ;
			if(FindingEntity == m_EntityList.end())
				return nullptr ;

			return FindingEntity->second ;
	}
	SceneEntity* Layer::PopEntity(std::string _iEntityName)
	{
			ENTITYLIST::iterator PopEntity = m_EntityList.find(_iEntityName) ;
			if(PopEntity == m_EntityList.end())
				return nullptr ;

			m_EntityList.push_back(PopEntity) ;
			return PopEntity->second ;
	}
	void Layer::ProcessPopEntity()
	{
			for(auto iter : m_PopEntityList)
				m_EntityList.erase(iter) ;

			m_PopEntityList.clear() ;
	}
}