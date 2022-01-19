#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;

node * insert(node *root, int data);
void print_tree(node *root);

int main()
{

  node *root = NULL;
  int array[] = {10, 5, 15, 2, 7, 12, 17, 1, 3, 6, 8, 11, 13, 16, 18};

  for (int i = 0; i < sizeof(array)/sizeof(int); i++) {
    printf("Inserting %d\n", array[i]);
    root = insert(root, array[i]);
  }

  printf("\nTree:\n");
  print_tree(root);
  printf("\n");

  return 0;
}

node * insert(node *root, int data)
{
  node * tmp = (node *)malloc(sizeof(node));
  tmp->data = data;
  tmp->left = NULL;
  tmp->right = NULL;

  if (!root)
    return tmp;

  node *curr = root;
  node *parent = NULL;

  while(1)
  {
    parent = curr;
    if (data < curr->data)
    {
      curr = curr->left;

      if (!curr)
      {
        parent->left = tmp;
        return root;
      }
    }
    else
    {
      curr = curr->right;

      if (!curr)
      {
        parent->right = tmp;
        return root;
      }
    }
  }
}

void print_tree(node *root)
{
  if (!root) return;

  print_tree(root->left);
  printf("%d ", root->data);
  print_tree(root->right);
}
