//ForwardList
#include<iostream>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;

public:
	friend class ForwardList;
	friend class Iterator;

	Element(int data, Element* pNext = nullptr) :Data(data), pNext(pNext){}
	~Element() {}

	int get_data()const { return Data; }
	operator int() const { return get_data(); }
};

class Iterator {
	Element* Temp;
public:
	Iterator(Element* temp) : Temp(temp){}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator& operator++(int)
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;
	unsigned int size;

public:
	int count()const { return size; }

	ForwardList() : Head(nullptr), size(0)
	{
	}
	ForwardList(const ForwardList& other) : ForwardList()
	{
		*this = other;
	}

	ForwardList(const std::initializer_list<int>& lst) : ForwardList()
	{
		for (int i : lst)
			push_front(i);
		reverse();
	}
	~ForwardList()
	{
		clear();
	}

	void push_front(int data)
	{
		insert(0, data);
	}
	void push_back(int data)
	{
		insert(size,data);
	}
	void insert(unsigned int index, int data)
	{
		if (index > size) { cout << "Error: Out of range" << endl; return; }

		if (index == 0)
			Head = new Element(data, Head);
		else
		{
			Element* Temp = Head;
			for (int i = 0; i < index - 1; i++)
				Temp = Temp->pNext;
			Temp->pNext = new Element(data, Temp->pNext);
		}
		size++;
	}
	void pop_front()
	{
		erase(0);
	}
	void pop_back()
	{
		erase(size - 1);
	}
	void erase(unsigned int index)
	{
		if (index >= size) { cout << "Error: Out of range" << endl; return; }

		Element* erased = nullptr;
		if (index == 0) 
		{
			erased = Head;
			Head = Head->pNext;
		}
		else 
		{
			int i = 0;
			for (Element* Temp = Head; Temp; Temp = Temp->pNext, i++)
			{
				if (i == index - 1) 
				{
					erased = Temp->pNext;
					Temp->pNext = erased->pNext;
					break;
				}
			}
		}
		delete erased;
		size--;
	}
	void print()const
	{
		cout << "Head:\t" << Head << endl;

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		}
		cout << "Count elements of list\t  " << size << endl;
	}
	void clear()
	{
		while (Head)
			pop_front();
	}
	void copy_value(const ForwardList& other)
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
	}
	void reverse() 
	{
		ForwardList buffer;
		while(Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}
	Iterator begin() { return Head; }
	Iterator end() const { return nullptr; }
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		this->clear();
		this->copy_value(other);
		return *this;
	}
	ForwardList& operator=(ForwardList&& obj)
	{
		this->Head = obj.Head;
		this->size = obj.size;
		obj.Head = nullptr;
		obj.size = 0;
		return *this;
	}
	int operator[](unsigned int index)const
	{
		if (index < size)
		{
			Element* Temp = Head;
			for (int i = 0; i < size; i++)
			{
				if (i == index)
					return Temp->Data;

				Temp = Temp->pNext;
			}
		}
		else
			cout << "Error Index!" << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result;
	result.copy_value(left);
	result.copy_value(right);

	return result;
}

void main()
{
	ForwardList list = { 27, 31, 59, 13, 21 };
	list.print();
	list.reverse(); 
	
	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;
}