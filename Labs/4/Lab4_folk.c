#include <stdio.h>

#define SIZE 10
#define EMPTY -1

struct stack {    
    char items[SIZE];
    int top;
};
    
void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, int value);
int empty(struct stack* stackPtr);
int pop(struct stack* stackPtr);
int top(struct stack* stackPtr);


void display(struct stack* stackPtr);



int main() {
    int i;
    struct stack stack1;    
    struct stack stack2;       
    initialize(&stack1);    
    initialize(&stack2);    
    int ele;   
    int ch;    
     while(1)    {        
        printf("\nMenu:\n 1: Stack 1 push\n 2: Stack 2 Push\n 3: Stack 1 Pop\n 4: Stack 2 Pop\n 5: Stack 1 display\n 6: Stack 2 Display\n 7: Exit\nEnter your choice:");        
        scanf("%d",&ch);        
        if(ch==7) {            
            printf("<<EXIT>>");            
             break;        
         }        
        else if (ch==1){            
            printf("Enter an element to PUSH in the stack1: ");            
            scanf("%d",&ele);            
            push(&stack1, ele);            
            display(&stack1);
        }       
        else if (ch==2) {            
            printf("Enter an element to PUSH in the stack2: ");            
            scanf("%d",&ele);            
            push(&stack2, ele);           
            display(&stack2);        
        }        
        else if (ch==3)  {            
            ele = pop(&stack1);            
            if(ele!=0 )  {                
                printf(" ITEM POPPED from Stack 1: %d ",ele);                
                display(&stack1);            
            }        
        }        
        else if (ch==4)  {            
            ele = pop(&stack2);            
            if(ele!=0 )   {                
                printf(" ITEM POPPED from Stack 2: %d ",ele);                
                display(&stack2);            
            }        
        }        
        else if(ch==5) {            
            display(&stack1);       
        }        
        else if(ch==6)  {            
            display(&stack2);        
        }    
    }    
    return 0;
}


void initialize(struct stack* stackPtr) {     
    stackPtr->top = -1;  
}

int push(struct stack* stackPtr, int value) {    
    if (full(stackPtr))        
    return 0;    
    stackPtr->items[stackPtr->top+1] = value;    
    (stackPtr->top)++;    
    return 1;
    }
    int full(struct stack* stackPtr) {
    return (stackPtr->top == SIZE - 1);
    }
    int empty(struct stack* stackPtr) {    
        return (stackPtr->top == -1);
    }
        
int pop(struct stack* stackPtr) {    
    int retval;    
    if (empty(stackPtr))       
    return EMPTY;    
    retval = stackPtr->items[stackPtr->top];    
    (stackPtr->top)--;    
    return retval;
}
        
int top(struct stack* stackPtr) {    
    if (empty(stackPtr))        
    return EMPTY;    
    return stackPtr->items[stackPtr->top];
}
            
void display(struct stack* stackPtr) {    
    printf("\nPrinting the Current stack...");    
    for(int i=0; i<=stackPtr->top; i++)        
    printf("%d ", stackPtr->items[i]);
}