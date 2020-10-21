#pragma once
#include <xmemory>
#include <iostream>
template<class Vec>
class My_Const_Iterator
{
public:
	// iterator traits
	using iterator_category = std::random_access_iterator_tag;
	using value_type = typename Vec::value_type;
	using difference_type = typename Vec::difference_type;
	using pointer = typename Vec::pointer;
	using reference = typename Vec::reference;
	My_Const_Iterator()
		: ptr()
	{
	}
	My_Const_Iterator(pointer _ptr)
		: ptr(_ptr)
	{
	}
	pointer operator->() const {
		return ptr;
	}
	reference operator*() const {
		return (*ptr);
	}
	My_Const_Iterator& operator++() { // 전위
		++ptr;
		return (*this);
	}
	My_Const_Iterator operator++(int) { //후위
		My_Const_Iterator temp = *this;
		++(*this);
		return temp;
	}
	My_Const_Iterator& operator--() { //전위
		--ptr;
		return *this;
	}
	My_Const_Iterator operator--(int) { //후위
		My_Const_Iterator temp = *this;
		--(*this);
		return temp;
	}
	My_Const_Iterator& operator+=(const difference_type _type) {
		ptr += _type;
		return *this;
	}
	const My_Const_Iterator operator+(const difference_type _type) const {
		My_Const_Iterator temp = *this;
		return (temp += _type);
	}

	My_Const_Iterator& operator-=(const difference_type _type) {
		return *this += -_type;
	}

	const My_Const_Iterator operator-(const difference_type _type) const {
		My_Const_Iterator temp = *this;
		return (temp -= _type);
	}
	bool operator==(const My_Const_Iterator& _obj) const {
		return ptr == _obj.ptr ? true : false;
	}
	bool operator!=(const My_Const_Iterator& _obj) const {
		return !(*this == _obj);
	}
	reference operator[](const difference_type _type) const {
		return *(*this + _type);
	}
	bool operator<(const My_Const_Iterator& _obj) const { // obj < operator
		return *ptr < *(_obj.ptr) ? true : false;
	}
	bool operator>=(const My_Const_Iterator& _obj) const { // obj < operator
		return !(*this < _obj);
	}
	bool operator>(const My_Const_Iterator& _obj) const { // obj < operator
		return *ptr > *(_obj.ptr) ? true : false;
	}
	bool operator<=(const My_Const_Iterator& _obj) const { // obj < operator
		return !(*this > _obj);
	}
	pointer ptr;
};
template<class Vec>
class My_Iterator
	: public My_Const_Iterator<Vec> {
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = typename Vec::value_type;
	using difference_type = typename Vec::difference_type;
	using pointer = typename Vec::pointer;
	using reference = typename Vec::reference;
	using base = My_Const_Iterator<Vec>;
	My_Iterator()
	{
	}
	My_Iterator(pointer _ptr)
		: base(_ptr)
	{
	}
	reference operator*() const {
		return (base::operator*());
	}
	pointer operator->() const {
		return (base::operator->());
	}
	My_Iterator& operator++() { // 전위
		++(*(base *)this);
		return *this;
	}
	My_Iterator operator++(int) { //후위
		My_Iterator tmp = *this;
		++(*this);
		return tmp;
	}
	My_Iterator& operator--() {
		--(*(base *)this);
		return *this;
	}
	My_Iterator operator--(int) { //후위
		My_Iterator tmp = *this;
		--(*this);
		return tmp;
	}
	My_Iterator& operator+=(const difference_type _type) {
		(*(base *)this) += _type;
		return *this;
	}
	const My_Iterator operator+(const difference_type _type) const {
		My_Iterator tmp = *this;
		return (tmp += _type);
	}
	My_Iterator& operator-=(const difference_type _type) {
		return (*this += -_type);
	}
	const My_Iterator operator-(const difference_type _type) const {
		My_Iterator tmp = *this;
		return (tmp -= _type);
	}
	reference operator[](const difference_type _type) const {
		return *(*this + _type);
	}
};
template<class T,
	class Alloc = allocator<T>>
	class MyVector
{
public:
	using value_type = T;
	using difference_type = int;
	using pointer = value_type * ;
	using reference = value_type & ;
	using iterator = My_Iterator<MyVector<T, Alloc>>;
	using const_iterator = My_Const_Iterator<MyVector<T, Alloc>>;
	using size_type = unsigned int;

