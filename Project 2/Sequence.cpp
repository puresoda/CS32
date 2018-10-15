#include "Sequence.h"
#include <iostream>

Sequence::Sequence()
	:head(nullptr)
{

}

Sequence::~Sequence()
{
	Node* temp = head;

	while (temp != nullptr)
	{
		Node* del = temp;
		temp = temp->next;
		delete del;
	}
}

Sequence::Sequence(const Sequence& other)
	:head(nullptr)
{
	Node* othertemp = other.head;

	for (int pos = 0; othertemp != nullptr; othertemp = othertemp->next, pos++) //insert othertemp's data at pos
		insert(pos, othertemp->data);
}

Sequence& Sequence::operator=(const Sequence& other)
{
	if (this != &other) // check aliasing
	{
		Sequence temp(other);
		swap(temp);
	}
	
	return *this;
}

bool Sequence::empty() const
{
	if (head != nullptr) //empty if head doesn't point to anything
		return false;

	return true;
}

int Sequence::size() const
{
	Node* temp = head;
	int count = 0;

	//loop through entire Sequence until we hit nullptr
	while (temp != nullptr) 
	{
		temp = temp->next;
		count++;
	}

	return count;
}

bool Sequence::insert(int pos, const ItemType& value)
{
	//filter out bad input
	if (pos > size() || pos < 0)
		return false;

	else if (pos == 0) // insert at the beginning
	{
		Node* temp = new Node;
		temp->data = value;
		temp->prev = nullptr;
		temp->next = head;
		head = temp;

		if (size() > 1) //consider special case where list was originally empty
			temp->next->prev = temp;
	}

	else
	{
		Node* temp = head;
		int count = 0;

		while (temp->next != nullptr && count != pos) // get Node at specified position
		{
			count++;
			temp = temp->next;
		}

		Node* in = new Node;
		in->data = value; //insert data into new Node


		//insert in the middle
		if (pos != size())
		{
			in->prev = temp->prev; // new Node's previous should point to temp's prev
			in->next = temp; //New node is inserted before temp

			temp->prev->next = in; // previous Node's next should point to new Node
			temp->prev = in; //temp's previous should point to new Node
		}

		//insert at end
		else
		{
			in->prev = temp;
			in->next = temp->next;
			temp->next = in;
		}
	}

	return true;
}

int Sequence::insert(const ItemType& value)

{
	Node* temp = head;
	int count = 0;

	while (temp != nullptr && value > temp->data) //update position
	{
		temp = temp->next;
		count++;
	}


	if (!insert(count, value)) // if we are unable to insert for some reason
		return -1;
	else
		return count;
}

bool Sequence::erase(int pos)
{
	int size1 = size();

	//can't erase empty Sequence
	if (size1 <= 0 || pos >= size1)
		return false;

	int count = 0;
	Node* temp = head;

	while (temp != nullptr && count != pos)
	{
		temp = temp->next;
		count++;
	}

	//remove first Node
	if (pos == 0)
	{
		head = temp->next;

		//if Sequence was not empty
		if (temp->next != nullptr)
			temp->next->prev = nullptr;
	}

	//remove last Node
	else if (pos == size1 -1)
		temp->prev->next = nullptr;

	//remove middle Nodes
	else
	{
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}

	delete temp;

	return true;
	
}

int Sequence::remove(const ItemType& value)
{
	int count = 0;

	while (find(value) != -1) //loop until we are unable to find an instance of value
	{
		erase(find(value));
		count++;
	}

	return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
	//filter out bad inputs
	if (pos >= size() || pos < 0)
		return false;

	int count = 0;
	Node* temp = head;

	while (temp->next != nullptr && count != pos)
	{
		temp = temp->next;
		count++;
	}

	value = temp->data;

	return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
	//filter out bad input
	if (pos >= size() || pos < 0)
		return false;

	int count = 0;
	Node* temp = head;

	while (temp->next != nullptr && count != pos)
	{
		temp = temp->next;
		count++;
	}

	temp->data = value;

	return true;
}

int Sequence::find(const ItemType& value) const
{
	Node* temp = head;
	int pos = 0;

	// loop through linked list
	while (temp != nullptr && temp->data != value)
	{
		temp = temp->next;
		pos++;
	}
		
	//reached the end of the linked list without finding the value
	if (temp == nullptr)
		return -1;

	else
		return pos;

}

void Sequence::swap(Sequence& other)
{
	Node* temp = head;
	head = other.head;
	other.head = temp;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	int size2 = seq2.size();
	int size1 = seq1.size();

	if (size1 < size2 || size2 <= 0)
		return -1;

	Sequence temp(seq1);

	int pos;
	int count =0;
	ItemType val;
	ItemType val2;

	//find first instance of seq2's first value
	seq2.get(0, val);
	pos = temp.find(val);

	for (int i = 0; pos != -1 && i < size2; i++)
	{
		//values should match as loop moves one by one
		seq2.get(i, val);
		temp.get(pos + i, val2);

		//subsequence is not found
		if (val2 != val)
		{
			temp.erase(pos); //erase the value so we can move on to next instance
			i = 0; //reset i 
			seq2.get(i, val); 
			pos = temp.find(val); // get next instance
			count++; //since we decrease temp's size, we must account for this when we return
		}
	}

	if (pos == -1) // if subsequence was not found, no need to adjust pos
		count = 0;

	return (pos+count);
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	ItemType val;
	Sequence temp;
	int size1 = seq1.size();
	int size2 = seq2.size();

	if (size1 >= size2)
	{
		temp =seq1; //copy seq2 into temp

		for (int i = 0; i < size2; i++) //insert seq2 values at every odd position
		{
			seq2.get(i, val);
			temp.insert(2 * i + 1, val);
		}
	}

	else
	{
		temp = seq2;

		for (int i = 0; i < size1; i++) //insert seq1 values at every even point 
		{
			seq1.get(i, val);
			temp.insert(2 * i, val);
		}
	}

	result.swap(temp);
}

void Sequence::dump() const
{
	if (size() > 0)
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			std::cerr << temp->data << " ";
			temp = temp->next;
		}

		temp = head;

		while (temp->next != nullptr)
		{
			temp = temp->next;
		}

		std::cerr << std::endl;

		while (temp != nullptr)
		{
			std::cerr << temp->data << " ";
			temp = temp->prev;
		}

		std::cerr << std::endl;
	}
}