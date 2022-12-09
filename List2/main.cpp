#include<iostream>
#include<chrono>

using std::cin;
using std::cout;
using std::endl;




class MyList
{
private:

	class Element
	{
	public:
		int Data;
		Element* pNext;
		Element* pPrev;
		Element(int data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(data), pNext(pNext), pPrev(pPrev) {}
		~Element() { }
		int get_data()const { return Data; }
		operator int() const { return get_data(); }
	};

	class Iterator 
	{
	public:
		Element* Temp;
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

	Element* Head;
	Element* Tail;
	unsigned int size;

public:
	MyList() : Head(nullptr), Tail(nullptr), size(0) {}
	MyList(const MyList& other) : MyList()
	{
		*this = other;
	}
	MyList(const std::initializer_list<int>& lst) : MyList()
	{
		for (int i : lst)
			push_back(i);
	}
	~MyList()
	{
		clear();
	}

	int count()const { return size; }
	void push_front(int data)
	{
		if (!size)
		{
			Head = Tail = new Element(data);
			size++;
			return;
		}
		Head = Head->pPrev = new Element(data, Head, nullptr);
		
		size++;
	}
	void push_back(int data)
	{
		if (!size) 
			push_front(data);
		else 
		{
			Tail = Tail->pNext = new Element(data, nullptr, Tail);
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
		if (Head == nullptr) return;
		if (Head == Tail) {
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
	void pop_back()
	{
		if (Head == Tail) pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
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
			cout << Temp << "\t" << Temp->get_data() << "\t" << Temp->pNext << "\t" << Temp->pPrev << endl;
		
		cout << "Tail:\t" << Tail << endl << "Count elements of list\t  " << size << endl;
	}
	void clear()
	{
		while (Head)
			pop_front();
	}
	void copy_value(const MyList& other)
	{
		for (int i : other)
			push_back(i);
	}
	void reverse()
	{
		MyList buffer;
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
	MyList& operator=(const MyList& other)
	{
		if (this == &other)return *this;
		this->clear();
		this->copy_value(other);
		return *this;
	}
	MyList& operator=(MyList&& obj)
	{
		this->Head = obj.Head;
		this->Tail = obj.Tail;
		this->size = obj.size;
		obj.Head = nullptr;
		obj.Tail = nullptr;
		obj.size = 0;
		return *this;
	}

	//////////////              NEW FUNCTIONS					////////////////
	
	void sort() 
	{
		if (size < 2) return;
		bool isSorting = false;
		while (!isSorting) 
		{
			isSorting = true;
			for (Element* temp = Head; temp != nullptr; temp = temp->pNext)
			{
				if (temp->pNext != nullptr && temp->pNext->Data < temp->Data)
				{
					std::swap(temp->Data, temp->pNext->Data);
					isSorting = false;
				}
			}
		}
	}
	int min() 
	{
		if (size)
		{
			int result = INT32_MAX;
			for (int i : *this)
			{
				if (i < result) result = i;
			}
			return result;
		}
	}
	int max()
	{
		if (size)
		{
			int result = INT32_MIN;
			for (int i : *this)
			{
				if (i > result) result = i;
			}
			return result;
		}
	}
};

MyList operator+(const MyList& left, const MyList& right)
{
	MyList result;
	result.copy_value(left);
	result.copy_value(right);
	return result;
}

std::chrono::steady_clock::time_point start;
#define START start = std::chrono::steady_clock::now();
#define RESULT cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() << endl;

void main()
{
	int n; cin >> n;
	MyList list;

	for (size_t i = 0; i < n; i++)
	{
		list.push_back(rand() % 1000);
	}

	cout << list.min() << "\t" << list.max() << endl;

	list.sort();
	for (int i : list) 
	{
		cout << i << "\t";
	}
	cout << endl;
}