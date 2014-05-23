#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Entity.h"
#include <memory.h>
#include <malloc.h>

namespace unipen
{
	//! 링크드 리스트 기법을 사용한 컨테이너
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
		*@brief 새로운 원소를 특정 위치에 넣는다.
		*@param _iNew 새로운 원소
		*@param _iIndex 삽입할 위치의 인덱스
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
		 *@brief 새로운 원소를 넣는다.
		 *@param _iNew 새로운 원소
		 */
		void Add(T _iNew)
		{
			AddAt(_iNew, GetSize()) ;
		}

		/**
		*@brief 인자로 받은 인덱스에 있는 원소를 삭제한다.
		*@param _iIndex 삭제할 원소의 인덱스
		*@return 삭제된 원소의 값
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
		*@brief 인자로 받은 인덱스에 있는 원소를 반환한다.
		*@param _iIndex 반환받을 원소의 인덱스
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
		*@brief 리스트의 크기를 반환한다.
		*@return 리스트의 크기
		*/
		int GetSize()
		{
			return m_Size ;
		}
	} ;
}






#endif