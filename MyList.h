#pragma once
template <class T>
class MyList
{
	struct Node {
		T val;
		Node * prev;
		Node * next;
	};
public:
	MyList() {
		head = new Node; // DUMMY NODE ����
		head->prev = nullptr;
		head->next = nullptr;
		size = 0;
	}
	//��� ����
	void Insert(const T& _val) {
		Node * newNode = new Node;
		newNode->val = _val;
		newNode->next = head->next;
		newNode->prev = head;
		head->next = newNode;
		++size;
	}
	//��� ����
	void Insert(T&& _val) {
		Node * newNode = new Node;
		newNode->val = _val;
		newNode->next = head->next;
		newNode->prev = head;
		head->next = newNode;
		++size;
	}
	//ù��° ��� ��ȸ
	T First() {
		if (head->next != nullptr) {
			before = head;
			cur = head->next;
			return cur->val;
		}
	}
	//���� ��� ��ȸ
	T Next() {
		if (cur->next != nullptr) {
			before = cur;
			cur = cur->next;
			cur->prev = before;
			return cur->val;
		}
	}
	//���� ��� ��ȸ
	T Prev() {
		if (before->prev != nullptr) {
			before = before->prev;
			cur = cur->prev;
			return cur->val;
		}
	}
	//���� ��ġ ��� ����
	void Remove() {
		if (cur != head) {
			Node *rNode = cur;

			before->next = cur->next;
			cur->next->prev = before;
			cur = before;
			--size;
			delete rNode;
		}
	}
	//��� ��� ����
	void Clear() {
		cur = head;
		while (cur->next != nullptr) {
			before = cur;
			cur = cur->next;
			--size;
			delete before;
		}
	}
	const T& SIZE() const {
		return size;
	}
private:
	Node * head;
	Node * before;
	Node * cur;
	size_t size;
};

