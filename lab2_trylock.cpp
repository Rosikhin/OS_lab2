// 9893, Росихин Александр, 
// Дисциплина ОС,
// Лабораторная работа №2.

/*
	trylock
*/

#include <iostream>
#include <pthread.h>
#include <unistd.h>


int flag1 = 0;
int flag2 = 0;

pthread_mutex_t mutex;

void* thread1(void* flag1)
{
  while (*((int*)flag1)==0 )
  {
  	int error = pthread_mutex_trylock(&mutex);
  	
  	if (error != EBUSY)
  	 for(int i=0; i<5; i++)
   	 {
  	  std::cout << "1";
	  usleep(1000);

  	}
  	else  std::cout << "Ресурс занят\n";
  	
  	pthread_mutex_unlock(&mutex);
  	usleep(1000);
  }
  return 0;
}

void* thread2(void* flag2)
{
  while (*((int*)flag2)==0 )
  {
  	int error = pthread_mutex_trylock(&mutex);
  	
  	if (error != EBUSY)
    	for(int i=0; i<5; i++)
   	{
  	 std::cout << "2";
	 usleep(1000);

  	} 
  	else  std::cout << "Ресурс занят\n";
  	
  	pthread_mutex_unlock(&mutex);
  	usleep(1000);
  }
  return 0;
}


int main()
{
 std::cout << "Росихин, 9893, ОС, Лаба 2.\n";
 pthread_t id1;
 pthread_t id2;

 pthread_mutex_init(&mutex, NULL);
 
 pthread_create(&id1, NULL, thread1, &flag1);
 pthread_create(&id2, NULL, thread2, &flag2); 
 
  std::cout << "Ждем нажатия\n";
  getchar();
 
  flag1 = 1;
  flag2 = 1;
  
  pthread_join(id1, NULL); 
  pthread_join(id2, NULL); 
  
  pthread_mutex_destroy(&mutex);
  
  std::cout << "\nЗавершение работы программы.\n";
 


}
