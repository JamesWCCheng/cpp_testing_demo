#include "TLS.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;
//g++ -o test TLS.cpp -std=c++0x -lpthread
//g++ -o test TLS.cpp -std=c++0x -lpthread -m32
typedef void* (*ThreadProc)(void*);
ThreadLocal<long long> gTLS;
void thread(void*)
{
  for(;;)
  {
    usleep(200000);
    printf("[%u] get = %llx\n", (unsigned int)pthread_self(), gTLS.get());

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
  int i,ret;
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