#include "NodeOfList.h"
template <class T>
NodeOfList<T>::NodeOfList(T data, NodeOfList* next, NodeOfList* last)
{
	this->data = data;
	this->next = next;
	this->last = last;
}

template <class T>
NodeOfList<T>::NodeOfList(T data)
{
	this->data = data;
}