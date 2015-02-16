#include <memory>
#include <cstdio>

using std::shared_ptr;
using std::weak_ptr;

class A;
class B;

class A
{
public:
	~A() { printf("A destructor\n"); }
	shared_ptr<B> ptr;
};

class B
{
public:
	~B() { printf("B destructor\n"); }
	//shared_ptr<A> ptr;
	weak_ptr<A> ptr;
};

int main(void)
{
	{
		shared_ptr<A> a(new A());
		shared_ptr<B> b(new B());
		a->ptr = b;
		b->ptr = a;

		printf("A use count = %ld\n", a.use_count());
		printf("B use count = %ld\n", b.use_count());
	}
	printf("End of main()\n");
	return 0;
}
