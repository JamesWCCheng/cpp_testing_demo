#include <iostream>
#include <utility>  //std::forward
#include <memory> //std::shared_ptr
using namespace std;

template<class C, class T, class... Args>
struct Proxy
{
  shared_ptr<C> _objC;
  typedef T(C::*funcptr_t)(Args...);
  funcptr_t _fp;

  Proxy(shared_ptr<C> objC, funcptr_t fp) : _objC(objC), _fp(fp) {}

  template<class... ActualArgs>
  T operator()(ActualArgs&&... args)
  {
    return ((*_objC).*_fp)(std::forward<ActualArgs>(args)...);
  }
};

template<class C, class T, class... Args>
Proxy<C, T, Args...> operator ->* (shared_ptr<C> c, T(C::*fp)(Args...))
{
  return Proxy<C, T, Args...>(c, fp);
}
class Bar
{
public:
  Bar(){}
  Bar(Bar && b){ cout << "move" << endl; }
  Bar(const Bar& b){ cout << "copy" << endl; }
};

struct Clazz
{
  int v;

  Clazz(int x) : v(x) {}

  int foo(int w) { return v + w; }
  int bar(int x, int y) { return v * x + y; }
  void qux(Bar b) {  }
};

int main(void)
{
  shared_ptr<Clazz> pObj(new Clazz(42));


  auto fp3 = &Clazz::qux;

  Bar b;

  (pObj->*fp3)(b);

  return 0;
}
