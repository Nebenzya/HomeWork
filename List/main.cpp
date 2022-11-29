//ForwardList
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;	

public:

	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList;
};

class ForwardList
{
	Element* Head;
	Element* LastElement;
	unsigned int size;

public:
	int get_size()const { return size; }

	ForwardList() :Head(nullptr), size(0)
	{
		cout << "LConstructor:\t" << this << endl;
	}

	ForwardList(const ForwardList& obj) 
	{
		Element* Temp = obj.Head;
		while (Temp)
		{
			this->push_back(Temp->Data);
			Temp = Temp->pNext;
		}

		cout << "LCopyConstructor:\t" << this << endl;
	}

	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;

		Element* Temp = Head;
		while (size)
		{
			Element* erased = Temp;
			Temp = Temp->pNext;
			delete erased;
			size--;
		}
	}

	void push_front(int Data)
	{
		Element* New = new Element(Data);

		if (!size) LastElement = New;

		New->pNext = Head;
		Head = New;
		size++;
	}
	void push_front(Element* el) {
		if (!size) LastElement = el;

		el->pNext = Head;
		Head = el;
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);

		LastElement->pNext = New;
		LastElement = New;
		size++;
	}
	void push_back(Element* el) {
		if (Head == nullptr)return push_front(el);
		LastElement->pNext = el;
		LastElement = el;
		size++;
	}


	void insert(int Index, int Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)
		{
			cout << "Error: Out of range" << endl;
			return;
		}

		Element* New = new Element(Data);
		Element* Temp = Head;

		for (int i = 0; i < Index - 1; i++)
			Temp = Temp->pNext;

		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void pop_front()
	{
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;

		while (Temp->pNext->pNext)
			Temp = Temp->pNext;

		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}


	void print()const
	{
		Element* Temp = Head;
		cout << "Head:\t" << Head << endl;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	
		}
		cout << "Количество элементов списка:\t  " << size << endl;
	}

	ForwardList& operator=(const ForwardList& obj)
	{
		this->Head = obj.Head;
		this->LastElement = obj.LastElement;
		this->size = obj.size;
		return *this;
	}
	ForwardList& operator=(ForwardList&& obj)
	{
		this->Head = obj.Head;
		this->LastElement = obj.LastElement;
		this->size = obj.size;
		obj.Head = nullptr;
		obj.LastElement = nullptr;
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
		{
			cout << "Error Index!" << endl;
		}
	}
};

ForwardList operator+(const ForwardList &left, const ForwardList &right) 
{
	ForwardList result;
	for (int i = 0; i < left.get_size(); i++)
	{
		result.push_back(left[i]);
	}

	for (int i = 0; i < right.get_size(); i++)
	{
		result.push_back(right[i]);
	}
	return result;
}

void main()
{
	setlocale(LC_ALL, "");


	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();

	ForwardList list3 = list1 + list2;
	list3.print();
}