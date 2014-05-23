#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "Entity.h"
#include <memory.h>
#include <malloc.h>

namespace unipen
{
	//! ũ�Ⱑ �������� �迭 �����̳�
	template <typename T>
	class ArrayList
	{
	private:
		T* m_List ;
		int m_ElementCount ;
		int m_Size ;

	public:
		ArrayList()
		{
			m_List = nullptr ;
			m_ElementCount = 0 ;
			m_Size = 0 ;
		}
		~ArrayList()
		{
			if(m_List != nullptr)
				free(m_List) ;
		}

		/**
		*@brief ���ο� ���Ҹ� �ִ´�.
		*@param _iNew ���ο� ����
		*@param _iIndex ������ ��ġ�� �ε���
		*return ���� ���� ����
		*/
		bool AddAt(T _iNew, int _iIndex = 0)
		{
			if(_iIndex < 0 || _iIndex > m_ElementCount)
				return false ;

			if(m_ElementCount + 1 > m_Size)
			{
				m_Size += 3 ;
				if(m_List == nullptr)
				{
					m_List = (T*)malloc(sizeof(T)*m_Size) ;
				}
				else
					m_List = (T*)realloc(m_List, sizeof(T)*m_Size) ;
			}

			memcpy(m_List + _iIndex + 1, m_List + _iIndex, sizeof(T) * (m_ElementCount - _iIndex)) ;
			m_List[_iIndex] = _iNew ;
			m_ElementCount++ ;
			return true ;
		}
		
		/**
		*@brief ���ο� ���Ҹ� �ִ´�.
		*@param _iNew ���ο� ����
		*@param _iIndex ������ ��ġ�� �ε���
		*return ���� ���� ����
		*/
		void Add(T _iNew)
		{
			AddAt(_iNew, GetElementCount()) ;
		}

		/**
		*@brief ���ڷ� ���� �ε����� �ִ� ���Ҹ� �����Ѵ�.
		*@param _iIndex ������ ������ �ε���
		*@return ������ ������ ��
		*/
		T RemoveAt(int _iIndex)
		{
			if(_iIndex < m_ElementCount)
			{
				T RemoveVal =  m_List[_iIndex] ;
				memcpy(m_List + _iIndex, m_List + _iIndex + 1, sizeof(T) * (m_ElementCount - _iIndex - 1)) ;
				m_ElementCount-- ;
				if(m_Size - m_ElementCount > 3)
				{
					m_Size -= 3 ;
					if(m_Size == 0)
					{
						free(m_List) ;
						m_List = nullptr ;
					}
					else
						m_List = (T*)realloc(m_List, sizeof(T)*m_Size) ;
				}
				return RemoveVal ;
			}
			return T(0) ;
		}

		/**
		*@brief ���ڷ� ���� �ε����� �ִ� ���Ҹ� ��ȯ�Ѵ�.
		*@param _iIndex ��ȯ���� ������ �ε���
		*/
		T GetAt(int _iIndex)
		{
			if(_iIndex < m_ElementCount)
			{
				return m_List[_iIndex] ;
			}
			return T(0) ;
		}

		/**
		*@brief �迭�� ũ�⸦ ��ȯ�Ѵ�.
		*@return �迭�� ũ��
		*/
		int GetSize()
		{
			return m_Size ;
		}

		/**
		*@brief ���� ������ ��ȯ�Ѵ�.
		*@return ������ ����
		*/
		int GetElementCount()
		{
			return m_ElementCount ;
		}
	} ;
}



#endif