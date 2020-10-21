#pragma once
#include <iostream>
#include <functional>
using namespace std;
// ���� Ʈ�� [ ��ȸ�� �� ��� ]
template <class T>
class MyBTree
{
	struct Node {
		T val;
		Node *left;
		Node *right;
		Node(const T &_val)
		: val(_val){}
	};
public:
	MyBTree(const T &_val, function<bool(const T&, const T&)>_Pred) {
		root = new Node(_val);
		root->left = nullptr;
		root->right = nullptr;
		pred = _Pred;
		++size;
	}
	~MyBTree(){
		Internal_Clear(root);
	}
	// ��� �߰�
	bool Insert(const T& _val) {
		if (root == nullptr) {
			root = new Node(_val);
			root->left = nullptr;
			root->right = nullptr;
			++size;
			return true;
		}
		++size;
		return Internal_Insert(root, _val);
	}
	// ���� ��ȸ
	void Traverse_in_order() {
		Internal_traverse_in_order(root);
	}
	// ��� ��� ����
	void Clear() { 
		Internal_Clear(root);
	}
	// ũ�� ��ȯ
	const size_t SIZE() const {
		return size;
	}
private:
	bool Default_Pred(const T& parent, const T& child) {
		if (parent >= child)
			return true;
		else
			return false;
	}
	// [Wrapper] ��� �߰�
	bool Internal_Insert(Node*& _cur, const T& _val) {

		if (_cur == nullptr) {
			_cur = new Node(_val);
			_cur->left = nullptr;
			_cur->right = nullptr;
			return true;
		}
		else if ((pred(_cur->val, _val)) == true) { // TRUE �� ��� LEFT
			return Internal_Insert(_cur->left, _val);
		}
		else {										 // FALSE �� ��� RIGHT
			return Internal_Insert(_cur->right, _val);
		}
	}
	// [Wrapper] ���� ��ȸ
	void Internal_traverse_in_order(Node *_cur) {
		if (_cur == nullptr) {
			return;
		}
		Internal_traverse_in_order(_cur->left);
		cout << _cur->val << endl;
		Internal_traverse_in_order(_cur->right);
	}
	// [Wrapper] ��� ��� ����
	void Internal_Clear(Node *_cur) {
		if (_cur == nullptr) 
			return;
		Internal_Clear (_cur->left);
		Internal_Clear (_cur->right);
		delete _cur;
		root = nullptr;
		size = 0;
	}
	Node* root;
	size_t size; 
	function<bool(const T&, const T&)> pred;
};

