#pragma once
#include "Entity.h"

namespace unipen
{
	class SceneEntity : public Entity
	{
	public:
		SceneEntity(void);
		~SceneEntity(void);
		
	public:
		virtual void Update(float eTime) ;
		virtual void Render() ;

	public:

	};

}