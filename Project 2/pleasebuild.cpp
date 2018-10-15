/*
#include "Sequence.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
	//Test cases used with data item "ItemType" set to the type std::string

	Sequence a; //defult constructor

	Sequence b(a); //copy constructor

	assert(b.empty()); //empty method for an empty sequence

	assert(b.insert("Hello") == 0); //insert method
	assert(!b.insert(2, "Nope")); //inserting out of range
	assert(a.empty());

	a = b; //assignment operator
	assert(!a.empty() && a.size() == 1);

	ItemType temp;
	assert(!a.get(1, temp) && temp == ""); //unsuccessful get method
	assert(a.get(0, temp) && temp == "Hello"); // get method

	assert(!b.erase(1) && !b.empty()); //unsuccessful erase method
	assert(b.erase(0) && b.empty()); //erase method

	assert(b.remove("Hello") == 0 && a.remove("Hello") == 1); //remove method

	assert(a.insert("b") == 0); //inserting in order
	assert(a.insert("c") == 1);
	assert(a.insert("a") == 0);

	assert(a.set(1, "D")); //set method
	assert(!a.set(3, "NO"));

	assert(a.find("b") == -1); //find method
	assert(a.find("c") == 2);
	assert(b.find("a") == -1);

	a.swap(b); //swap method
	assert(a.empty() && b.size() == 3);
	assert(a.insert(0, "Start"));
	a.swap(b);
	assert(a.size() == 3 && b.size() == 1);
	assert(b.get(0, temp) && temp == "Start");

	Sequence c(a); //subsequence method
	Sequence empty;
	assert(subsequence(a, c) == 0);
	assert(subsequence(a, b) == -1);
	b.set(0, "D");
	assert(subsequence(a, b) == 1);
	assert(subsequence(a, empty) == -1);

	Sequence d; //interleave method
	Sequence e;
	interleave(a, b, d);
	assert(d.find("a") == 0);
	assert(d.find("D") == 1);
	assert(d.get(2, temp) && temp == "D");
	assert(d.find("c") == 3);
	assert(d.size() == 4 && !d.get(4, temp) && temp == "D");
	interleave(a, b, c);
	assert(c.find("a") == 0);
	assert(c.find("D") == 1);
	assert(c.get(2, temp) && temp == "D");
	assert(c.find("c") == 3);
	assert(c.size() == 4 && !c.get(4, temp) && temp == "D");
	interleave(a, b, a);
	assert(a.find("a") == 0);
	assert(a.find("D") == 1);
	assert(a.get(2, temp) && temp == "D");
	assert(a.find("c") == 3);
	assert(a.size() == 4 && !a.get(4, temp) && temp == "D");
	interleave(a, a, e);
	assert(e.find("a") == 0);
	assert(e.find("D") == 2);
	assert(e.find("c") == 6);
	assert(e.get(1, temp) && temp == "a");
	assert(e.get(3, temp) && temp == "D");
	assert(e.get(4, temp) && temp == "D");
	assert(e.get(5, temp) && temp == "D");
	assert(e.get(7, temp) && temp == "c");
	assert(e.size() == 8 && !e.get(8, temp) && temp == "c");
	interleave(a, a, a);
	assert(a.find("a") == 0);
	assert(a.find("D") == 2);
	assert(a.find("c") == 6);
	assert(a.get(1, temp) && temp == "a");
	assert(a.get(3, temp) && temp == "D");
	assert(a.get(4, temp) && temp == "D");
	assert(a.get(5, temp) && temp == "D");
	assert(a.get(7, temp) && temp == "c");
	assert(a.size() == 8 && !a.get(8, temp) && temp == "c");

	std::cerr << std::endl << "All Cases passed!" << std::endl;
	return 0;
}
/**/

