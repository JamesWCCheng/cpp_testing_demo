#include "function.h"
#include <iostream>
using namespace std;

void XD(){std::cout<<"XD"<<std::endl;}
struct Foo
{
  Foo() {
  }

  Foo(const Foo &ref) {
  std::cout << "copy " << &ref << std::endl;
  }

  Foo(Foo &&ref) {
  std::cout << "move " << &ref << std::endl;
  }

  void operator()()
  {std::cout<<"void functor"<<std::endl;}

  void MemberFunction(){std::cout<<"member function"<<std::endl;}
};

typedef void(*FPTR)();
int main()
{
  Foo foo;
  //lambda
  Function<void(Foo)> f = [] (Foo arg) {
  std::cout << "arg " << &arg << std::endl;
  };
  f(foo);
  //std bind
  Function<void()> ff = std::bind([] (Foo arg) {
  std::cout << "arg " << &arg << std::endl;
  }, foo);
  ff();
  //Functor
  Function<void(void)> v = Foo();
  v();
  //function pointer
  FPTR fptr = &XD;
  Function<void(void)> fp = fptr;

  //member function
  Function<void(void)> mfp(&foo,&Foo::MemberFunction);
  mfp();

  return 0;
}