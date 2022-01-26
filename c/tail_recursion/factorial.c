#include <stdio.h>

int bad_factorial(int n, int prints[], int firstValue);
int good_factorial(int n, int accumulator);

int main()
{
  int prints[5];
  for (int i = 0; i < 5; i++)
    prints[i] = -1;


  printf("Testing bad factorial\n");
  int bf = bad_factorial(5, prints, 5);
  printf("Result: %d\n", bf);

  printf("\nTesting good factorial\n");
  int gf = good_factorial(5, 1);
  printf("Result: %d\n", gf);
  return 0;
}

// BAD:
// This function uses a lot of memory.

int bad_factorial(int n, int prints[], int firstValue)
{
  if (n == 1)
    return 1;
  else {
    prints[firstValue - n] = n;
    printf("Memory: ");
    for (int i = 0; prints[i] != -1; i++)
      printf(" %d *", prints[i]);
    printf(" factorial(%d)\n", n - 1);
    return n * bad_factorial(n - 1, prints, firstValue);
  }
}

// GOOD (using tail recursion):
// This function uses less memory. :)

int good_factorial(int n, int accumulator)
{
  if (n == 1)
    return accumulator;
  else
  {
    printf("Memory: %d * factorial(%d)\n", accumulator * n, n - 1);
    return good_factorial(n - 1, accumulator * n);
  }
}
