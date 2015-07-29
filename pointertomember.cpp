#include <iostream>
#include <cstdio>
#include <memory>
#include <functional>
#include <typeinfo>
using namespace std;
class Base
{
public:
  virtual void VirtualMemberFunction()
  {
    cout<<"I'm Base"<<endl;
  }
  virtual void VirtualConstMemberFunction() const
  {
    cout<<"I'm Base Const"<<endl;
  }
  virtual ~Base()
  {

  }
};
class Derived : public Base
{
public:
  virtual void VirtualMemberFunction() override
  {
    cout<<"I'm Derived"<<endl;
  }
  virtual void VirtualConstMemberFunction() const override
  {
    cout<<"I'm Derived Const"<<endl;
  }
};
int main(int argc, char const *argv[])
{
  Base* ptr = new Derived();
  auto func = &Base::VirtualMemberFunction;
  (ptr->*func)();

  const Base* ptr2 = new Derived();

   void (Base::*func2)() const = &Base::VirtualConstMemberFunction;

  (ptr2->*func2)();

  const shared_ptr<Base> spb = std::make_shared<Derived>();
  ((*spb).*func)();
  return 0;
}