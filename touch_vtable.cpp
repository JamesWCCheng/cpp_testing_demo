#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
class BB{
public:
	//virtual ~BB(){}
};
class Bar
{
public:
	virtual void XD()
	{
		cout << this << "Bar XD" << endl;
	}
};
class Foo : public Bar, public BB
{
public:
	virtual void XD(BB* gg)
	{
		if (this == gg)// gg will shift 4 bytes =  this + 4, but still compared equal.
		{
			cout << this << "Foo XD" << gg << endl;
		}

	}
};

class Foo2 : public Bar
{
public:
	virtual void XD() override
	{
		cout << this << "Foo XD" << endl;
	}
};

class SharePtr
{
public:
	SharePtr(Foo2 * ptr)
		:rawptr(ptr)
	{
	}
	Foo2* rawptr;
};
void QQ(){}
typedef void(*fptr)();
int main()
{

	/*Foo *ptr = new Foo();
	cout << ptr<<endl;
	((fptr)*(reinterpret_cast<void***>(ptr)[0]))();*/
	
	Foo2 *ptr = new Foo2();
	SharePtr sp = ptr;
	((fptr)*(reinterpret_cast<void****>(&sp)[0][0]))(); 



	return 0;
}