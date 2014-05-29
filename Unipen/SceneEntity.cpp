#include "SceneEntity.h"
#include "Layer.h"
#include <math.h>

namespace unipen
{
	SceneEntity::SceneEntity(void)
	{
		m_Rot = 0 ;
		m_Color = 0xffffffff ;
		m_Scale = 1.0f ;

		m_OwnerLayer = nullptr ;
	}


	SceneEntity::~SceneEntity(void)
	{
	}
	void SceneEntity::Update(float eTime)
	{
	}
	void SceneEntity::Render()
	{
	}
#define M_PI 3.14159265358979323846
	void SceneEntity::SetRot(int _iRot)
	{
		m_Rot = _iRot/180.0f * M_PI ;
	}
	int SceneEntity::GetRot()
	{
		return m_Rot * 180.0f / M_PI ;
	}
	int SceneEntity::GetWorldRot()
	{
		if(m_OwnerLayer != nullptr)
			return GetOwnerLayer()->GetWorldRot() + GetRot() ;
		return GetRot() ;
	}

	void SceneEntity::SetColor(int _iColor)
	{
		m_Color = _iColor ;
	}
	int SceneEntity::GetColor()
	{
		return m_Color ;
	}
	int SceneEntity::GetWorldColor()
	{
		if(m_OwnerLayer != nullptr)
			return GetOwnerLayer()->GetWorldColor() + GetColor() ;
		return GetColor() ;
	}

	void SceneEntity::SetScale(float _iScale)
	{
		m_Scale = _iScale ;
	}
	float SceneEntity::GetScale()
	{
		return m_Scale ;
	}
	float SceneEntity::GetWorldScale()
	{
		if(m_OwnerLayer != nullptr)
			return GetOwnerLayer()->GetWorldScale() + GetScale() ;
		return GetScale() ;
	}

	void SceneEntity::SetOwnerLayer(Layer* _iOwnerLayer)
	{
		m_OwnerLayer = _iOwnerLayer ;
	}
	Layer* SceneEntity::GetOwnerLayer()
	{
		return m_OwnerLayer; 
	}
}