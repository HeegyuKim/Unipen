#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "Entity.h"
#include <memory.h>
#include <malloc.h>

namespace unipen
{
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
		*@param _iIndex 삽입할 위치의 인덱스
		*return 삽입 성공 여부
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
		*@brief 새로운 원소를 넣는다.
		*@param _iNew 새로운 원소
		*@param _iIndex 삽입할 위치의 인덱스
		*return 삽입 성공 여부
		*/
		void Add(T _iNew)
		{
			AddAt(_iNew, GetElementCount()) ;
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
}



#endif