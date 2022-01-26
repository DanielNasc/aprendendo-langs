#include <stdio.h>

long bad_fibonacci(long n);
long good_fibonacci(long n, long pair[]);

int main()
{
  long  n,
        pair[] = {0, 1};

  printf("Enter a number:\n");
  printf("Max number supported is 46, after that it will overflow.\n");
  scanf("%ld", &n);

  printf("\nTail recursion\n");
  printf("fib(%d) = %d\n", n, good_fibonacci(n, pair));

  printf("\nBad recursion\n");
  printf("You will need to be patient...\n");
  printf("fib(%ld) = %d\n", n, bad_fibonacci(n));

  return 0;
}

// BAD:

long bad_fibonacci(long n)
{
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else
    return bad_fibonacci(n - 1) + bad_fibonacci(n - 2);
}

// GOOD:
// fib (n, (a, b))
// after -> fib (n - 1, (b, a + b))
// ...
// if (n == 0) return a
// if (n == 1) return b

long good_fibonacci(long n, long pair[])
{
  if (n == 0)
    return pair[0];
  else if (n == 1)
    return pair[1];
  else
  {
    long temp = pair[0];
    pair[0] = pair[1];
    pair[1] = temp + pair[1];
    return good_fibonacci(n - 1, pair);
  }
}
