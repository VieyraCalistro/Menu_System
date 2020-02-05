#include "pch.h"
#pragma once

template<typename Type>


class DynArray
{
public:
	DynArray();
	~DynArray();

	DynArray(const DynArray<Type>& that);

	DynArray<Type>& operator=(const DynArray<Type>& that);

	const Type& operator[](const unsigned int index) const;

	Type& operator[](const unsigned int index);

	void append(const Type& item);

	void clear();

	void reserve(const unsigned int & newCap = 0);

	unsigned int size() const;
	void SetSize(unsigned int newSize);

	unsigned int capacity() const;
	void SetCapacity(unsigned int newCapacity);




protected:

	Type* Array;

	unsigned int _size;

	unsigned int _capacity;



};

template<typename Type>
unsigned int DynArray<Type>::capacity() const
{
	return _capacity;
}


template<typename Type>
void DynArray<Type>::SetCapacity(unsigned int newCapacity)
{
	_capacity = newCapacity;
}


template<typename Type>
unsigned int DynArray<Type>::size() const
{
	return _size;
}


template<typename Type>
void DynArray<Type>::SetSize(unsigned int newSize)
{
	_size = newSize;
}


template<typename Type>
DynArray<Type>::DynArray()
{
	this->Array = nullptr;
	SetCapacity(0);
	SetSize(0);
}


template<typename Type>
DynArray<Type>::~DynArray()
{
	delete[] this->Array;
}


template<typename Type>
DynArray<Type>::DynArray(const DynArray<Type>& that)
{
	this->SetCapacity(that.capacity());
	this->SetSize(that.size());
	

	// allocate the pointer and make a for loop and copy everything over
	this->Array = new Type[that.capacity()];

	for (unsigned int index = 0; index < that.size(); index++)
	{
		this->Array[index] = that[index];
	}
}


template<typename Type>
DynArray<Type>& DynArray<Type>::operator=(const DynArray<Type>& that)
{
	if (this != &that)
	{

		delete[] this->Array;

		this->SetCapacity(that.capacity());
		this->SetSize(that.size());

		this->Array = new Type[that.capacity()];

		for (unsigned int index = 0; index < that.size(); index++)
		{
			this->Array[index] = that[index];
		}


	}

	return *this;
}

template<typename Type>
const Type & DynArray<Type>::operator[](const unsigned int index) const
{

	return Array[index];

}


template<typename Type>
Type & DynArray<Type>::operator[](const unsigned int index)
{

	return Array[index];

}

template<typename Type>
void DynArray<Type>::append(const Type & item)
{

	if (size() == capacity() && capacity() != 0)
	{
		unsigned int doubleCapacity = capacity() * 2;

		Type* temp = new Type[capacity()];

		for (unsigned int index1 = 0; index1 < capacity(); index1++)
		{
			temp[index1] = this->Array[index1];
		}

		delete[] this->Array;

		this->Array = new Type[doubleCapacity];

		for (unsigned int index = 0; index < capacity(); index++)
		{
			this->Array[index] = temp[index];
		}

		delete[] temp;

		SetCapacity(doubleCapacity);
		
	}
	else if (capacity() == 0)
	{

		this->Array = new Type[1];
		SetCapacity(1);

	}
	
	Array[size()] = item;
	SetSize(size() + 1);
	
	

}



template<typename Type>
inline void DynArray<Type>::clear()
{
	
	delete[] Array;

	Array = nullptr;
	SetCapacity(0);
	SetSize(0);

}

template<typename Type>
void DynArray<Type>::reserve(const unsigned int & newCap)
{

	if (newCap == 0)
	{
		if (capacity() == 0)
		{
			SetCapacity(1);
		}
		else
		{
			unsigned int doubleCapacity = capacity() * 2;

			SetCapacity(doubleCapacity);
		}
		
	}
	else if (newCap > capacity())
	{

		SetCapacity(newCap);

	}

	Type* temp = new Type[capacity()];

	for (unsigned int index = 0; index < size(); index++)
	{

		temp[index] = this->Array[index];

	}

	delete[] this->Array;

	this->Array = temp;
	

};









