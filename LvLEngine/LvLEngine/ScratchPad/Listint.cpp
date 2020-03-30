#include "Listint.h"
#include<iostream>
Listint::Listint()
{
	//_parr = new int[_capacity];
	_parr = (int*)malloc(sizeof(int) * _capacity);
}

Listint::Listint(int capacity)
{
	_capacity = capacity;
	//_parr = new int[_capacity];
	_parr = (int*)malloc(sizeof(int) * _capacity);
}

Listint::~Listint()
{
	if (_parr)
		delete _parr;
	_parr = 0;
}

void Listint::Add(int d)
{
	if (_capacity <= _count) 
	{
		//above the capacity
		int* newarr = (int*)malloc(sizeof(int) * (_capacity + 1)); //allocate new mem for new array
		int oldsize = sizeof(int) * _capacity; //16 bytes
		memcpy_s(newarr, oldsize, _parr, oldsize);
		delete _parr;
		_parr = newarr;
		_capacity++;
	}
		_parr[_count] = d;
		_count++;
}

int* Listint::GetBuffer()
{
	return _parr;
}

int Listint::Count()
{
	return _count;
}

int Listint::GetCapacity()
{
	return _capacity;
}

void Listint::Pop(bool resize)
{
	//remove the last element of the array and resize the array to the corresponding _count amount
	_count--;
	//_capacity--;
	_parr[_count] = NULL;
	if (_capacity > _count) 
	{
		resize = true;
	}
	if (resize) 
	{
		TrimExcess();
	}
}

void Listint::PopFirst()
{
	if (_count != 0)
	{
		//remove the first element of the array

		int* fromsecond = _parr + 1;

		int newsize = sizeof(int) * (_capacity - 1);
		int* newarr = (int*)malloc(sizeof(int) * (_capacity - 1));
		memcpy_s(newarr, newsize, fromsecond, newsize);
		delete _parr;
		_parr = newarr;
		_capacity--;
		_count--;
		
	}
	else
		return;
	//printf("first element is : %d, second element is :%d \n", kk,jj);


	
}

void Listint::TrimExcess()
{
		_capacity = _count;
		int* newarr = (int*)malloc(sizeof(int) * _capacity);
		int size = sizeof(int) * _capacity;
		memcpy_s(newarr, size, _parr, size);
		delete _parr;
		_parr = newarr;
}

void Listint::Clear()
{
	delete _parr;
	_count = 0;
	_capacity = 0;
}

void Listint::Insert(int whichindex, int whatvalue)
{
	int* newarr = (int*)(sizeof(int) * (whichindex));
	int sizetocpy = sizeof(int) * whichindex;
	memcpy_s(newarr, sizetocpy, _parr, sizetocpy);

	newarr[whichindex] = whatvalue;
	_count++;
	_capacity++;

	int newsizetocpy = sizeof(int) * (_capacity);
	memcpy_s(newarr + whichindex, newsizetocpy, _parr + whichindex, newsizetocpy);
}

void Listint::RemoveAt(int whichindex)
{
	_parr[whichindex] = NULL;
	_capacity--;
	_count--;
}
