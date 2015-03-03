/*
g++ -g -o test pthread.cpp -lpthread
*/
#include <stdio.h>
#include <pthread.h>

#include <unistd.h>
void thread(void*)
{
  int i;
  for(i=0;i<3;i++) {
    sleep(3);
    printf("This is a pthread.\n");
  }
}
typedef void* (*ThreadProc)(void*);
int main(void)
{
  pthread_t id;
  int i,ret;
  ret=pthread_create(&id,NULL,(ThreadProc) thread,NULL);
  if(ret!=0){
    printf ("Create pthread error!\n");
    return 1;
  }
  pthread_join(id, NULL);
  return (0);
}
