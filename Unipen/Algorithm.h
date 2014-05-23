#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Entity.h"
#include <memory.h>
#include <malloc.h>

namespace unipen {
	/**
	 *@brief ���������� ���ִ� �Լ�
	 *@param _mArray ������ �� �迭
	 *@param _iArrayLength �迭�� ����
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
	 *@brief ���������� ���ִ� �Լ�
	 *@param _mArray ������ �� �迭
	 *@param _iArrayLength �迭�� ����
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
	 *@brief �������� ���ִ� �Լ�
	 *@param _mArray ������ �� �迭
	 *@param _iArrayLength �迭�� ����
	 */
	template <typename T>
	void QuickSort(T* _mArray, int _iArrayLength)
	{
		QuickSortProcessor(_mArray, 0, _iArrayLength -1);
	}
	
	/**
	 *@brief ���������� �������� ���ִ� �Լ�
	 *@param _mArray ������ �� �迭
	 *@param _iArrayLength �迭�� ����
	 */
	template <typename T>
	static void QuickSortProcessor(T* _mArray, int left, int right)
	{
		int pivot, l_hold, r_hold;
		l_hold = left;
		r_hold = right;
		pivot = _mArray[left]; // 0��° ���Ҹ� �Ǻ����� ����
		while (left < right)
		{
			// ���� ������ �Ǻ��� ���ų� ũ�ٸ�, �̵��� �ʿ䰡 ����
			while ((_mArray[right] >= pivot) && (left < right))
				right --;

			// �׷��� �ʰ� ���� �Ǻ����� �۴ٸ�,
			// �Ǻ��� ��ġ�� ���� ���� �ִ´�.
			if (left != right)
			{
				_mArray[left] = _mArray[right];
			}
			// ���ʺ��� ���� ��ġ���� ���� �о���̸鼭
			// �Ǻ����� ū ���� �ִٸ�, ���� �̵��Ѵ�.
			while ((_mArray[left] <= pivot) && (left < right))
				left ++;
			if (left != right)
			{
				_mArray[right] = _mArray[left];
				right --;
			}
		}
		// ��� ��ĵ�� �����ٸ�, �Ǻ����� ���� ��ġ�� �Է��Ѵ�.
		// ���� �Ǻ��� �������� ���ʿ��� �Ǻ����� �۰ų� ���� ���� ���Ҵ�.
		_mArray[left] = pivot;
		pivot = left;
		left = l_hold;
		right = r_hold;

		// ���ȣ���� �����Ѵ�.
		if (left < pivot)
			QuickSortProcessor(_mArray, left, pivot - 1);
		if (right > pivot)
			QuickSortProcessor(_mArray, pivot+1, right);
	}

	/**
	*@brief �迭���� �ش� ���� �ε����� �����˻��� ���Ͽ� ã�´�.
	*@return �ش� ���� �ε�����
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
	 *@brief �迭���� �ش� ���� �ε����� �����˻��� ���Ͽ� ã�´�.
	 *@return �ش� ���� �ε�����
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