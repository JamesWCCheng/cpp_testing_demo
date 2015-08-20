//g++ -g promise.cpp --std=c++11 -pthread
// promise example
#include <iostream>
#include <functional>
#include <thread>
#include <future>
#include <chrono>
void compute(std::promise<int>& prom) {

  std::this_thread::sleep_for(std::chrono::seconds(3));
  prom.set_value (10);                         // fulfill promise
}

int main ()
{
  std::promise<int> prom;                      // create promise

  std::future<int> fut = prom.get_future();    // engagement with future

  std::thread th1 (compute, std::ref(prom));  // send future to new thread

  std::cout<< "wait for value" <<std::endl;
  int x = fut.get();
  std::cout<<"answer = "<<x<<std::endl;
  th1.join();
  return 0;
}