#include <stdio.h>

struct node{
     int data;
     struct node* next;
};

// 1. adds n to data of each node

void addN(struct node* list, int n){

     struct node* temp = list;
     while (temp != NULL) {

          temp->data = temp->data + n;
          temp = temp->next;
     }
}

// 2. deletes first node in the list and returns the address of

// second node as the head of the list

struct node* deleteFirst(struct node* list){

     if (list == NULL)
          return NULL;

     struct node* temp = list;
     list = temp->next;
     free(temp);

     return list;
}

// 3. copies the given list into a new list and returns the

// address of the new list

struct node* copy(struct node* list){

     struct node* temp = list;
     struct node* newList = NULL;
     struct node* newNode = NULL;
     struct node* prev = NULL;

     while (temp != NULL){

          newNode = malloc(sizeof(struct node));
          newNode->data = temp->data;
          newNode->next = NULL;

          if (newList == NULL){
              newList = newNode;
          }

          else{
              prev->next = newNode;
          }

          prev = newNode;
          temp = temp->next;
     }
     return newList;
}

// 5. returns 1, if the given list is in sorted order

// return 0, otherwise

int isSorted(struct node* list){

     struct node* temp = list;

     while (temp->next != NULL){

          if (temp->data > temp->next->data)
              return 0;
          temp = temp->next;
     }
     return 1;
}

// 6. inserts the given value at a given place in the list

// if the place value is greater than the number of nodes

// in the list, the value is inserted at the end of the list

void insertToPlace(struct node* list, int val, int place){

     int curPos = 1;
     struct node* newValue = malloc(sizeof(struct node));
     newValue->data = val;
     newValue->next = NULL;
     struct node* curNode = list;
     while ((curPos + 1) < place && curNode->next != NULL){
          curNode = curNode->next;
          curPos++;
     }

     if (curNode->next == NULL){

          curNode->next = newValue;
     }

     else if ((curPos + 1) == place){

          newValue->next = curNode->next;
          curNode->next = newValue;
     }
}

// 7. inserts a value 2 in the list, after each node that has value 4

void list_42(struct node* list{

     struct node* newNode2 = NULL;
     struct node* curNode = list;
     while (curNode != NULL){

          if (curNode->data == 4){

              newNode2 = malloc(sizeof(struct node));
              newNode2->data = 2;
              newNode2->next = curNode->next;
              curNode->next = newNode2;
              curNode = newNode2->next;
          }
          else
              curNode = curNode->next;
     }
}

// 8. moves the front element to end of the list

// and returns the pointer to second node as

// the head of the list

struct node* moveFrontToBack(struct node* alpha){

     struct node* first = alpha;
     struct node* second = alpha->next;
     struct node* temp = second;
     while (temp->next != NULL)
          temp = temp->next;

     first->next = NULL;
     temp->next = first;

     return second;

}

// prints the linked list

void print(struct node* list){

     struct node* temp = list;
     while (temp != NULL){

          printf("%d->", temp->data);
          temp = temp->next;
     
     printf("NULL");
}

int main(){

     struct node* head = malloc(sizeof(struct node));
     head->data = 1;
     struct node* node0 = malloc(sizeof(struct node));
     head->next = node0;
     node0->data = 2;
     struct node* node1 = malloc(sizeof(struct node));
     node0->next = node1;
     node1->data = 3;
     node1->next = NULL;
     print(head);
     printf("\nTest isSorted: \n");
     printf("%d\n", isSorted(head));
     printf("Test addN: \n");
     addN(head, 2);
     print(head);
     printf("\nTest copy: \n");
     struct node* newlst = copy(head);
     print(newlst);
     printf("\nTest insertToPlace: \n");
     insertToPlace(head, 10, 3);
     print(head);
     printf("\nTest list_42: \n");
     list_42(head);
     print(head);
     printf("\nTest moveFrontToBack: \n");
     head = moveFrontToBack(head);
     print(head);
     printf("\nTest deleteFirst: \n");
     head = deleteFirst(head);
     print(head);
     printf("\n");
     return 0;
}