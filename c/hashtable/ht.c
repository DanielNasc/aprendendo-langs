#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

/*
 * I learned this here: https://youtu.be/YyWMN_0g3BQ?list=PLdsnXVqbHDUcrE56CH8sXaPF3TTqoBP2z
*/

#define MAX_LEN 100

struct Node {
  char *key;
  char *value;
  struct Node *next;
};

struct HashTable {
  struct Node *table[MAX_LEN];
};  

// Prototypes
void insertNode(struct HashTable *hashTable, char *key, char *value);
char *searchValue(struct HashTable *hashTable, char *key);
struct Node* createNode(char *key, char *value);
uint8_t hashKey(char *key);
void printHashTable(struct HashTable *hashTable);

int main()
{
  struct HashTable *hashTable = malloc(sizeof(struct HashTable));

  printf("Inserting values into hash table...\n");

  for (int i = 0; i < 50; i++)
  {
    // key = "key${i}"
    char *key = malloc(sizeof(char) * (strlen("key") + 1 + 1));
    strcpy(key, "key");
    key[3] = '0' + i;
    key[4] = '\0';
    
    // value = "value${i}"
    char *value = malloc(sizeof(char) * (strlen("value") + 1 + 1));
    strcpy(value, "value");
    value[5] = 'a' + i;
    value[6] = '\0';

    insertNode(hashTable, key, value);
  }

  int choice;
  printf("\n\n1. Print hash table\n2. Search for value\n");
  scanf("%d", &choice);

  if (choice == 1)
  {
    printHashTable(hashTable);
  }
  else if (choice == 2)
  {
    char *key = malloc(sizeof(char) * (strlen("key") + 1 + 1)); 
    printf("Enter key: ");
    scanf("%s", key);

    char *value = searchValue(hashTable, key);
    if (value) printf("Value: %s\n", value);
    else printf("Key not found\n");
  }

  return 0;
}

// Using djb2 hash function:
// Mutiply by 33 and add the ascii value of the current character
uint8_t hashKey(char *key)
{
  unsigned long hash = 5381;
  unsigned int c;

  /*
   * hash << 5 "shifts" the hash value 5 bits to the left, multiplying the value by 32 (2^5).
   * then + hash adds another value of hash, turning this into multiplying by 33.
   * https://theartincode.stanis.me/008-djb2/
  */
  while ((c = *key++))
    hash = ((hash << 5) + hash) + c; /* hash ''* 33 + c */

  return hash % MAX_LEN;
}

struct Node*
createNode(char *key, char *value)
{
  struct Node *node = malloc(sizeof(struct Node));
  node->key = key;
  node->value = value;
  node->next = NULL;
  return node;
}

void insertNode(struct HashTable *hashTable, 
                char *key, 
                char *value)
{
  uint8_t hash = hashKey(key);
  struct Node *node = hashTable->table[hash];

  // If the position is empty, insert the node
  if (node == NULL) {
    hashTable->table[hash] = createNode(key, value);
  }
  // else, iterate through the linked list until the end, then insert the node
  else {
    while (node->next != NULL) {
      node = node->next;
    }
    node->next = createNode(key, value);
  }
}


char *searchValue(struct HashTable *hashTable, char *key)
{
  uint8_t hash = hashKey(key);
  struct Node *node = hashTable->table[hash];

  if (node == NULL){
    return NULL;
  }
  else {
    while (node) {
      if (strcmp(node->key, key) == 0) {
        return node->value;
      }
      node = node->next;
    }
    return NULL;
  }
}

void printHashTable(struct HashTable *hashTable)
{
  printf("\nHash table:\n");
  for (int i = 0; i < MAX_LEN; i++)
  {
    struct Node *node = hashTable->table[i];
    if (!node) continue;
    printf("Index: %d\n", i);
    while(node)
    {
      printf("\tKey: %s, Value: %s\n", node->key, node->value);
      node = node->next;
    }
  }
}
