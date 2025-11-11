#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

// ------------ OPEN HASHING (CHAINING) ------------
struct node {
    int data;
    struct node* next;
};
struct node* chain[SIZE];

void initChain() {
    for(int i=0;i<SIZE;i++) chain[i] = NULL;
}

int hash(int key) {
    return key % SIZE;
}

void insertChain(int key) {
    int i = hash(key);
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = key;
    newNode->next = chain[i];
    chain[i] = newNode;
}

void displayChain() {
    printf("\nOpen Hashing (Chaining):\n");
    for(int i=0;i<SIZE;i++) {
        printf("%d -> ", i);
        struct node* temp = chain[i];
        while(temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// ------------ CLOSED HASHING ARRAYS ------------
int linear[SIZE], quadratic[SIZE], dbl[SIZE];

void initClosed(int arr[]) {
    for(int i=0;i<SIZE;i++) arr[i] = -1;
}

// ------------ LINEAR PROBING ------------
void insertLinear(int key) {
    int i = hash(key);
    while(linear[i] != -1) i = (i + 1) % SIZE;
    linear[i] = key;
}

// ------------ QUADRATIC PROBING ------------
void insertQuadratic(int key) {
    int i = hash(key), j = 1;
    while(quadratic[i] != -1) {
        i = (i + j*j) % SIZE;
        j++;
    }
    quadratic[i] = key;
}

// ------------ DOUBLE HASHING ------------
int h1(int key){ return key % SIZE; }
int h2(int key){ return 7 - (key % 7); }

void insertDouble(int key) {
    int i = h1(key), step = h2(key);
    while(dbl[i] != -1)
        i = (i + step) % SIZE;
    dbl[i] = key;
}

void displayArray(int arr[], char* msg) {
    printf("\n%s:\n", msg);
    for(int i=0;i<SIZE;i++)
        printf("%d -> %d\n", i, arr[i]);
}

// ------------ MAIN MENU ------------
int main() {
    int ch, key;

    initChain();
    initClosed(linear);
    initClosed(quadratic);
    initClosed(dbl);

    while(1) {
        printf("\n--- HASHING MENU ---\n");
        printf("1. Insert (Open Hashing / Chaining)\n");
        printf("2. Insert (Linear Probing)\n");
        printf("3. Insert (Quadratic Probing)\n");
        printf("4. Insert (Double Hashing)\n");
        printf("5. Display All\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        if(ch == 6) break;

        if(ch >= 1 && ch <= 4) {
            printf("Enter key: ");
            scanf("%d", &key);
        }

        switch(ch) {
            case 1: insertChain(key); break;
            case 2: insertLinear(key); break;
            case 3: insertQuadratic(key); break;
            case 4: insertDouble(key); break;

            case 5:
                displayChain();
                displayArray(linear, "Linear Probing");
                displayArray(quadratic, "Quadratic Probing");
                displayArray(dbl, "Double Hashing");
                break;
        }
    }
    return 0;
}
