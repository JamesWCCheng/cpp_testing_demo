
#ifndef TLS_h
#define TLS_h

#include <pthread.h>
#include <signal.h>
#include <iostream>
#include <stdint.h>
using namespace std;
typedef sig_atomic_t sig_safe_t;

template<typename T>
class ThreadLocal
{
  typedef pthread_key_t key_t;

  // Integral types narrower than void* must be extended to avoid
  // warnings from valgrind on some platforms.  This helper type
  // achieves that without penalizing the common case of ThreadLocals
  // instantiated using a pointer type.
  template<typename S>
  struct Helper
  {
    typedef uintptr_t Type;
  };

  template<typename S>
  struct Helper<S *>
  {
    typedef S *Type;
  };

public:
  inline bool init();

  inline T get() const;

  inline void set(const T aValue);

  bool initialized() const { return mInited; }

private:
  key_t mKey;
  bool mInited;
};

template<typename T>
inline bool
ThreadLocal<T>::init()
{

  mInited = !pthread_key_create(&mKey, nullptr);

  cout<<"mInited = "<<mInited<<endl;
  return mInited;
}

template<typename T>
inline T
ThreadLocal<T>::get() const
{
  void* h;

  h = pthread_getspecific(mKey);

  return static_cast<T>(reinterpret_cast<typename Helper<T>::Type>(h));
}

template<typename T>
inline void
ThreadLocal<T>::set(const T aValue)
{
  //MOZ_ASSERT(initialized());
  void* h = reinterpret_cast<void*>(static_cast<typename Helper<T>::Type>(aValue));

  bool succeeded = !pthread_setspecific(mKey, h);

  if (!succeeded) {
    cout<<"gg"<<endl;
  }
}


#endif
