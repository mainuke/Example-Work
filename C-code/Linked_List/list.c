/*Manuel Iribarren UID 114751782 CMSC216 Project #7 Friday, October 18th, 2019

This program utilizes dynamically allocated memory to implement a
singley-linked-list data structure. The only dynamically allocated portions of
the list include every individual node EXCEPT FOR HEAD, the value of which will
be stored in the initialized calloc when init is called. These functions
manipulate said recursive structure -- all using dynamically allocated memory*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


/*The init function initializes its List structure parameter, creating an empty
linked list. In order for a List variable to be used in this program, this
function MUST be called first to create the underlying skeleton structure to
then be populated*/
void init(List *const list) {
  list->data = 0;
  list->next= NULL;
}

/*The append function inserts the integer parameter as a new element at the
very end of the linked list. The function will return 0 only if memory was
unable to be allocated for the element insertion and ifif the list parameter
is NULL*/
int append(List *const list, int new_value) {

  /*If the list parameter is NULL return 0*/
  if (list == NULL) {
    return 0;
  }
  /*Base case: if the list is empty, new_value becomes the new head*/
  if (list->data == 0 && list->next == NULL) {
    list->data= malloc(sizeof(int));
    *list->data= new_value; /*DANGER*/

    list->next= NULL;
    return 1;
  }

/*If list->next points to NULL, then the current parameter is the tail element*/
  if (list->next == NULL) {
    list->next= malloc(sizeof(List));
    list->next->data= malloc(sizeof(int));

/*If no memory can be allocated for the new element, then function returns 0*/
    if (list->next == NULL || list->next->data == NULL) {
      return 0;
    }
/*Sets tail as new_value*/
    *(list->next)->data= new_value;
    (list->next)->next= NULL;

    return 1;
  } else {
  /*If the next element is NOT NULL, then we have not yet reached the end of the
  list, therefore a recursive call to the next element occurs*/
    return append(list->next, new_value);
  }
}


/*The delete function removes the element corresponding to the integer parameter
from the list parameter. After freeing the memory allocated for said element,
the element previous to the deleted element will then point to the element that
comes after the deleted element. If the integer parameter does not denote a
valid index in the linked list parameter, the function will return 0 without
modifying anything*/
int delete(List *const list, unsigned int position) {
  List *temp_next= NULL;
  int *temp_data= 0;

/*Denotes an invalid index to delete or initial list parameter*/
  if (list == NULL || (list->data == 0 && list->next == NULL) ||
      position >= size(list)) {
    return 0;
  }
  /*Base case: if node marked for deletion IS the head/only node*/
  else if (position == 0 && size(list) >= 1) {

    /*If node to be deleted is the ONLY node left*/
    if (list->next == NULL) {

      free(list->data);
      list->data= 0;

      list->next= NULL;

      return 1;
    } else {
      /*if there are one or more nodes AFTER the head that is to be deleted */
      temp_data= list->next->data;

      /*Store the poiner to the element after the one to be deleted*/
      temp_next= list->next->next;

      free(list->data);
      free(list->next);

      list->data= temp_data;
    /*The head data value either becomes the next value in the list or NULL*/
/*makes new next pointer equal to the pointer of the element AFTER the deleted
  node or NULL if there was no proceeding node*/
      list->next= temp_next;
    }
    return 1;
  }

  /*If the function reaches the node directly preceding the one to be deleted*/
  else if (position == 1) {

    /*if the node marked for deletion is NOT the tail node*/
    if (list->next->next != NULL) {
      temp_data= list->next->next->data;
      temp_next= list->next->next->next;

      free(list->next->data);
      free(list->next->next);

      list->next->data= temp_data;
      list->next->next= temp_next;

    } else { /*If the node marked for deletion IS the tail*/
      free(list->next->data);
      list->next->data= 0;

      free(list->next);
      list->next= NULL;
    }

    return 1;
  }

  return delete(list->next, --position);
}


/*The find function queries the entirity of the list parameter until the first
occurance of the value parameter is found. IF found, the function returns the
first index of the first occurence of the value parameter. If the integer
parameter is NOT present in the list parameter, -1 will be returned. */
int find(List *const list, int value) {
  int count= 0;
  List *head= list, *curr= head;

  while (curr->next != NULL && *curr->data != value) {
    count++;
    curr= curr->next;
  }

  if (curr->next == NULL && *curr->data != value) {
    /*This assumes that the entire list was traversed without
    finding an occurance of the value parameter*/
    return -1;
  }

  return count;
}

/*The prepend function inserts the integer parameter as the HEAD (first)
element in the list parameter, pushing all the original elements to exist
AFTER this new head element. The function will return 0 only if memory was
unable to be allocated for the element insertion and ifif the list parameter
is NULL*/
int prepend(List *const list, int new_value) {
  List *head= list, *new_node= malloc(sizeof(List)), *temp_next= NULL;
  int *temp_data= 0;

  new_node->data= malloc(sizeof(int));

  /*0 Must be returned if memory cannot be allocated for the new element OR
  if the list parameter is NULL */
  if (new_node == NULL || new_node->data == NULL || list == NULL) {
    free(new_node->data);
    new_node->data= 0;

    free(new_node);
    new_node= NULL;

    return 0;
  }

  *new_node->data= new_value;

/*if the list is already empty, the new_value will become the sole element*/
  if (list->data == 0) {

    *list= *new_node;
    list->data= new_node->data;

    list->next= NULL;

    return 1;
  } else {
    /*If there is an existing head that must be PUSHED to follow the new node*/
    temp_next= head->next; /*store next pointer*/

    head->next= malloc(sizeof(new_node));
    temp_data= malloc(sizeof(int));

    *temp_data= *head->data;
    *head->data= *new_node->data;

    head->next->data= temp_data;
    head->next->next= temp_next;

    free(new_node->data);
    free(new_node);
  }

  return 1;
}

/*The print function will print all elements of the list parameter on the same
output line from beginning to end, with a single space separating each
pair of elements, followed by a new line character. If the list parameter
happens to be EMPTY, then the function will not print anything */
void print(List *const list) {

  /*Function will only print non-empty lists*/
  if (list->data != 0) {
    printf("%d", *list->data);

    if (list->next != NULL) {
      printf(" ");
    }
    /*If the current element is the tail, new line must be printed
    then the function ends*/
    if (list->next == NULL) {
      printf("\n");

      return;
    } else {
      print(list->next);
    }
  }
}

/*The size function returns the exact number of elements stored in the list
parameter, the returned value will always be 0 or greater*/
int size(List *const list) {
  int size= 0;
  List const*curr= list;

  while (curr != NULL && curr->data != 0) {
    size++;
    curr= curr->next;
  }

  return size;
}
