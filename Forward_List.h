#pragma once

#include <iostream>

template <class T>
class Forward_List {

	class Node {
	public:
		Node* next = nullptr;
		T data;
	};

	Node* head = nullptr;
	int size = 0;

public:
	
	Forward_List() {} // ����������� �� ���������
	Forward_List(Forward_List& other); // ����������� �����������
	Forward_List(Forward_List&& other); // ����������� ��������
	~Forward_List();   // ����������

	int _size(); // ��������� ������� ���������
	void push_front(const T& data); // ������� � ������ ���������
	void push_back(const T& data); // ������� � ����� ���������
	void push_after(int index, const T& data); // ������� ����� �������� � �������� index
	void pop_front(); // �������� ������� ��������
	void pop_back();  // �������� ���������� ��������
	void pop_after(int index); // �������� ��������'����� �������� � �������� index
	void print() const; // ����� ��������� �� �������
	void sort_asc(); // ���������� �� �����������
	void sort_desc(); // ���������� �� ��������

	T& operator[](int index); // 
	Forward_List& operator=(Forward_List& other);
	bool operator==(Forward_List& other);
	bool operator!=(Forward_List& other);
};

template<class T>
Forward_List<T>::Forward_List(Forward_List& other) // ����������� �����������
{
	for (int i = other.size - 1; i >= 0; i--)
		this->push_front(other[i]);
}

template<class T>
Forward_List<T>::Forward_List(Forward_List&& other) // ����������� ��������
{
	size = other.size;
	head = other.head;
	other.head = nullptr;
}

template<class T>
Forward_List<T>::~Forward_List()  // ����������
{
	while (size > 0) pop_front();
}

template<class T>
inline int Forward_List<T>::_size()   // ��������� ������� ���������
{
	return size;
}

template<class T>
void Forward_List<T>::push_front(const T& data)  // ������� � ������ ���������
{
	if (head == nullptr) {
		head = new Node();
		head->data = data;
	}
	else {
		Node* temporary = new Node();
		temporary->next = head;
		temporary->data = data;
		head = temporary;
	}
	size++;
}

template<class T>
void Forward_List<T>::push_back(const T& data) // ������� � ����� ���������
{
	push_after(size - 1, data);
}

template<class T>
void Forward_List<T>::push_after(int index, const T& data) // ������� ����� �������� � �������� index
{
	if (index < 0 || index >= size) throw std::exception("incorect index!!!");
	Node* temporary = head;
	int _index = 0;

	while (_index != index) {
		temporary = temporary->next;
		_index++;
	}

	Node* new_node = new Node();
	new_node->data = data;
	new_node->next = temporary->next;
	temporary->next = new_node;
	size++;
}

template<class T>
void Forward_List<T>::pop_front() // �������� ������� ��������
{
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
	}
	else {
		Node* temporary = head->next;
		delete head;
		head = temporary;
	}
	size--;
}

template<class T>
void Forward_List<T>::pop_back() // �������� ���������� ��������
{
	pop_after(size - 2);
}

template<class T>
void Forward_List<T>::pop_after(int index)  // �������� ��������'����� �������� � �������� index
{
	if (index < 0 || index >= size - 1) throw std::exception("incorect index!!!");
	Node* temporary = head;
	int _index = 0;

	while (_index != index) {
		temporary = temporary->next;
		_index++;
	}
	Node* copy = temporary->next;
	temporary->next = copy->next;
	delete copy;
	size--;
}

template<class T>
void Forward_List<T>::print() const  // ����� ��������� �� �������
{
	Node* temporary = head;
	while (temporary != nullptr) {
		std::cout << temporary->data << "   ";
		temporary = temporary->next;
	}
	std::cout << "\n";
}

template<class T>
void Forward_List<T>::sort_asc()
{
	for (int i = 0; i < size - 1; i++) {
		Node* start1 = head;
		Node* start2 = start1->next;
		for (int j = 0; j < size - 1 - i; j++) {
			if (start1->data > start2->data)
				std::swap(start1->data, start2->data);
			start1 = start1->next;
			start2 = start2->next;
		}
	}
}

template<class T>
void Forward_List<T>::sort_desc()
{
	for (int i = 0; i < size - 1; i++) {
		Node* start1 = head;
		Node* start2 = start1->next;
		for (int j = 0; j < size - 1 - i; j++) {
			if (start1->data < start2->data)
				std::swap(start1->data, start2->data);
			start1 = start1->next;
			start2 = start2->next;
		}
	}
}

template<class T>
T& Forward_List<T>::operator[](int index)  // ���������� ��������� []
{
	if (index < 0 || index >= size) throw std::exception("incorect index!!!");
	Node* temporary = head;
	int _index = 0;

	while (_index != index) {
		temporary = temporary->next;
		_index++;
	}
	return temporary->data;
}

template<class T>
Forward_List<T>& Forward_List<T>::operator=(Forward_List& other)
{
	if (this == &other) return *this;
	for (int i = other.size - 1; i >= 0; i--)
		this->push_front(other[i]);
	return *this;
}

template<class T>
bool Forward_List<T>::operator==(Forward_List& other)
{
	if (size != other.size) return false;
    
	Node* start1 = head;
	Node* start2 = other.head;
	
	while (start1 != nullptr) {
		if (start1->data != start2->data) return false;
		start1 = start1->next;
		start2 = start2->next;
	}
	return true;
}

template<class T>
bool Forward_List<T>::operator!=(Forward_List& other)
{
	if (*this == other) return false;
	return true;
}