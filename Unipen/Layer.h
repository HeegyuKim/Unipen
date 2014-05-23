#ifndef LAYER_H
#define LAYER_H

#include "SceneEntity.h"
#include <list>

namespace unipen
{
	class Layer : public SceneEntity
	{
	private:
		typedef std::list<SceneEntity> ENTITYLIST ;
		ENTITYLIST m_EntityList ;
	public:
		Layer(void);
		virtual ~Layer(void);

	public:
		virtual void Update(float eTime) ;
		virtual void Render() ;

	public:
		void AddSceneEntity() ;
		void 
	} ;
}
#endif