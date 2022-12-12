#include<iostream>

using std::cin;
using std::cout;
using std::endl;

template<typename T>
class MyList
{
private:

	template<typename T>
	class Element
	{
	public:
		T Data;
		Element<T>* pNext;
		Element<T>* pPrev;
		Element(T data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(data), pNext(pNext), pPrev(pPrev) {}
	};

	template<typename T>
	class Iterator
	{
	public:
		Element<T>* Temp;
		Iterator(Element<T>* temp) : Temp(temp) {}
		Iterator<T>& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator<T>& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		bool operator==(const Iterator<T>& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator<T>& other)const
		{
			return this->Temp != other.Temp;
		}
		const T operator*()const
		{
			return Temp->Data;
		}
		T& operator*()
		{
			return Temp->Data;
		}
	};

	Element<T>* Head;
	Element<T>* Tail;
	unsigned int size;

public:
	MyList() : Head(nullptr), Tail(nullptr), size(0) {}
	MyList(const MyList<T>& other) : MyList()
	{
		*this = other;
	}
	MyList(const std::initializer_list<T>& lst) : MyList()
	{
		for (auto i : lst)
			push_back(i);
	}
	~MyList()
	{
		clear();
	}
	void push_front(T data)
	{
		if (!size)
		{
			Head = Tail = new Element<T>(data);
			size++;
			return;
		}
		Head = Head->pPrev = new Element<T>(data, Head, nullptr);

		size++;
	}
	void push_back(T data)
	{
		if (!size)
			push_front(data);
		else
		{
			Tail = Tail->pNext = new Element<T>(data, nullptr, Tail);
			size++;
		}
	}
	void insert(unsigned int index, T data)
	{
		if (index <= size)
		{
			if (index == 0)
				push_front(data);
			else if (index == size)
				push_back(data);
			else
			{
				Element<T>* Temp;
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
				Temp->pPrev = Temp->pPrev->pNext = new Element<T>(data, Temp, Temp->pPrev);
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
			Temp->pPrev->pNext = Temp->pNext;
			Temp->pNext->pPrev = Temp->pPrev;
			delete Temp;
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
	void copy_value(const MyList<T>& other)
	{
		for (auto i : other)
			push_back(i);
	}
	void reverse()
	{
		MyList<T> buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->Tail = buffer.Tail;
		this->size = buffer.size;
		buffer.Head = buffer.Tail = nullptr;
	}
	Iterator<T> begin() const { return Head; }
	Iterator<T> end() const { return nullptr; }
	MyList<T>& operator=(const MyList<T>& other)
	{
		if (this == &other)return *this;
		this->clear();
		this->copy_value(other);
		return *this;
	}
	MyList<T>& operator=(MyList<T>&& obj)
	{
		this->Head = obj.Head;
		this->Tail = obj.Tail;
		this->size = obj.size;
		obj.Head = obj.Tail = nullptr;
		obj.size = 0;
		return *this;
	}

};

template<typename T>
MyList<T> operator+(const MyList<T>& left, const MyList<T>& right)
{
	MyList<T> result;
	result.copy_value(left);
	result.copy_value(right);
	return result;
}

#define TYPE char

void main()
{
	int n; cin >> n;
	MyList<TYPE> list;

	for (size_t i = 0; i < n; i++)
	{
		list.push_back(rand() % 255);
	}

	MyList<TYPE> list2 = list + list;

	for (auto i : list2)
	{
		cout << i << "\t";
	}
	cout << endl;
}