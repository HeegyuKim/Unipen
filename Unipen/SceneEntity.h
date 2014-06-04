#pragma once
#include "Entity.h"

namespace unipen
{
	class Layer ;

	//! 화면을 구성하는 기본 객체
	class SceneEntity : public Entity
	{
	private:
		float m_Rot ;
		int m_Color ;
		float m_Scale ;
		int m_X ;
		int m_Y ;

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
		//! 렌더링 처리를 한다.
		virtual void Render() ;

	public:
		/**
		 *@brief 각도를 설정한다.
		 *@param _iRot 새로운 각도
		 */
		void SetRot(int _iRot) ;
		//! 현재의 각도값을 얻어온다.
		int GetRot() ;
		/**
		 *@brief 자신을 소유한 부모레이어의 각도값과 자신의 각도값을 합쳐
		 실질적인 각도값을 얻어온다.
		 */
		int GetWorldRot() ;
		
		/**
		 *@brief 색상을 설정한다.
		 *@param _iColor 새로운 색상
		 */
		void SetColor(int _iColor) ;
		//! brief 현재의 색상값을 얻어온다.
		int GetColor() ;
		/**
		 *@brief 자신을 소유한 부모레이어의 색상값과 자신의 색상값을 합쳐
		 실질적인 색상값을 얻어온다.
		 */
		int GetWorldColor() ;
		
		/**
		 *@brief 확대 수치를 설정한다.
		 *@param _iColor 새로운 확대 수치
		 */
		void SetScale(float _iScale) ;
		//! 현재의 확대 수치를 얻어온다.
		float GetScale() ;
		/**
		 *@brief 자신을 소유한 부모레이어의 확대 수치와 자신의 확대수치를 합쳐
		 실질적인 확대 수치를 얻어온다.
		 */
		float GetWorldScale() ;
		
		/**
		 *@brief X좌표를 설정한다.
		 *@param _iX 새로운 X좌표
		 */
		void SetX(int _iX) ;
		//! 현재의 X좌표를 얻어온다.
		int GetX() ;
		//! 자신을 소유한 부모레이어의 X좌표와 자신의 X좌표를 합쳐 실질적인 X좌표를 얻어온다.
		int GetWorldX() ;
		
		/**
		 *@brief Y좌표를 설정한다.
		 *@param _iY 새로운 Y좌표
		 */
		void SetY(int _iY) ;
		//! 현재의 Y좌표를 얻어온다.
		int GetY() ;
		//! 자신을 소유한 부모레이어의 Y좌표와 자신의 Y좌표를 합쳐 실질적인 Y좌표를 얻어온다.
		int GetWorldY() ;

		//! X좌표와 Y좌표를 설정한다.
		void SetXY(int _iX, int _iY) ;

		//! 자신을 소유한 Layer를 등록한다.
		void SetOwnerLayer(Layer* _iOwnerLayer) ;
		//! 자신을 소유한 Layer를 얻어온다.
		Layer* GetOwnerLayer() ;
	};
}