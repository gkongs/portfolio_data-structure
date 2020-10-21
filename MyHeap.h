#pragma once
#include <functional>
template <class T>
class MyHeap { // min_heap
public:
	MyHeap()
		: size(0), capacity(1)
	{}
	~MyHeap() { 
		delete arr; 
	}
	// 삽입
	void Insert(const T& _val) {
		if ((size + 1) == capacity) {
			T *old_arr = arr;
			arr = new T[alloc_capacity()];
			for (size_t i = 1; i < (size + 1); i++) 
				arr[i] = old_arr[i];
			delete old_arr;
		}
		arr[++size] = _val;
		push_val_heap(size);
	}
	// 삭제
	void Remove() {
		int parent_idx, l_child_idx, r_child_idx;
		parent_idx = 1;
		arr[parent_idx] = arr[size];
		while (true) {
			l_child_idx = parent_idx * 2;
			r_child_idx = parent_idx * 2 + 1;
			if (l_child_idx >= size) break;
			if (arr[parent_idx] > arr[l_child_idx]) {
				if (arr[l_child_idx] < arr[r_child_idx]) {
					Swap(arr[parent_idx], arr[l_child_idx]);
					parent_idx = l_child_idx;
				}
				else {
					if (l_child_idx >= size) break;
					Swap(arr[parent_idx], arr[r_child_idx]);
					parent_idx = r_child_idx;
				}
			}
			else if(arr[parent_idx] < arr[l_child_idx]) { 
				if (l_child_idx >= size) break;
				if (arr[r_child_idx] < arr[parent_idx]) {
					Swap(arr[parent_idx], arr[r_child_idx]);
					parent_idx = r_child_idx;
				}
				else
					break;
			}else
				break;
		}
		--size;
	} 
	T& operator[](const size_t _idx) const{
		return arr[_idx];
	}
	const size_t& SIZE() const {
		return size;
	}
private:
	// capacity 할당
	const size_t alloc_capacity() {
		if (size > 7) {
			capacity = capacity + (capacity / 2);
			return capacity;
		}
		else {
			return ++capacity;
		}
	}
	// insert help function
	void push_val_heap(size_t _cur_idx) {
		int parent_idx;

		while (_cur_idx > 1) {
			parent_idx = _cur_idx / 2;
			if (arr[parent_idx] > arr[_cur_idx]) {
				Swap(arr[parent_idx], arr[_cur_idx]);
				_cur_idx = parent_idx;
			}
			else
				break;
		}
	}
	void Swap(T& _parent , T& _child) {
		T tmp = _parent;
		_parent = _child;
		_child = tmp;
	}
	T* arr;
	size_t size;
	size_t capacity;
};

