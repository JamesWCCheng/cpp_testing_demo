#include <iostream>
#include <tuple>
#include <Windows.h>
#include <mutex>
using namespace std;

template<class Type, Type...>
struct Sequence {
};

template<class /*Sequence Type*/, class /*Sequence<...>*/, int /*END*/>
struct Append;

template<class Type, Type... BEGIN, Type END>
struct Append<Type, Sequence<Type, BEGIN...>, END> {
  typedef Sequence<Type, BEGIN..., END> result;
};

template<int BEGIN, int END, bool = (END >= BEGIN)> struct MakeIntegerSequenceImpl;

template<int BEGIN, int END>
struct MakeIntegerSequenceImpl<BEGIN, END, false> {
  typedef Sequence<int> result;
};

template<int BEGIN, int END>
struct MakeIntegerSequenceImpl<BEGIN, END, true> {
  typedef typename Append<int, typename MakeIntegerSequenceImpl<BEGIN, END - 1>::result, END>::result result;
};

template<int BEGIN>
struct MakeIntegerSequenceImpl<BEGIN, BEGIN, true> {
  typedef Sequence<int, BEGIN> result;
};

template<int BEGIN, int END>
struct MakeIntegerSequence {
  typedef typename MakeIntegerSequenceImpl<BEGIN, END>::result result;
};

template<class Func, class... Args>
class ThreadData
{
public:
  ThreadData(Func func, std::tuple<Args...> data)
    : mUserFunc(std::move(func)), mThreadData(std::move(data))
  {
    
  }

  template<int... N>
  DWORD RunInternal(Sequence<int, N...>&&)
  {
    mUserFunc(std::get<N>(mThreadData)...);
    return 0;
  }
  static DWORD WINAPI Run(LPVOID obj)
  {
    // 
    ThreadData* threadData = static_cast<ThreadData*>(obj);
    // threadData->mUserFunc(std::get<0>(threadData->mThreadData));
    //threadData->mUserFunc(std::get<0.....N-1>(threadData->mThreadData)...);
    //auto result = threadData->RunInternal(Sequence<0>());
    auto result = threadData->RunInternal(typename MakeIntegerSequence<0, sizeof...(Args)-1>::result());
    delete threadData;
    return result;
  }
  

private:
  Func mUserFunc;
  std::tuple<Args...> mThreadData;
};
class Thread
{
public:
  template<class Func, class... Args>
  Thread(Func&& func, Args&&... args)
  {
    ThreadData<Func, Args...> *data = new ThreadData<Func, Args...>(std::forward<Func>(func), std::make_tuple(std::forward<Args>(args)...));
    
    mThreadHandle = CreateThread(
      NULL, 0,
      ThreadData<Func, Args...>::Run, data,
      0, NULL
      );

  }
  void Join()
  {
    WaitForSingleObject(mThreadHandle, INFINITE);
  }
  ~Thread()
  {
    CloseHandle(mThreadHandle);
  }
private:
  HANDLE mThreadHandle;
};

std::mutex gMutex;
void ThreadProc(int num)
{
  std::lock_guard<std::mutex> lock(gMutex);
  cout << num << endl;
}

void ThreadProc2(int num, double num2)
{
  std::lock_guard<std::mutex> lock(gMutex);
  cout << num << "," << num2 <<endl;
}
void ThreadProc3()
{
  std::lock_guard<std::mutex> lock(gMutex);
  cout << "No param" << endl;
}
int main()
{
  Thread thread(ThreadProc, 123);

  Thread thread2(ThreadProc2, 5566, 77.88);

  Thread thread3(ThreadProc3);

  thread.Join();
  thread2.Join();
  thread3.Join();
  return 0;
}