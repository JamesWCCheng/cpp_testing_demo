#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <class Type1, class Type2>
void XD(Type1 t1, Type2 t2)
{

}
template <class Type1, class Type2, class Type3>
void XD(Type1 t1, Type2 t2, Type3 t3)
{

}
template<class... Args>
class Variadic
{
public:
  Variadic(Args... args)
  {
    XD(args...);
  }
};

template <class T>
class Fooo
{

};
template <template <class... TT> class T>
class Bar{
public:
  Bar() : vec(1,2)
  {

  }
  T<int, int> vec;
};


template <class T>
class Fooo2
{

};

template <class T>
class Bar2{
  T vec;
};

int main()
{
  Bar<Variadic> bar;
  Bar2<Fooo2<int>> bar2;
  //bar.f(vec);
  return 0;
}