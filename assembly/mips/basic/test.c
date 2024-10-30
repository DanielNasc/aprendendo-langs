#include <stdio.h>

int main (int argc, char *argv[])
{
  double pei = 0x000000003fe00000;
  printf("%f\n", pei);
  int j = 3;
  for (int i = 0; i < j; i++) {
    printf("%d %d\n", i, j);
    j++;
  }
  return 0;
}
