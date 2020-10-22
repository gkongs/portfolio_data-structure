#pragma once
template <class T>
class MyQuickSort // 퀵 정렬
{
public:
	MyQuickSort(T* _arr,  size_t _left ,  size_t _right)
	{
		arr = _arr;
		Sort(_left,_right);
	}

private:
	void set_pivot(size_t _left, size_t _right) { // get 3 idx and select
		size_t pos[3] = { _left , (_left+_right) / 2 , _right }; 
		if (arr[pos[0]] > arr[pos[1]]) {
			Swap(pos[0], pos[1]);
		}
		if (arr[pos[1]] > arr[pos[2]]) {
			Swap(pos[1], pos[2]);
		}
		if (arr[pos[0]] > arr[pos[1]]) {
			Swap(pos[0], pos[1]);
		}
		p_idx = pos[1];
		pivot = arr[p_idx];
	}
	void Swap(const size_t _l_idx, const size_t _r_idx) {
		T tmp = arr[_l_idx];
		arr[_l_idx] = arr[_r_idx];
		arr[_r_idx] = tmp;
	}

	T Partition(size_t _left, size_t _right) { // set pos pivot and div
		set_pivot(_left, _right);
		low = _left + 1;
		high = _right;
		Swap(_left, p_idx);
		
		while (low <= high) { // low ->  <- high

			while (arr[low] <= pivot && low <= _right) {
				++low;
			}
			while (arr[high] >= pivot && high >= (_left + 1) ) {
				--high;
			}
			if (low <= high)
				Swap(low, high);
		}
		Swap(_left, high);
		return high;
	}
	void Sort(int _left, int _right) { 
		if (_left <= _right) {
			p_idx = Partition(_left, _right);
			Sort(_left, p_idx - 1);
			Sort(p_idx + 1, _right);
		}
	}
	size_t low, high, p_idx;
	T pivot;
	T *arr;
};