	iterator Begin() {
		return iterator(first);
	}
	const_iterator Begin() const {
		return const_iterator(first);
	}
	iterator End() {
		return iterator(last);
	}
	const_iterator End() const {
		return const_iterator(last);
	}
	MyVector() // basic
		: size(0), capacity(0), arr(nullptr)
	{
	}
	explicit MyVector(const T& val) // T L
	{
		arr = new T[++capacity];
		arr[size++] = val;
		Set_PtrVal();
	}
	explicit MyVector(const MyVector& val) // construct L
	{
		size = val.size;
		capacity = val.capacity;
		arr = new T[size];
		for (int i = 0; i < size; i++)
			arr[i] = val.arr[i];
		Set_PtrVal();
	}
	explicit MyVector(MyVector&& val) // construct R
	{
		size = val.size;
		capacity = val.capacity;
		arr = val.arr;
		Set_PtrVal();

		val.arr = nullptr;
		val.size = 0;
		val.capacity = 0;
	}
	reference operator[](int idx) {
		_STL_VERIFY(idx < size, " out of range"); 
		return *(first + idx);
	}
	MyVector& operator=(const MyVector& _obj) {
		size = _obj.size;
		capacity = _obj.capacity;
		arr = new T[size];
		for (size_type i = 0; i < size; i++)
			arr[i] = _obj.arr[i];
		Set_PtrVal();
		return *this;
	}
	bool operator==(const MyVector& _obj) {
		return arr == _obj.arr ? true : false;
	}
	bool operator!=(const MyVector& _obj) {
		return !(*this == _obj);
	}
	~MyVector()
	{
		delete[] arr;
	}
	const size_type& Capacity() const {
		return capacity;
	}
	const size_type& Size() const {
		return size;
	}
	iterator Erase(const_iterator _where) { // iterator 대응 값 삭제 후 배열 재할당
		iterator remove_val;
		pointer tmp = new T[capacity];
		size_type tmp_idx = 0;
		
		for (size_type i = 0; i < size; ++i)
		{
			if ((first + i) != _where.ptr) {
				tmp[tmp_idx] = arr[i];
			}
			else {
				tmp[tmp_idx] = arr[++i];
				remove_val = iterator(arr + i);
			}
			++tmp_idx;
		}
		delete[] arr; 
		arr = tmp;
		Set_PtrVal(); // last , end 포인터 값 대입
		--size;
		return remove_val;
	}
	void Clear() { // 기존 배열 삭제 후 새 배열과 swap 
		pointer newArr = new T[capacity];
		delete[] arr;
		arr = newArr;
		size = 0;
		Set_PtrVal();
	}
	bool Empty() { // 시작과 끝이 같은지 판단하여 비었는지 확인 
		return first == last;
	}
private:
	int Alloc_Capacity() { // capacity 할당
		if (capacity < 5) ++capacity;
		else capacity = capacity * 2;
		return capacity;
	}
public:
	void Push_back(const T& val) { // 배열 끝에 val 삽입
		if (size == capacity) {
			T *temp = new T[Alloc_Capacity()];
			for (int i = 0; i < size; i++) {
				temp[i] = arr[i];
			}
			Set_Iter_Val(temp);
			delete[] arr;
			arr = temp;
			arr[size++] = val;
			Set_PtrVal();
		}
		else {
			arr[size++] = val;
			Set_PtrVal();
		}
	}
	void Push_back(T&& val) { // 배열 끝에 val 삽입
		if (size == capacity) {
			T *temp = new T[Alloc_Capacity()];
			for (int i = 0; i < size; i++) {
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = temp;
			arr[size++] = val;
			Set_PtrVal();
		}
		else {
			arr[size++] = val;
			Set_PtrVal();
		}
	}
	void Pop_back() {
		T *temp = new T[--size];
		for (int i = 0; i < size; i++)
			temp[i] = arr[i];
		delete[]arr;
		arr = temp;
		Set_PtrVal();
	}
	void Assign(const size_type _new_size, const T &_val) {
		delete[] arr;
		size = _new_size;
		capacity = _new_size;
		arr = new T[_new_size];
		for (size_type i = 0; i < _new_size; i++) {
			arr[i] = _val;
		}
		Set_PtrVal();
	}
	T& At(const size_type _Pos) {
		return arr[_Pos];
	}
	const T& At(const size_type _Pos) const {
		return arr[_Pos];
	}
	T& Back() {
		return *(last - 1);
	}
	const T& Back() const {
		return *(last - 1);
	}
	T& Front() {
		return *first;
	}
	const T& Front() const{
		return *first;
	}
	iterator Insert(const_iterator _where , const T& _val) {
		T* new_arr = new T[++capacity];	
		size_type newArr_idx = 0 , oldArr_idx = 0;
		++size;
		while(newArr_idx < size){
			if (_where.ptr - first != newArr_idx) {
				new_arr[newArr_idx] = arr[oldArr_idx];
				++oldArr_idx;
			}
			else {
				new_arr[newArr_idx] = _val;
			}
			++newArr_idx;
		}
		delete[] arr;
		arr = new_arr;
		Set_PtrVal();
		return iterator(_where.ptr);
	}
	void Resize(const size_type _new_size , const T& _val = 0) {
		if (_new_size > capacity) {
			T* new_arr = new T[_new_size];
			for (size_type i = 0; i < size; i++) {
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
			capacity = _new_size;
		}
		if (_new_size < size) {
			T* new_arr = new T[capacity];
			for (size_type i = 0; i < _new_size; i++) {
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
			size = _new_size;
		}
		for (size_type i = size; i < _new_size; i++) {
			arr[i] = _val;
			++size;
		}
		Set_PtrVal();
	}
	void Reserve(const size_type &_new_cap) {
		if (capacity < _new_cap) {
			capacity = _new_cap;
			T* new_arr = new T[capacity];
			for (size_type i = 0; i < size; i++) {
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
			Set_PtrVal();
		}
	}
	void Swap(MyVector& _obj) {
		if (*this != _obj) {
			MyVector tmp(_obj);
			_obj = *this;
			*this = tmp;
		}
	}
private:
	pointer arr;
	size_type size;
	size_type capacity;

	pointer first; // 배열 시작
	pointer last; // 배열의 현재 끝
	pointer end; // 배열 끝
	
	void Set_PtrVal() {
		first = arr;
		last = first + size;
		end = first + capacity;
	}
};