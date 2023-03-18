#include <omp.h>
#include <stdio.h>
#include <math.h>

#define power1 3
#define power2 6

void task1(void);
void task2(void);

int main(void)
{
  #pragma omp parallel num_threads(2)
  {
    #pragma omp sections
    {
      #pragma omp section
      task1();
      #pragma omp section
      task2();
    }
  }
  
}

void task1() {
  for (int i = 0; i < pow(10, 3); i++) {
    printf("thread::%d | i::%d\n", omp_get_thread_num(), i);
  }
}

void task2() {
  for (int o = 1; o < 100; o++) {
    int p = pow(o, power1);
    printf("thread::%d | (o**pow)::%d\n", omp_get_thread_num(), p);
  }
}
