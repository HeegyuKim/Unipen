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
		if(GetOwnerLayer() != nullptr)
		{
			int Color ;
			int WorldColor = 0 ;
			for(int i = 0; i < 4; i++)
			{
				Color = ((GetColor() >> (i*8))%256) + ((GetOwnerLayer()->GetWorldColor() >> (i*8))%256)  ;
				if(Color >= 256)
					Color = 255 ;
				WorldColor += Color << (i*8) ;
			}

			return GetOwnerLayer()->GetWorldColor() + GetColor() ;
		}
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

	void SceneEntity::SetX(int _iX)
	{
		m_X = _iX ;
	}
	int SceneEntity::GetX()
	{
		return m_X ;
	}
	int SceneEntity::GetWorldX()
	{
		if(GetOwnerLayer() != nullptr)
			return GetX() + GetOwnerLayer()->GetX() ;
		return GetX() ;
	}

	void SceneEntity::SetY(int _iY)
	{
		m_Y = _iY ;
	}
	int SceneEntity::GetY()
	{
		return m_Y ;
	}
	int SceneEntity::GetWorldY()
	{
		if(GetOwnerLayer() != nullptr)
			return GetY() + GetOwnerLayer()->GetY() ;
		return GetY() ;
	}

	void SceneEntity::SetXY(int _iX, int _iY)
	{
		SetX(_iX) ;
		SetY(_iY) ;
	}
}