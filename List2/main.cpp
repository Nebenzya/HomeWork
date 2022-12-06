#include<iostream>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;

public:
	friend class ForwardList;
	friend class Iterator;

	Element(int data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(data), pNext(pNext), pPrev(pPrev) {}
	~Element() {}

	int get_data()const { return Data; }
	operator int() const { return get_data(); }
};

class Iterator {
	Element* Temp;
public:
	Iterator(Element* temp) : Temp(temp) {}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	Iterator& operator--()
	{
		Temp = Temp->pPrev;
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
	Element* Tail;
	unsigned int size;

public:
	

	ForwardList() : Head(nullptr), Tail(nullptr), size(0) {}
	ForwardList(const ForwardList& other) : ForwardList()
	{
		*this = other;
	}
	ForwardList(const std::initializer_list<int>& lst) : ForwardList()
	{
		for (int i : lst)
			push_back(i);
	}
	~ForwardList()
	{
		clear();
	}

	int get_size()const { return size; }
	void push_front(int data)
	{
		Head = new Element(data, Head, nullptr);
		if (!Tail)
			Tail = Head;
		size++;
	}
	void push_back(int data)
	{
		if (!size) 
			push_front(data);
		else 
		{
			Tail->pPrev->pNext = Tail = new Element(data, nullptr, Tail);
			size++;
		}
	}
	void insert(unsigned int index, int data)
	{
		if (index <= size) 
		{
			if (index == 0)
				push_front(data);
			else if (index == size)
				push_back(data);
			else
			{
				Element* Temp;
				if (index < size / 2) 
				{
					Temp = Head;
					for (int i = 0; i < index; i++)
						Temp = Temp->pNext;
				}
				else
				{
					Temp = Tail;
					for (int i = size-1; i > index; i--)
						Temp = Temp->pPrev;
				}
				Temp->pPrev = Temp->pPrev->pNext = new Element(data, Temp, Temp->pPrev);
			}
			size++;
		}
	}
	void pop_front()
	{
		Element* erased = Head;
		Head = Head->pNext;
		if(!Head->pPrev) Head->pPrev = nullptr;
		delete erased;
		size--;
	}
	void pop_back()
	{
		Element* erased = Tail;
		Tail = Tail->pPrev;
		if (!Head->pNext) Tail->pNext = nullptr;
		delete erased;
		size--;
	}
	void erase(unsigned int index)
	{
		if (index >= size) { cout << "Error: Out of range" << endl; return; }

		if (index == 0)
			pop_front();
		else if (index == size - 1)
			pop_back();
		else
		{
			Element* Temp;
			if (index < size / 2)
			{
				Temp = Head;
				for (int i = 0; i < index; i++)
					Temp = Temp->pNext;
			}
			else
			{
				Temp = Tail;
				for (int i = size - 1; i > index; i--)
					Temp = Temp->pPrev;
			}
				
			Element* erased = Temp;
			Temp->pPrev->pNext = erased->pNext;
			Temp->pNext->pPrev = erased->pPrev;
			delete erased;
		}
		size--;
	}
	void print()const
	{
		cout << "Head:\t" << Head << endl;

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << "\t" << Temp->get_data() << "\t" << Temp->pNext << "\t" << Temp->pPrev << endl;
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
		for (int i : other)
			push_back(i);
	}
	void reverse()
	{
		ForwardList buffer;
		while (Head)
		{
			buffer.push_front(Head->get_data());
			pop_front();
		}
		this->Head = buffer.Head;
		this->Tail = buffer.Tail;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}
	Iterator begin() const { return Head; }
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
		this->Tail = obj.Tail;
		this->size = obj.size;
		obj.Head = nullptr;
		obj.Tail = nullptr;
		obj.size = 0;
		return *this;
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
	ForwardList list = { 3, 5, 8, 13, 21 };
	list.print();
	list.reverse();
	list.erase(3);
	list.print();

	list.insert(4, 77);
	list.print();
	list.pop_front();

	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;
}