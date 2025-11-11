#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct node {
    int data;
    struct node* next;
};

struct node* hashTable[SIZE];

int hash(int key) {
    return key % SIZE;
}

void insert(int key) {
    int index = hash(key);
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

int search(int key) {
    int index = hash(key);
    struct node* temp = hashTable[index];
    while (temp != NULL) {
        if (temp->data == key)
            return 1;
        temp = temp->next;
    }
    return 0;
}

void deleteKey(int key) {
    int index = hash(key);
    struct node *temp = hashTable[index], *prev = NULL;

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) return;

    if (prev == NULL)
        hashTable[index] = temp->next;
    else
        prev->next = temp->next;
    
    free(temp);
}

void display() {
    for(int i = 0; i < SIZE; i++) {
        printf("%d -> ", i);
        struct node* temp = hashTable[i];
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, key;

    while(1) {
        printf("\n1.Insert\n2.Search\n3.Delete\n4.Display\n5.Exit\n");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                scanf("%d", &key);
                if (search(key)) printf("Found\n");
                else printf("Not Found\n");
                break;
            case 3:
                scanf("%d", &key);
                deleteKey(key);
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
        }
    }
    return 0;
}
