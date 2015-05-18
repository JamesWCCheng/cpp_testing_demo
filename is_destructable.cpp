//true, if class has public constructor.

#include <iostream>
#include <memory>
#include <type_traits>
using namespace std;
#define OVERRIDE(func, ...) \
void func() __VA_ARGS__ {}


class Base
{
public:
  virtual ~Base()
  {
    cout<<"~Base"<<endl;
  }
  virtual void ORZ(){}

};
class Derived :public Base
{
public:
  static void Release(void* _ptr)
  {
     Derived* ptr = static_cast<Derived*>(_ptr);
     delete ptr;
  }
  OVERRIDE(ORZ, override);
protected:
  ~Derived(){}
};
template<typename T, T Value>
struct IntegralConstant
{
  static const T value = Value;
  typedef T ValueType;
  typedef IntegralConstant<T, Value> Type;
};

/** Convenient aliases. */
typedef IntegralConstant<bool, true> TrueType;
typedef IntegralConstant<bool, false> FalseType;
struct IsDestructibleFallbackImpl
{
  template<typename T> static T&& Declval();

  template<typename T, typename = decltype(Declval<T>().~T())>
  static TrueType Test(int);

  template<typename>
  static FalseType Test(...);

  template<typename T>
  struct Selector
  {
    typedef decltype(Test<T>(0)) type;
  };
};

template<typename T>
struct IsDestructibleFallback
  : IsDestructibleFallbackImpl::Selector<T>::type
{
};
int main()
{
  cout<<std::is_destructible<Derived>::value << std::endl;
  cout<<IsDestructibleFallback<Derived>::value<< std::endl;
  // shared_ptr<Derived> sp(new Derived());
  // Base *ptr = sp.get();
  // //delete ptr;
  // Derived::Release(ptr);
  //delete ptr;
  return 0;

}