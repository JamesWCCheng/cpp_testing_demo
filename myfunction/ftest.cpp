#include "function.h"
#include <iostream>
using namespace std;

void Bar(){std::cout<<"Bar"<<std::endl;}
struct Foo
{
  void operator()()
  {std::cout<<"void functor"<<std::endl;}

  void MemberFunction(){std::cout<<"member function"<<std::endl;}
};

class XDD
{
public: XDD(const XDD& rhs){cout<<"XDD"<<endl;} XDD(){}
  XDD(XDD&& rhs){cout<<"move"<<endl;}
};
void XD(XDD xdd)
{
  std::cout<<"XD"<<std::endl;
}
typedef void(*FPTR)(XDD);
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

  //member function
  Function<void(void)> mfp(&foo,&Foo::MemberFunction);
  mfp();

  //function pointer
  XDD xdd;
  FPTR fptr = &XD;
  cout<<"===+"<<endl;
  Function<void(XDD)> fp = fptr;
  cout<<"===-"<<endl;
  fp(xdd);
  return 0;
}