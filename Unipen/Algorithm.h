#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Entity.h"
#include <memory.h>
#include <malloc.h>

namespace unipen {
	/**
	 *@brief 버블정렬을 해주는 함수
	 *@param _mArray 정렬이 될 배열
	 *@param _iArrayLength 배열의 길이
	 */
	template <typename T>
	void BubbleSort(T* _mArray, int _iArrayLength)
	{
		for(int i = 0; i < _iArrayLength; i++)
		{
			for(int j = _iArrayLength-1; j > i; j--)
			{
				if(_mArray[j] < _mArray[j-1])
				{
					int temp = _mArray[j];
					_mArray[j] = _mArray[j-1];
					_mArray[j-1] = temp;
				}

			}
		}
	}
	/**
	 *@brief 선택정렬을 해주는 함수
	 *@param _mArray 정렬이 될 배열
	 *@param _iArrayLength 배열의 길이
	 */
	template <typename T>
	void SelectionSort(T* _mArray, int _iArrayLength)
	{
		for (int i = 0; i < _iArrayLength - 1; i++)
		{
			int index = i;
			for (int j = i + 1; j < _iArrayLength; j++)
			{
				if (_mArray[index] > _mArray[j])
				{
					index = j;
				}
			}
			int temp = _mArray[index];
			_mArray[index] = _mArray[i];
			_mArray[i] = temp;
		}
	}
	/**
	 *@brief 퀵정렬을 해주는 함수
	 *@param _mArray 정렬이 될 배열
	 *@param _iArrayLength 배열의 길이
	 */
	template <typename T>
	void QuickSort(T* _mArray, int _iArrayLength)
	{
		QuickSortProcessor(_mArray, 0, _iArrayLength -1);
	}
	
	/**
	 *@brief 실질적으로 퀵정렬을 해주는 함수
	 *@param _mArray 정렬이 될 배열
	 *@param _iArrayLength 배열의 길이
	 */
	template <typename T>
	static void QuickSortProcessor(T* _mArray, int left, int right)
	{
		int pivot, l_hold, r_hold;
		l_hold = left;
		r_hold = right;
		pivot = _mArray[left]; // 0번째 원소를 피봇으로 선택
		while (left < right)
		{
			// 값이 선택한 피봇과 같거나 크다면, 이동할 필요가 없다
			while ((_mArray[right] >= pivot) && (left < right))
				right --;

			// 그렇지 않고 값이 피봇보다 작다면,
			// 피봇의 위치에 현재 값을 넣는다.
			if (left != right)
			{
				_mArray[left] = _mArray[right];
			}
			// 왼쪽부터 현재 위치까지 값을 읽어들이면서
			// 피봇보다 큰 값이 있다면, 값을 이동한다.
			while ((_mArray[left] <= pivot) && (left < right))
				left ++;
			if (left != right)
			{
				_mArray[right] = _mArray[left];
				right --;
			}
		}
		// 모든 스캔이 끝났다면, 피봇값을 현재 위치에 입력한다.
		// 이제 피봇을 기준으로 왼쪽에는 피봇보다 작거나 같은 값만 남았다.
		_mArray[left] = pivot;
		pivot = left;
		left = l_hold;
		right = r_hold;

		// 재귀호출을 수행한다.
		if (left < pivot)
			QuickSortProcessor(_mArray, left, pivot - 1);
		if (right > pivot)
			QuickSortProcessor(_mArray, pivot+1, right);
	}

	/**
	*@brief 배열에서 해당 값의 인덱스를 순차검색을 통하여 찾는다.
	*@return 해당 값의 인덱스값
	*/
	template <typename T>
	int SequentialSearch(T _iFindingValue, T* _mArray, int _iArrayLength)
	{
		for(int i = 0; i < _iArrayLength; i++)
			if(_mArray[i] == _iFindingValue)
				return i ;

		return -1 ;
	}
	/**
	 *@brief 배열에서 해당 값의 인덱스를 이진검색을 통하여 찾는다.
	 *@return 해당 값의 인덱스값
	 */
	template <typename T>
	int BinarySearch(T _iFindingValue, T* _mArray, int _iArrayLength)
	{
		int left = 0, right = _iArrayLength-1 ;
		int mid = right / 2 ;

		while(left <= right)
		{
			mid = (left+right)/2 ;
			if(_iFindingValue > _mArray[mid])
			{
				left = mid + 1 ;
			}
			else if(_iFindingValue < _mArray[mid])
			{
				right = mid - 1 ;
			}
			else
				return mid ;
		}

		return -1 ;
	}
}
#endif