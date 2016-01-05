/* g++ -std=c++11 std_async.cpp -lpthread */
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
using namespace std;
thread_local int tls = 0;
int Task(int a, int b)
{
  cout << "tls = " << tls << endl;
  tls++;
  std::thread::id this_id = std::this_thread::get_id();
  cout << "Task ++ ID= " << this_id << " a = " << a << ", b = " << b << endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  cout << "Task --" << endl;
  throw a;
  cout << "throw?" << endl;
  return b;
}
int main()
{
  std::thread::id this_id = std::this_thread::get_id();
  cout << "Main thread id = " << this_id << endl;
  // 跑在其他thread不用等get or wait被呼叫就先跑
  auto async = std::launch::async;
  // 跑在呼叫get or wait的thread
  auto deferred = std::launch::deferred;
  // 行為很怪異, 
  // g++, 行為跟deferred 一樣
  // VC 行為跟async 一樣
  auto async_deferred = std::launch::async | std::launch::deferred;
  auto fut = std::async(async,
    Task, 1, 7788);
  fut.wait();
  fut = std::async(deferred,
    Task, 2, 5566);
  try
  {
    cout << fut.get();
  }
  catch (int err)
  {
    cout << "catch = " << err << endl;
  }
  fut = std::async(async_deferred,
    Task, 3, 1234);
  try
  {
    cout << fut.get();
  }
  catch (int err)
  {
    cout << "catch = " << err << endl;
  }
  // hreadProc  有exception 他會先幫你catch, 如果你很靠北去get()就rethrow~~
  getchar();
  return 0;
}
