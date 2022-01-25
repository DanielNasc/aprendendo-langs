#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct {
  char *name;
  uint8_t age;
  uint8_t height;
} Person;

void createPerson(char name[], 
    uint8_t age, 
    uint8_t height,
    void(*callback)(Person *person))
{
  Person *person = (Person *)malloc(sizeof(Person));
  person->name = name;
  person->age = age;
  person->height = height;
  callback(person);
}

void printPerson(Person *person)
{
  printf("Name: %s\n", person->name);
  printf("Age: %d\n", person->age);
  printf("Height: %d\n", person->height);
}

int main()
{
  createPerson("John", 20, 180, &printPerson);
  return 0;
}
