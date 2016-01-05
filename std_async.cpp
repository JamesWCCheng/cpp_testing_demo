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
  // �]�b��Lthread���ε�get or wait�Q�I�s�N���]
  auto async = std::launch::async;
  // �]�b�I�sget or wait��thread
  auto deferred = std::launch::deferred;
  // �欰�ܩǲ�, 
  // g++, �欰��deferred �@��
  // VC �欰��async �@��
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
  // hreadProc  ��exception �L�|�����Acatch, �p�G�A�ܾa�_�hget()�Nrethrow~~
  getchar();
  return 0;
}
