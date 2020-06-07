/* COP 3502C Assignment 2
This program is written by: Joanna Folk */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct customer {
    char name[9];
    int item_count;
    int line_num;
    long entering_time;
} customer;

typedef struct node {
    struct customer *customer;
    struct node *next;
} node;

typedef struct cqueue {
    struct node *first;
    struct node *last;
} cqueue;

customer *peek(cqueue *queue) {
    if (queue->first != NULL) {
        customer *cust = queue->first->customer;
        return cust;
    }
    return NULL;
}

int empty(cqueue *queue) {
    if (queue->first == NULL) {
        return 1;
    } else {
        return 0;
    };
}

void enqueue(cqueue *queue, customer *cust) {
    struct node *node = (struct node *) malloc(sizeof(struct node));
    node->customer = cust;
    node->next = NULL;
    // If there is no element in list set first and last
    if (empty(queue)) {
        queue->first = node;
        queue->last = node;
    } else {
        queue->last->next = node;
        queue->last = node;
    };
}

customer *dequeue(cqueue *cqueue) {
    customer *dequeueCustomer;
    dequeueCustomer = cqueue->first->customer;
    node *dequeueNode;
    dequeueNode = cqueue->first;
    cqueue->first = cqueue->first->next;
    // Free memory for dequeued node
    if (cqueue->first == NULL) {
        cqueue->last = NULL;
    }
    free(dequeueNode);
    return dequeueCustomer;
}

customer *findNextCustomer(cqueue lines[], long *currentTime) {
    int nextFound = 0;
    int time = *currentTime;
    *currentTime = 100;
    customer *nextCustomer = NULL;
    // Peek at all lines and check if arrivalTime < currentTime
    // if so pick the costumer with the least items first
    // if the item count is the same pick lower line number
    while (nextFound == 0) {

        for (int i = 0; i < 12; i++) {
            if (empty(&lines[i])) {
                continue;
            }
            customer *peekedCustomer = peek(&lines[i]);
            if (peekedCustomer->entering_time > time) {
                continue;
            } else if (nextCustomer == NULL) {
                nextCustomer = peekedCustomer;
            } else if (nextCustomer->item_count > peekedCustomer->item_count) {
                nextCustomer = peekedCustomer;
            } else if (nextCustomer->item_count == peekedCustomer->item_count) {
                if (nextCustomer->line_num > peekedCustomer->line_num) {
                    nextCustomer = peekedCustomer;
                }
            };
        }
        if (nextCustomer == NULL) {
            time++;
        } else {
            nextFound = 1;
        }

    }
    *currentTime = time;
    return nextCustomer;
}

int main() {
    FILE *IN, *OUT;
    const int numberLines = 12;
    int num_cases;

    struct cqueue lines[numberLines];
    IN = fopen("in.txt", "r");
    if (IN == NULL) {
        printf("No in.txt File!");
        return 1;
    }

    OUT = fopen("out.txt", "w+");
    int first, second;
    fscanf(IN, "%d", &num_cases);
    for (int i = 0; i < num_cases; i++) {
        // Empty Lines Array to have empty lines for each test case   
        memset(lines, 0, sizeof(struct cqueue) * numberLines);
        long currentTime = 0;
        long numCustomers;
        fscanf(IN, "%ld", &numCustomers);
        for (long i = 0; i < numCustomers; i++) {
            customer *cust = (customer *) malloc(sizeof(customer));
            // Read costumer
            fscanf(IN, "%ld %d %8s %d", &cust->entering_time, &cust->line_num, &cust->name[0], &cust->item_count);
            enqueue(&lines[cust->line_num - 1], cust);
        }
        // For number of customer in case find next and process
        for (long c = 0; c < numCustomers; c++) {
            customer *nextCustomer = findNextCustomer(lines, &currentTime);
            dequeue(&lines[nextCustomer->line_num - 1]);
            // Calculate the time customer checks out
            currentTime = currentTime + (30 + nextCustomer->item_count * 5);
            fprintf(OUT, "%s from line %d checks out at time %ld.", nextCustomer->name, nextCustomer->line_num,
                    currentTime);
            if (c == numCustomers - 1 && i == num_cases - 1) {
                // Don't add new line after last line written.
            } else {
                fprintf(OUT, "\n");
            }
            free(nextCustomer);
        }
    }
    return 0;
}