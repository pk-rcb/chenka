#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct node {
    int data;
    struct node* next;
};

struct node* hashTable[SIZE];
int collisionCount = 0;

int hash(int key) {
    return key % SIZE;
}

void insert(int key) {
    int index = hash(key);
    struct node* temp = hashTable[index];

    while (temp != NULL) {
        if (temp->data == key) {
            printf("⚠️  Key %d already exists. Duplicate not inserted.\n", key);
            return;
        }
        temp = temp->next;
    }

    if (hashTable[index] != NULL)
        collisionCount++;

    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = key;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;

    printf("✅ Key %d inserted successfully.\n", key);
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

    if (temp == NULL) {
        printf("❌ Key %d not found.\n", key);
        return;
    }

    if (prev == NULL)
        hashTable[index] = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("🗑️  Key %d deleted successfully.\n", key);
}

void display() {
    printf("\n====== Hash Table ======\n");
    for (int i = 0; i < SIZE; i++) {
        printf("[%2d] -> ", i);
        struct node* temp = hashTable[i];
        if (!temp)
            printf("NULL");
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("========================\n");
    printf("Total Collisions: %d\n", collisionCount);
}

void freeTable() {
    for (int i = 0; i < SIZE; i++) {
        struct node* temp = hashTable[i];
        while (temp != NULL) {
            struct node* del = temp;
            temp = temp->next;
            free(del);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    int choice, key;

    for (int i = 0; i < SIZE; i++)
        hashTable[i] = NULL;

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(key)) printf("✅ Key %d found.\n", key);
                else printf("❌ Key %d not found.\n", key);
                break;
            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(key);
                break;
            case 4:
                display();
                break;
            case 5:
                freeTable();
                printf("👋 Exiting... All memory freed.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
