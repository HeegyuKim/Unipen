#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Entity.h"
#include <memory.h>
#include <malloc.h>

namespace unipen
{
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
		int m_Size ;
	public:
		LinkedList()
		{
			m_Header = nullptr ;
			m_Size = 0 ;
		}
		~LinkedList()
		{
			if(m_Header != nullptr)
			{
				Node* RemoveNode = m_Header ;
				Node* NextNode = RemoveNode->Next ;

				while(RemoveNode != nullptr)
				{
					NextNode = RemoveNode->Next ;
					delete RemoveNode ;
					RemoveNode = NextNode ;
				}
			}
		}

		/**
		*@brief ���ο� ���Ҹ� Ư�� ��ġ�� �ִ´�.
		*@param _iNew ���ο� ����
		*@param _iIndex ������ ��ġ�� �ε���
		*/
		void AddAt(T _iNew, int _iIndex = 0)
		{
			Node * NewNode = (Node*)malloc(sizeof(Node)) ;
			NewNode->Data = _iNew ;
			

			if(_iIndex <= 0)
			{
				NewNode->Next = m_Header ;
				m_Header = NewNode ;
			}
			else
			{
				Node * NewNodesPrevNode = m_Header ;
				while(_iIndex > 1)
				{
					NewNodesPrevNode = NewNodesPrevNode->Next ;
					_iIndex-- ;
				}

				NewNode->Next = NewNodesPrevNode->Next ;
				NewNodesPrevNode->Next = NewNode ;
			}
			++m_Size ;
		}

		/**
		 *@brief ���ο� ���Ҹ� �ִ´�.
		 *@param _iNew ���ο� ����
		 */
		void Add(T _iNew)
		{
			AddAt(_iNew, GetSize()) ;
		}

		/**
		*@brief ���ڷ� ���� �ε����� �ִ� ���Ҹ� �����Ѵ�.
		*@param _iIndex ������ ������ �ε���
		*@return ������ ������ ��
		*/
		T RemoveAt(int _iIndex)
		{
			if(m_Header == nullptr || _iIndex < 0 || _iIndex >= GetSize())
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
			--m_Size ;

			return RemoveVal ;
		}

		/**
		*@brief ���ڷ� ���� �ε����� �ִ� ���Ҹ� ��ȯ�Ѵ�.
		*@param _iIndex ��ȯ���� ������ �ε���
		*/
		T GetAt(int _iIndex)
		{
			if(_iIndex < 0 || _iIndex >= GetSize())
				return T(0);
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
			return m_Size ;
		}
	} ;
}






#endif