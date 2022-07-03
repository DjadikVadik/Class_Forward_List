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
	
	Forward_List() {} // конструктор по умолчанию
	Forward_List(Forward_List& other); // конструктор копирования
	Forward_List(Forward_List&& other); // конструктор переноса
	~Forward_List();   // деструктор

	int _size(); // получение размера коллекции
	void push_front(const T& data); // вставка в начало коллекции
	void push_back(const T& data); // вставка в конец коллекции
	void push_after(int index, const T& data); // вставка после элемента с индексом index
	void pop_front(); // удаление первого элемента
	void pop_back();  // удаление последнего элемента
	void pop_after(int index); // удаление элемента'после элемента с индексом index
	void print() const; // вывод коллекции на консоль
	void sort_asc(); // сортировка по возростанию
	void sort_desc(); // сортировка по убыванию

	T& operator[](int index); // 
	Forward_List& operator=(Forward_List& other);
	bool operator==(Forward_List& other);
	bool operator!=(Forward_List& other);
};

template<class T>
Forward_List<T>::Forward_List(Forward_List& other) // конструктор копирования
{
	for (int i = other.size - 1; i >= 0; i--)
		this->push_front(other[i]);
}

template<class T>
Forward_List<T>::Forward_List(Forward_List&& other) // конструктор переноса
{
	size = other.size;
	head = other.head;
	other.head = nullptr;
}

template<class T>
Forward_List<T>::~Forward_List()  // деструктор
{
	while (size > 0) pop_front();
}

template<class T>
inline int Forward_List<T>::_size()   // получение размера коллекции
{
	return size;
}

template<class T>
void Forward_List<T>::push_front(const T& data)  // вставка в начало коллекции
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
void Forward_List<T>::push_back(const T& data) // вставка в конец коллекции
{
	push_after(size - 1, data);
}

template<class T>
void Forward_List<T>::push_after(int index, const T& data) // вставка после элемента с индексом index
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
void Forward_List<T>::pop_front() // удаление первого элемента
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
void Forward_List<T>::pop_back() // удаление последнего элемента
{
	pop_after(size - 2);
}

template<class T>
void Forward_List<T>::pop_after(int index)  // удаление элемента'после элемента с индексом index
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
void Forward_List<T>::print() const  // вывод коллекции на консоль
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
T& Forward_List<T>::operator[](int index)  // перегрузка оператора []
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