#pragma once
#include "Entity.h"

namespace unipen
{
	class Layer ;

	class SceneEntity : public Entity
	{
	private:
		float m_Rot ;
		int m_Color ;
		float m_Scale ;

		Layer* m_OwnerLayer ;
	public:
		SceneEntity(void);
		~SceneEntity(void);
		
	public:
		/**
		 *@brief 자신의 상태를 갱신한다.
		 *@param eTime 이전의 Update로부터 현재의 Update까지 걸린 시간
		 */
		virtual void Update(float eTime) ;
		/**
		 *@brief 렌더링 처리를 한다.
		 */
		virtual void Render() ;

	public:
		/**
		 *@brief 새로운 각도를 설정한다.
		 *@param _iRot 새로운 각도
		 */
		void SetRot(int _iRot) ;
		/**
		 *@brief 현재의 각도값을 얻어온다.
		 */
		int GetRot() ;
		/**
		 *@brief 자신을 소유한 부모레이어의 각도값과 자신의 각도값을 합쳐
		 실질적인 각도값을 얻어온다.
		 */
		int GetWorldRot() ;
		
		/**
		 *@brief 새로운 색상을 설정한다.
		 *@param _iColor 새로운 색상
		 */
		void SetColor(int _iColor) ;
		/**
		 *@brief 현재의 색상값을 얻어온다.
		 */
		int GetColor() ;
		/**
		 *@brief 자신을 소유한 부모레이어의 색상값과 자신의 색상값을 합쳐
		 실질적인 색상값을 얻어온다.
		 */
		int GetWorldColor() ;
		
		/**
		 *@brief 새로운 확대 수치를 설정한다.
		 *@param _iColor 새로운 확대 수치
		 */
		void SetScale(float _iScale) ;
		/**
		 *@brief 현재의 확대 수치를 얻어온다.
		 */
		float GetScale() ;
		/**
		 *@brief 자신을 소유한 부모레이어의 확대 수치와 자신의 확대수치를 합쳐
		 실질적인 확대 수치를 얻어온다.
		 */
		float GetWorldScale() ;

		//! 자신을 소유한 Layer를 등록한다.
		void SetOwnerLayer(Layer* _iOwnerLayer) ;
		//! 자신을 소유한 Layer를 얻어온다.
		Layer* GetOwnerLayer() ;
	};
}