/*
#include "Sequence.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
Sequence a;
a.insert(0, 1);
a.insert(1, 2);
a.insert(2, 2);
a.insert(3, 3);
a.insert(4, 4);
Sequence b;
b.insert(0, 2);
b.insert(1, 3);
std::cerr << "Sequence A:" << std::endl;
a.dump();
std::cerr << "Sequence B:" << std::endl;
b.dump();
assert(subsequence(a, b) == 2);
Sequence c;
interleave(a, b, c);
std::cerr << "Sequence C:" << std::endl;
c.dump();


std::cerr << "All cases passed! :)" << std::endl;
return 0;
}
/**/

/*
#include "Sequence.h"
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Sequence>::value,
"Sequence must be default-constructible.");
static_assert(std::is_copy_constructible<Sequence>::value,
"Sequence must be copy-constructible.");

void thisFunctionWillNeverBeCalled()
{
CHECKTYPE(&Sequence::operator=, Sequence& (Sequence::*)(const Sequence&));
CHECKTYPE(&Sequence::empty, bool (Sequence::*)() const);
CHECKTYPE(&Sequence::size, int  (Sequence::*)() const);
CHECKTYPE(&Sequence::insert, bool (Sequence::*)(int, const ItemType&));
CHECKTYPE(&Sequence::insert, int (Sequence::*)(const ItemType&));
CHECKTYPE(&Sequence::erase, bool (Sequence::*)(int));
CHECKTYPE(&Sequence::remove, int  (Sequence::*)(const ItemType&));
CHECKTYPE(&Sequence::get, bool (Sequence::*)(int, ItemType&) const);
CHECKTYPE(&Sequence::set, bool (Sequence::*)(int, const ItemType&));
CHECKTYPE(&Sequence::find, int  (Sequence::*)(const ItemType&) const);
CHECKTYPE(&Sequence::swap, void (Sequence::*)(Sequence&));
CHECKTYPE(subsequence, int(*)(const Sequence&, const Sequence&));
CHECKTYPE(interleave, void(*)(const Sequence&, const Sequence&, Sequence&));
}

int main()
{}
/**/

/*
#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
Sequence s;
assert(s.insert(0, "lavash"));
s.dump();
assert(s.insert(0, "tortilla"));
assert(s.size() == 2);
s.dump();
ItemType x = "injera";
assert(s.get(0, x) && x == "tortilla");
assert(s.get(1, x) && x == "lavash");
}

int main()
{
test();
cout << "Passed all tests" << endl;
}
/**/

/*
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
Sequence s;
assert(s.insert(0, 10));
assert(s.insert(0, 20));
assert(s.size() == 2);
ItemType x = 999;
assert(s.get(0, x)  &&  x == 20);
assert(s.get(1, x)  &&  x == 10);
}

int main()
{
test();
cout << "Passed all tests" << endl;
}
/**/

/*
#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
ItemType val;
Sequence s;
assert(s.size() == 0);
assert(s.find(1) == -1);
Sequence c(s);

Sequence t;
t.insert(1);
t.insert(2);
t.insert(3);
t.dump();
assert(t.size() == 3);
assert(t.get(0, val));
assert(val == 1);
assert(t.get(1, val));
assert(val == 2);
assert(t.get(2, val));
assert(val == 3);
assert(!t.get(4, val));
assert(val == 3);
assert(t.set(0, val));
assert(t.get(0, val));
assert(val == 3);
assert(!t.set(4, val));
assert(t.insert(4) == 3);
assert(t.size() == 4);
assert(t.get(3, val));
assert(val == 4);
assert(t.erase(3));
assert(!t.get(3, val));
assert(t.size() == 3);
assert(t.insert(3) == 0);
assert(t.remove(3) == 3);
assert(t.size() == 1);
assert(t.find(3) == -1);

t.dump();
}
/**/


#include "Sequence.h"
#include <iostream>
#include <cassert>

int main()
{
ItemType val; //store get()

Sequence s;
s.insert("1");
s.insert("2");
s.insert("3");

Sequence t;
t.insert("1");
t.insert("2");
t.insert("3");
t.insert(3,"1");
t.insert("5");

std::cout << subsequence(t, s);

std::cerr << "All tests passed!" << std::endl;
}
/**/