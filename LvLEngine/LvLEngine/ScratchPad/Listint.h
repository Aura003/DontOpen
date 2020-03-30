#pragma once
class Listint
{
public:
	Listint();
	Listint(int capacity);
	~Listint();
	void Add(int d);
	int* GetBuffer();
	int Count();
	int GetCapacity();
	void Pop(bool resize); //remove the last element of the list
	void PopFirst(); //remove the first element of the list
	void TrimExcess();
	void Clear();
	void Insert(int whichindex, int whatvalue);
	void RemoveAt(int whichindex);
private:
	int* _parr = 0;
	int _capacity = 10;
	int _count = 0;
};

