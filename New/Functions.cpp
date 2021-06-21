#include "Headlines.h"



template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
{
	this->Data = Data;
	this->pNext = pNext;
	this->pPrev = pPrev;
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::BaseIterator::BaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "BITConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::BaseIterator::~BaseIterator()
{
#ifdef DEBUG
	cout << "BITDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>bool List<T>::BaseIterator::operator==(const BaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::BaseIterator::operator!=(const BaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>const T& List<T>::BaseIterator::operator*()const
{
	return Temp->Data;
}
template<typename T>T& List<T>::BaseIterator::operator*()
{
	return Temp->Data;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::Iterator::Iterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::Iterator::~Iterator()
{
#ifdef DEBUG
	cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>typename List<T>::Iterator& List<T>::Iterator::operator++()	//Prefix increment
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}

template<typename T>typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
	Iterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::Iterator& List<T>::Iterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::Iterator List<T>::Iterator::operator--(int)
{
	Iterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>List<T>::ReverseIterator::ReverseIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RITConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ReverseIterator::~ReverseIterator()
{
#ifdef DEBUG
	cout << "RITDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>typename List<T>::ReverseIterator& List<T>::ReverseIterator::operator++()
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ReverseIterator List<T>::ReverseIterator::operator++(int)
{
	ReverseIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ReverseIterator& List<T>::ReverseIterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ReverseIterator List<T>::ReverseIterator::operator--(int)
{
	ReverseIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>size_t List<T>::getSize()const
{
	return size;
}

template <typename T>const typename List<T>::Iterator List<T>::begin()const
{
	return Head;
}
template <typename T> typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template <typename T>const typename List<T>::Iterator List<T>::end()const
{
	return nullptr;
}
template <typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template <typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template <typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(int size) :List()
{
	while (size--)push_back(0);
}
template<typename T>List<T>::List(const initializer_list<T>& il) : List()
{
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
		push_back(*it);
}
template<typename T>List<T>::List(const List<T>& other) :List()
{
	for (T i : other)push_back(i);
	cout << "CopyConstuctor:\t" << this << endl;
}
template <typename T>List<T>::List(List<T>&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;
	cout << "MoveConstructor:\t" << this << endl;
}
template <typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//				Operators:
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (T i : other)push_back(i);
	cout << "CopyAssignment:\t" << this << endl;
}
template<typename T>List<T>& List<T>::operator=(List<T>&& other)
{
	while (Head)pop_front();
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;
	cout << "MoveAssignment:\t" << this << endl;
	return *this;
}
template <typename T>T& List<T>::operator[](size_t index)
{
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
	}
	return Temp->Data;
}

//				Adding elements:
template <typename T>void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template <typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template <typename T>void List<T>::insert(unsigned int Index, T Data)
{
	if (Index > size)return;
	if (Index == 0)
	{
		push_front(Data);
		return;
	}
	if (Index == size)
	{
		push_back(Data);
		return;
	}
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}

//			Erasing elements:
template <typename T>void List<T>::pop_front()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template <typename T>void List<T>::pop_back()
{
	if (Head == Tail)
	{
		delete Tail;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template <typename T>void List<T>::erase(size_t index)
{
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index == size - 1)
	{
		pop_back();
		return;
	}
	if (index >= size)return;

	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
	}
	//1) Исключаем удаляемый элемент из списка:
	Temp->pPrev->pNext = Temp->pNext;	//В указатель pNext элемента Temp->pPrev записываем адрес элемента Temp->pNext
	Temp->pNext->pPrev = Temp->pPrev;	//В указатель pPrev элемента Temp->pNext записываем адрес элемента Temp->pPrev
	//2) Удаляем элемент из памяти:
	delete Temp;
	//Mission complete
}

//			Methods:
template <typename T>void List<T>::print()
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}
template <typename T>void List<T>::print_reverse()
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (T i : right)cat.push_back(i);
	return cat;
}