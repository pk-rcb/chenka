#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void push(struct Node** head, int data) {
    struct Node* temp = createNode(data);
    temp->next = *head;
    *head = temp;
}

struct Node* merge(struct Node* a, struct Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->data <= b->data) {
        a->next = merge(a->next, b);
        return a;
    } else {
        b->next = merge(a, b->next);
        return b;
    }
}

void split(struct Node* head, struct Node** a, struct Node** b) {
    struct Node* slow = head;
    struct Node* fast = head->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *a = head;
    *b = slow->next;
    slow->next = NULL;
}

void mergeSort(struct Node** head) {
    struct Node* temp = *head;
    struct Node* a;
    struct Node* b;
    if (!temp || !temp->next) return;
    split(temp, &a, &b);
    mergeSort(&a);
    mergeSort(&b);
    *head = merge(a, b);
}

void printList(struct Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main() {
    struct Node* head = NULL;
    int n, x;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%d", &x);
        push(&head, x);
    }
    mergeSort(&head);
    printList(head);
    return 0;
}
