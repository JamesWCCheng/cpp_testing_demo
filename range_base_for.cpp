#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <cstdio>
#include <memory>
#include <wchar.h>
using namespace std;
const wchar_t* utf16 = L"\u597D\u597D";
#include <stdio.h>
#include <pthread.h>

#include <unistd.h>

#include <iostream>
 
using namespace std;
 
// forward-declaration to allow use in Iter
class IntVector;
 
class Iter
{
    public:
    Iter (const IntVector* p_vec, int pos)
        : _pos( pos )
        , _p_vec( p_vec )
    { }
 
    // these three methods form the basis of an iterator for use with
    // a range-based for loop
    bool
    operator!= (const Iter& other) const
    {
        return _pos != other._pos;
    }
 
    // this method must be defined after the definition of IntVector
    // since it needs to use it
    int operator* () const;
 
    Iter& operator++ ()
    {
      cout<<"Iter& operator++ "<<endl;
        ++_pos;
        // although not strictly necessary for a range-based for loop
        // following the normal convention of returning a value from
        // operator++ is a good idea.
        return *this;
    }
 
    private:
    int _pos;
    const IntVector *_p_vec;
};
 
class IntVector
{
    public:
    IntVector () : _data({0})
    {
    }
 
    int get (int col) const
    {
      cout<<"get"<<endl;
        return _data[ col ];
    }
    Iter begin () const
    {
      cout<<"begin"<<endl;
        return Iter( this, 0 );
    }
 
    Iter end () const
    {
      cout<<"end"<<endl;
        return Iter( this, 100 );
    }
 
    void set (int index, int val)
    {
      cout<<"set"<<endl;
        _data[ index ] = val;
    }
 
    private:
   int _data[ 100 ];
};
 
int
Iter::operator* () const
{
        cout<<"operator *    "<<endl;
     return _p_vec->get( _pos );
}
 #define LOGX(args...)                                            \
    printf(args)
// sample usage of the range-based for loop on IntVector
int main()
{
  LOGX("orz %d", 123);
    IntVector v;
    // for ( int i = 0; i < 100; i++ )
    // {
    //     v.set( i , i );
    // }
    for ( int i : v ) { cout << i << endl; }
}