#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Entity.h"
#include <memory.h>
#include <malloc.h>

namespace unipen {

	//! 크기가 가변적인 배열 컨테이너
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
		*@brief 새로운 원소를 넣는다.
		*@param _iNew 새로운 원소
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
		*@brief 인자로 받은 인덱스에 있는 원소를 삭제한다.
		*@param _iIndex 삭제할 원소의 인덱스
		*@return 삭제된 원소의 값
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
		*@brief 인자로 받은 인덱스에 있는 원소를 반환한다.
		*@param _iIndex 반환받을 원소의 인덱스
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
		*@brief 배열의 크기를 반환한다.
		*@return 배열의 크기
		*/
		int GetSize()
		{
			return m_Size ;
		}

		/**
		*@brief 원소 갯수를 반환한다.
		*@return 원소의 갯수
		*/
		int GetElementCount()
		{
			return m_ElementCount ;
		}
	} ;


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
		*@brief 새로운 원소를 넣는다.
		*@param _iNew 새로운 원소
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
		*@brief 인자로 받은 인덱스에 있는 원소를 삭제한다.
		*@param _iIndex 삭제할 원소의 인덱스
		*@return 삭제된 원소의 값
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
		*@brief 인자로 받은 인덱스에 있는 원소를 반환한다.
		*@param _iIndex 반환받을 원소의 인덱스
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
		*@brief 리스트의 크기를 반환한다.
		*@return 리스트의 크기
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