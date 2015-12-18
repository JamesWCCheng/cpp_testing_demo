#include <iostream>
#include <sstream>
#include <string>

using namespace std;
template<class Arg>
string ToString(const char* func, int line, const char* varname, const Arg& arg)
{
  ostringstream ss;
  ss << "[" << func << "](" << line << ") :" << varname << " = " << arg << endl;
  return ss.str().c_str();
}
#define _(X) ToString(__func__,__LINE__,#X,X)

class EZLogger
{
public:

  template<class T>
  EZLogger& operator<<(T&& other)
  {
    cout << other;
    return *this;
  }
  EZLogger& operator<<(ostream& (*func)(ostream&))//for std::endl
  {
    cout << func;
    return *this;
  }
};
EZLogger ez;
class Foo
{
public:
  Foo() { x = 123; y = 5566; z = 7788; }
  int x;
  int y;
  friend ostream& operator<<(ostream& o, const Foo& f);
private:
  int z;

};
ostream& operator<<(ostream& o, const Foo& f)
{
  o << f.x << f.y << f.z << endl;
  return o;
}

int main()
{
  int qq = 123;
  Foo foo;
  ez << _(qq) << _(foo) << endl << "@@@@";

}
