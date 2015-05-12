#include "TLS.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;
//Build command.
//g++ -o test TLS.cpp -std=c++0x -lpthread
//g++ -o test TLS.cpp -std=c++0x -lpthread -m32
//Key Idea:
//用一個global 的key 去跟linux 要value, 而key會因為不同的thread而mapping到不一樣的value.
//這class能夠吃 sizeof < pointer的物件, 若 > pointer size , 請存pointer
//底下是驗證 不同thread 存取同一個key , 卻可以拿到不同的value
typedef void* (*ThreadProc)(void*);
ThreadLocal<long long> gTLS;
void thread(void*)
{
  int count = 0;
  gTLS.set(count);
  for(;;)
  {
    usleep(200000);
    printf("[%u] get = %llx\n", (unsigned int)pthread_self(), gTLS.get());
    gTLS.set(++count);
  }
}

int main()
{
  long long d = 0xabcdabcd00000000;
  gTLS.init();
   // cout<<sizeof(double);
   // cout<<sizeof(int);
   // cout<<sizeof(uintptr_t);
  gTLS.set(d);
  pthread_t id;
  int ret;
  ret=pthread_create(&id,NULL,(ThreadProc)thread,NULL);
  if(ret!=0){
    printf ("Create pthread error!\n");
    return 1;
  }
  for(;;)
  {
    sleep(1);
    printf("[%u] get = %llx\n", (unsigned int)pthread_self(), gTLS.get());
  }
  pthread_join(id, NULL);
  return 0;

}
