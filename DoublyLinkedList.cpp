#include <iostream>
using namespace std;

class Element
{
private:
	int data;
	Element *prev;
	Element *next;
public:
	Element(int d, Element *next = nullptr, Element *prev= nullptr)
	{
		this->data = d;
		this->next = next;
		this->prev = prev;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class List;
};

class List
{
private:
	Element *head;
	Element *tail;
	int size;
public:
	List();
	List(int num);
	List(initializer_list <int> il);
	List(List &source);
	List(List &&source);
	~List();
	void operator=(List &source);
	void operator=(List &&source);
	List operator+(List &source);
	void pushFront(int data);
	void pushBack(int data);
	void popFront();
	void popBack();
	void insert(int pos, int data);
	void remove(int pos);
	void printReverse();
	void concat(List &source);
	void clear();
};

List::List()
{
	head = tail = nullptr;
	size = 0;
}
List::List(int num)
{
	for (int i = 0; i < num; i++)
		pushBack(0);
	size = num;
}
List::List(initializer_list <int> il)
{
	for (const int *it = il.begin(); it != il.end(); it++)
	{
		pushBack(*it);
	}
}
List::List(List &source) :List()
{
	concat(source);
}
List::List(List &&source) : List()
{
	head = source.head;
	tail = source.tail;
	source.head = source.tail = nullptr;
}
List::~List()
{
	for (int i = 0; i < size; i++)
		popFront();
}
void List::operator=(List &source)
{
	clear();
	concat(source);
}
void List::operator=(List &&source)
{
	head = source.head;
	tail = source.tail;
	source.head = source.tail = nullptr;
}
List List::operator+(List &source)
{
	concat(source);
	return *this;
}
void List::pushFront(int data)
{
	Element *New = new Element(data);
	if (size == 0)
	{
		head = tail = New;
	}
	else
	{
		New->next = head;
		head->prev = New;
		head = New;
	}
	size++;
}
void List::pushBack(int data)
{
	Element *New = new Element(data);
	if (size == 0)
	{
		head = tail = New;
	}
	else
	{
		tail->next = New;
		New->prev = tail;
		tail = New;
	}
	size++;
}
void List::popFront()
{
	if (size >1)
	{
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
		size--;
	}
	else
	{
		delete head;
		head = tail = nullptr;
		size = 0;
	}
	
}
void List::popBack()
{
	if (size>1)
	{
	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;
	size--;
}
	else
	{
		delete head;
		head = tail = nullptr;
		size = 0;
	}

}
void List::printReverse()
{
	cout << endl;
	int index = size;
	for (Element *it = tail; it != nullptr; it = it->prev)
	{
		cout << index<<"\t"<<it->data << endl;
		index--;
	}
	cout << endl;
}
void List::insert(int pos, int data)
{
	Element *ptr;
	if (pos <= size / 2)
	{
		ptr = head;
		for (int i = 1; i < pos; i++)
		{
			ptr = ptr->next;
		}
	}
	else
	{
		ptr = tail;
		for (int i = size; i > pos; i--)
		{
			ptr = ptr->prev;
		}
	}
	ptr->prev = ptr->prev->next = new Element(data, ptr, ptr->prev);
	size++;

}
void List::remove(int pos)
{
	Element *ptr;
	if (pos <= size / 2)
	{
		ptr = head;
		for (int i = 1; i < pos; i++)
		{
			ptr = ptr->next;
		}
	}
	else
	{
		ptr = tail;
		for (int i = size - 1; i > pos; i--)
		{
			ptr = ptr->prev;
		}
	}
	ptr->prev->next = ptr->next;
	ptr->next->prev = ptr->prev;
	delete ptr;
	size--;
}
void List::concat(List &source)
{
	if (source.head != nullptr)
	{
		Element *sourceit = source.head;
		while (sourceit != nullptr)
		{
			pushBack(sourceit->data);
			sourceit = sourceit->next;
		}
	}
}
void List::clear()
{
	while (head!=nullptr)
		popFront();
}

void main()
{
	List A = {1,2,3,4,5};
	A.printReverse();
	List B=2;
	B = A;
	B.printReverse();
	List C = A + B;
	C.printReverse();
} 
