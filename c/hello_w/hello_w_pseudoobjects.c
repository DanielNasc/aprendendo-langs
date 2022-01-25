#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define Class struct

Class Person {
  char *name;
  uint8_t age;
  uint8_t height;
  void  (*printSelf)(Class Person *person);
};

void printPerson(Class Person *person)
{
  printf("Name: %s\n", person->name);
  printf("Age: %d\n", person->age);
  printf("Height: %d\n", person->height);
}

Class Person * newPerson(
    char name[],
    uint8_t age,
    uint8_t height)
{
    Class Person *self = (Class Person *)malloc(sizeof(Class Person));
    self->name = name;
    self->age = age;
    self->height = height;
    self->printSelf = &printPerson;

    return self;
}

int main()
{
    Class Person *person = newPerson("John", 20, 180);
    person->printSelf(person);
    return 0;
}