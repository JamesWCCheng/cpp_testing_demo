#include <iostream>
#include <memory>
using namespace std;

class Foo
{
public :
  Foo()
  {
           cout<< "constructor this = " <<this<<endl;
            //throw 5566; //只有跳出異常才會跳到 operator delete(void * pMemory, int count)
  }
  Foo( int count )
  {
           cout<< count<<endl;
  }
   static void * operator new(std::size_t size, int count)
  {

    auto mem = malloc(size );
    cout<< "Foo::operator new = " <<mem<<endl;
    return mem;
  }
   static void operator delete(void * pMemory, int count)
  {
    cout<< pMemory<<" Foo::operator delete count = "<<count<<endl;
  }
   static void operator delete(void * pMemory)
  {
    cout<< "Foo::operator delete" <<endl;
  }
};

void * operator new (size_t size) throw (std::bad_alloc)
{
  cout<< "operator new" <<endl;
  return malloc(size );
}
class Bar
{
public :
  Bar()
  {
  }
};
int main()
{

  Bar *b = new Bar;
  Foo *f = NULL ;
  try{
    f = new(5566) Foo ;
  }
  catch(int qq)
  {
    cout<<"catch"<<endl;
  }
  if(f != NULL )
  {
    delete f;
  }
}