/* (c) Larry Herman,  Manuel Iribarren 2019.  You are allowed to use this code yourself, but
   not to provide it to anyone else. */

typedef struct list {
  int *data;
  struct list *next;
}List;

void init(List *const list);
int append(List *const list, int new_value);
int prepend(List *const list, int new_value);
int size(List *const list);
int find(List *const list, int value);
int delete(List *const list, unsigned int position);
void print(List *const list);
