#pragma once
#include "Entity.h"

namespace unipen
{
	class Layer ;

	//! ȭ���� �����ϴ� �⺻ ��ü
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
		 *@brief �ڽ��� ���¸� �����Ѵ�.
		 *@param eTime ������ Update�κ��� ������ Update���� �ɸ� �ð�
		 */
		virtual void Update(float eTime) ;
		//! ������ ó���� �Ѵ�.
		virtual void Render() ;

	public:
		/**
		 *@brief ������ �����Ѵ�.
		 *@param _iRot ���ο� ����
		 */
		void SetRot(int _iRot) ;
		//! ������ �������� ���´�.
		int GetRot() ;
		/**
		 *@brief �ڽ��� ������ �θ��̾��� �������� �ڽ��� �������� ����
		 �������� �������� ���´�.
		 */
		int GetWorldRot() ;
		
		/**
		 *@brief ������ �����Ѵ�.
		 *@param _iColor ���ο� ����
		 */
		void SetColor(int _iColor) ;
		//! brief ������ ������ ���´�.
		int GetColor() ;
		/**
		 *@brief �ڽ��� ������ �θ��̾��� ���󰪰� �ڽ��� ������ ����
		 �������� ������ ���´�.
		 */
		int GetWorldColor() ;
		
		/**
		 *@brief Ȯ�� ��ġ�� �����Ѵ�.
		 *@param _iColor ���ο� Ȯ�� ��ġ
		 */
		void SetScale(float _iScale) ;
		//! ������ Ȯ�� ��ġ�� ���´�.
		float GetScale() ;
		/**
		 *@brief �ڽ��� ������ �θ��̾��� Ȯ�� ��ġ�� �ڽ��� Ȯ���ġ�� ����
		 �������� Ȯ�� ��ġ�� ���´�.
		 */
		float GetWorldScale() ;
		
		/**
		 *@brief X��ǥ�� �����Ѵ�.
		 *@param _iX ���ο� X��ǥ
		 */
		void SetX(int _iX) ;
		//! ������ X��ǥ�� ���´�.
		int GetX() ;
		//! �ڽ��� ������ �θ��̾��� X��ǥ�� �ڽ��� X��ǥ�� ���� �������� X��ǥ�� ���´�.
		int GetWorldX() ;
		
		/**
		 *@brief Y��ǥ�� �����Ѵ�.
		 *@param _iY ���ο� Y��ǥ
		 */
		void SetY(int _iY) ;
		//! ������ Y��ǥ�� ���´�.
		int GetY() ;
		//! �ڽ��� ������ �θ��̾��� Y��ǥ�� �ڽ��� Y��ǥ�� ���� �������� Y��ǥ�� ���´�.
		int GetWorldY() ;

		//! X��ǥ�� Y��ǥ�� �����Ѵ�.
		void SetXY(int _iX, int _iY) ;

		//! �ڽ��� ������ Layer�� ����Ѵ�.
		void SetOwnerLayer(Layer* _iOwnerLayer) ;
		//! �ڽ��� ������ Layer�� ���´�.
		Layer* GetOwnerLayer() ;
	};
}