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
		 *@brief �ڽ��� ���¸� �����Ѵ�.
		 *@param eTime ������ Update�κ��� ������ Update���� �ɸ� �ð�
		 */
		virtual void Update(float eTime) ;
		/**
		 *@brief ������ ó���� �Ѵ�.
		 */
		virtual void Render() ;

	public:
		/**
		 *@brief ���ο� ������ �����Ѵ�.
		 *@param _iRot ���ο� ����
		 */
		void SetRot(int _iRot) ;
		/**
		 *@brief ������ �������� ���´�.
		 */
		int GetRot() ;
		/**
		 *@brief �ڽ��� ������ �θ��̾��� �������� �ڽ��� �������� ����
		 �������� �������� ���´�.
		 */
		int GetWorldRot() ;
		
		/**
		 *@brief ���ο� ������ �����Ѵ�.
		 *@param _iColor ���ο� ����
		 */
		void SetColor(int _iColor) ;
		/**
		 *@brief ������ ������ ���´�.
		 */
		int GetColor() ;
		/**
		 *@brief �ڽ��� ������ �θ��̾��� ���󰪰� �ڽ��� ������ ����
		 �������� ������ ���´�.
		 */
		int GetWorldColor() ;
		
		/**
		 *@brief ���ο� Ȯ�� ��ġ�� �����Ѵ�.
		 *@param _iColor ���ο� Ȯ�� ��ġ
		 */
		void SetScale(float _iScale) ;
		/**
		 *@brief ������ Ȯ�� ��ġ�� ���´�.
		 */
		float GetScale() ;
		/**
		 *@brief �ڽ��� ������ �θ��̾��� Ȯ�� ��ġ�� �ڽ��� Ȯ���ġ�� ����
		 �������� Ȯ�� ��ġ�� ���´�.
		 */
		float GetWorldScale() ;

		//! �ڽ��� ������ Layer�� ����Ѵ�.
		void SetOwnerLayer(Layer* _iOwnerLayer) ;
		//! �ڽ��� ������ Layer�� ���´�.
		Layer* GetOwnerLayer() ;
	};
}