#include<iostream>

using std::cin;
using std::cout;
using std::endl;

class Tree
{
protected:

	class Element
	{
	public:
		int Data;
		Element* pLeft;
		Element* pRight;
		Element(int data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(data), pLeft(pLeft), pRight(pRight) {}
		bool isLeaf()const { return pLeft == pRight; }
	};

	Element* Root;

public:

	Tree() : Root(nullptr) {}
	Tree(const std::initializer_list<int> list) :Tree() {
		for (int i : list) 
			insert(i);
	}
	~Tree() { clear(); }

	int count()const { return _count(this->Root); }

	void insert(int data) {
		if (this->Root == nullptr) this->Root = new Element(data);
		else _insert(data, this->Root);
	}

	void erase(int data) {
		if (this->Root != nullptr)
			_erase(this->Root, data);
	}

	void clear() {
		_clear(this->Root);
		this->Root = nullptr;
	}

	void print()const {
		_print(this->Root);
	}

	int min()const {
		return _min(this->Root);
	}

	int max()const {
		return _max(this->Root);
	}

	int sum()const {
		return _sum(this->Root);
	}

	int avg()const {
		return _sum(this->Root) / count();
	}

	int depth()const {
		return _depth(this->Root);
	}
	

private:

	int _count(Element* Root)const
	{
		return !Root ? 0 : _count(Root->pLeft) + _count(Root->pRight) + 1;
	}

	void _insert(int data, Element* Root)
	{
		if (Root != nullptr) 
		{
			if (Root->Data > data) {
				if (Root->pLeft == nullptr) Root->pLeft = new Element(data);
				else _insert(data, Root->pLeft);
			}
			else {
				if (Root->pRight == nullptr) Root->pRight = new Element(data);
				else _insert(data, Root->pRight);
			}
		}
	}

	void _insert(Element* Root, Element* inputElement) 
	{
		if (!(Root == nullptr || inputElement == nullptr)) 
		{
			if (Root->Data > inputElement->Data) {
				if (Root->pLeft == nullptr) Root->pLeft = inputElement;
				else(_insert(Root->pLeft, inputElement));
			}
			else
			{
				if (Root->pRight == nullptr) Root->pRight = inputElement;
				else _insert(Root->pRight, inputElement);
			}
		}
	}

	void _erase(Element* Root, int data) 
	{
		if (Root->Data == data) 
		{
			if (_count(Root->pLeft) > _count(Root->pRight)) 
			{
				_insert(Root->pLeft, Root->pRight);
				this->Root = Root->pLeft;
			}
			else 
			{
				_insert(Root->pRight, Root->pLeft);
				this->Root = Root->pRight;
			}
			delete Root;
		}
		else
		{
			Element* buf = Root;
			while (Root != nullptr && Root->Data != data)
			{
				buf = Root;
				Root->Data > data ? Root = Root->pLeft : Root = Root->pRight;
			}

			if (Root != nullptr)
			{
				buf->pLeft == Root ? buf->pLeft = nullptr : buf->pRight = nullptr;
				_insert(this->Root, Root->pLeft);
				_insert(this->Root, Root->pRight);
				delete Root;
			}
		}
	}

	void _clear(Element* Root) 
	{
		if (Root != nullptr) 
		{
			_clear(Root->pLeft);
			_clear(Root->pRight);
			delete Root;
		}
	}

	void _print(Element* Root)const 
	{
		if (Root != nullptr)
		{
			_print(Root->pLeft);
			cout << Root->Data << "\t";
			_print(Root->pRight);
		}
	}

	int _min(Element* Root)const 
	{
		if (Root->pLeft == nullptr) return Root->Data;
		_min(Root->pLeft);
	}

	int _max(Element* Root)const 
	{
		if (Root->pRight == nullptr) return Root->Data;
		_max(Root->pRight);
	}

	int _sum(Element* Root)const 
	{
		if (Root == nullptr) return 0;
		return Root->Data + _sum(Root->pLeft) + _sum(Root->pRight);
	}

	int _depth(Element* Root)const 
	{
		if (Root == nullptr) return 0;
		int l = _depth(Root->pLeft) + 1;
		int r = _depth(Root->pRight) + 1;
		return l > r ? l : r;
	}
};

//#define RANDOM_VALUE
#define CHECK_ERASE

void main()
{
#ifdef RANDOM_VALUE
	srand(NULL);

	Tree tree;
	int n; cin >> n;
	for (size_t i = 0; i < n; i++)
	{
		tree.insert(rand());
	}
	tree.print();
	cout << "\nDepth " << tree.depth() << endl;
	cout << "Min and Max: " << tree.min() << "\t" << tree.max() << endl;
	cout << "Sum and Avg: " << tree.sum() << "\t" << tree.avg() << endl;
#endif // RANDOM_VALUE

#ifdef CHECK_ERASE
	Tree tree2 = { 50, 25, 75, 12, 37, 62, 87 };
	tree2.erase(25);
	tree2.print();
#endif // CHECK_ERASE


}