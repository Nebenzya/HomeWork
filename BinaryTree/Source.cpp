#include<iostream>

using std::cin;
using std::cout;
using std::endl;

class Tree
{
private:

	class Element
	{
	public:
		int Data;
		Element* pLeft;
		Element* pRight;
		Element(int data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(data), pLeft(pLeft), pRight(pRight) {}
	};

	Element* Root;
	unsigned int _count;

public:

	Tree() : Root(nullptr), _count(0) {}
	~Tree() { clear(); }

	unsigned int count() const { return _count; }

	void insert(int data) {
		if (this->Root == nullptr) this->Root = _add(data);
		else _insert(data, this->Root);
	}

	void erase(int data) {
		if (this->Root == nullptr) return;
		_erase(this->Root, data);
	}

	void clear() {
		_clear(this->Root);
		this->Root = nullptr;
		_count = 0;
	}

	void print()const {
		_print(this->Root);
		cout << "\nCount = " << _count << endl;
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
		return _sum(this->Root) / _count;
	}

	int depth()const {
		return _depth(this->Root);
	}
	

private:

	Element* _add(int data) {
		_count++;
		return new Element(data);
	}

	void _insert(int data, Element* Root)
	{
		if (Root == nullptr) return;
		if (Root->Data > data) {
			if (Root->pLeft == nullptr) Root->pLeft = _add(data);
			else _insert(data, Root->pLeft);
		}
		else {
			if (Root->pRight == nullptr) Root->pRight = _add(data);
			else _insert(data, Root->pRight);
		}
	}

	void _insert(Element* Root, Element* Move) {
		if (Root == nullptr || Move == nullptr)return;
		if (Root->Data > Move->Data) {
			if (Root->pLeft == nullptr) Root->pLeft = Move;
			else(_insert(Root->pLeft, Move));
		}
		else
		{
			if (Root->pRight == nullptr) Root->pRight = Move;
			else _insert(Root->pRight, Move);
		}
	}

	void _erase(Element* Root, int data) {

		Element* buf = Root;
		bool isLeft = false;

		if (Root->Data == data) 
		{
			_insert(Root->pLeft, Root->pRight);
			this->Root = Root->pLeft;
			delete buf;
			_count--;
		}
		else
		{
			while (Root != nullptr && Root->Data != data)
			{
				buf = Root;
				if (Root->Data > data) {
					Root = Root->pLeft;
					isLeft = true;
				}
				else {
					Root = Root->pRight;
					isLeft = false;
				}
			}

			if (Root != nullptr)
			{
				isLeft ? buf->pLeft = nullptr : buf->pRight = nullptr;
				_insert(this->Root, Root->pLeft);
				_insert(this->Root, Root->pRight);
				delete Root;
				_count--;
			}
		}

		
	}

	void _clear(Element* Root) {
		if (Root == nullptr) return;
		_clear(Root->pLeft);
		_clear(Root->pRight);
		delete Root;
	}

	void _print(Element* Root)const {
		if (Root == nullptr)return;
		_print(Root->pLeft);
		cout << Root->Data << "\t";
		_print(Root->pRight);
	}

	int _min(Element* Root)const {
		if (Root->pLeft == nullptr) return Root->Data;
		_min(Root->pLeft);
	}

	int _max(Element* Root)const {
		if (Root->pRight == nullptr) return Root->Data;
		_max(Root->pRight);
	}

	int _sum(Element* Root)const {
		if (Root == nullptr) return 0;
		return Root->Data + _sum(Root->pLeft) + _sum(Root->pRight);
	}

	int _depth(Element* Root)const {
		if (Root == nullptr) return 0;
		int l = _depth(Root->pLeft) + 1;
		int r = _depth(Root->pRight) + 1;
		return l > r ? l : r;
	}
};

void main()
{
	srand(NULL);

	Tree tree;
	for (size_t i = 0; i < 15; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << "Depth" << tree.depth() << endl;

	cout << tree.min() << "\t" << tree.max() << endl;
	cout << tree.sum() << "\t" << tree.avg() << endl;

	tree.erase(38);
	tree.print();
	cout << "Depth" << tree.depth() << endl;

}