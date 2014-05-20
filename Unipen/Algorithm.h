#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Entity.h"
#include <memory.h>
#include <malloc.h>

namespace unipen {

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
		*/
		void Add(T _iNew)
		{
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

			m_List[m_ElementCount] = _iNew ;
			m_ElementCount++ ;
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


	//! ��ũ�� ����Ʈ ����� ����� �����̳�
	template <typename T>
	class LinkedList
	{
	private:
		struct Node
		{
			Node* Next ;
			T Data ;
		} ;

		Node * m_Header ;
	public:
		LinkedList()
		{
			m_Header = nullptr ;
		}
		~LinkedList()
		{
			if(m_Header != nullptr)
			{
			}
		}

		/**
		*@brief ���ο� ���Ҹ� �ִ´�.
		*@param _iNew ���ο� ����
		*/
		void Add(T _iNew)
		{
			Node * NewNode = (Node*)malloc(sizeof(Node)) ;
			NewNode->Data = _iNew ;
			if(m_Header == nullptr)
			{
				m_Header = NewNode ;
				NewNode->Next = nullptr ;
			}
			else
			{
				NewNode->Next = &(*m_Header) ;
				m_Header = NewNode ;
			}
		}

		/**
		*@brief ���ڷ� ���� �ε����� �ִ� ���Ҹ� �����Ѵ�.
		*@param _iIndex ������ ������ �ε���
		*@return ������ ������ ��
		*/
		T RemoveAt(int _iIndex)
		{
			if(m_Header == nullptr || _iIndex < 0)
				return T(0) ;

			Node* RemoveNode = m_Header ;
			if(_iIndex == 0)
			{
				RemoveNode = m_Header ;
				m_Header = RemoveNode->Next ;
			}
			else
			{
				while(_iIndex  > 1 && RemoveNode != nullptr)
				{
					RemoveNode = RemoveNode->Next ;
					_iIndex-- ;
				}

				if(RemoveNode == nullptr)
					return T(0) ;

				Node* BackNode = RemoveNode ;
				RemoveNode = BackNode->Next ;
				BackNode->Next = RemoveNode->Next ;
			}

			T RemoveVal = RemoveNode->Data ;
			free(RemoveNode) ;

			return RemoveVal ;
		}

		/**
		*@brief ���ڷ� ���� �ε����� �ִ� ���Ҹ� ��ȯ�Ѵ�.
		*@param _iIndex ��ȯ���� ������ �ε���
		*/
		T GetAt(int _iIndex)
		{
			Node* ReturnNode = m_Header ;
			while(_iIndex != 0 && ReturnNode != nullptr)
			{
				ReturnNode = ReturnNode->Next ;
				_iIndex-- ;
			}

			if(ReturnNode == nullptr)
				return T(0) ;

			return ReturnNode->Data ;
		}

		/**
		*@brief ����Ʈ�� ũ�⸦ ��ȯ�Ѵ�.
		*@return ����Ʈ�� ũ��
		*/
		int GetSize()
		{
			int Size = 0 ;
			Node* ReturnNode = m_Header ;
			while(ReturnNode != nullptr)
			{
				ReturnNode = ReturnNode->Next ;
				Size++ ;
			}

			return Size ;
		}
	} ;
}
#endif