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

	Element(int data, Element* pNext = nullptr) :Data(data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	int get_data()const { return Data; }
	operator int() const { return get_data(); }

	 Element* operator++() const
	 {
		return pNext;
	 }

	 Element* operator++(int) const
	 {
		 return pNext;
	 }
};

class ForwardList
{
	Element* Head;
	unsigned int size;

public:
	int get_size()const { return size; }

	ForwardList() : Head(nullptr), size(0)
	{
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) : ForwardList()
	{
		*this = other;

		cout << "LCopyConstructor:\t" << this << endl;
	}

	ForwardList(std::initializer_list<int> lst) : ForwardList()
	{
		for (int i : lst)
			push_back(i);
	}
	~ForwardList()
	{
		clear();
		cout << "LDestructor:\t" << this << endl;
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
			for (Element* Temp = Head, int i = 0; Temp; Temp = Temp->pNext, i++)
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
		for (int i = size; i; i--)
		{
			buffer.push_back(this->operator[](i-1));
		}
		this->clear();
		this->copy_value(buffer);
	}

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
	Element* begin() { return Head; }
	Element* end() const { return nullptr; } // LastElement
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