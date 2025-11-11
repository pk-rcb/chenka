#include <stdio.h>
#define MAX 100

int pq[MAX], size = 0;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapifyDown(int i) {
    int left = 2*i, right = 2*i + 1, largest = i;
    if (left <= size && pq[left] > pq[largest]) largest = left;
    if (right <= size && pq[right] > pq[largest]) largest = right;

    if (largest != i) {
        swap(&pq[i], &pq[largest]);
        heapifyDown(largest);
    }
}

void heapifyUp(int i) {
    while (i > 1 && pq[i/2] < pq[i]) {
        swap(&pq[i], &pq[i/2]);
        i /= 2;
    }
}

void insert(int value) {
    if (size >= MAX) return;
    pq[++size] = value;
    heapifyUp(size);
}

int getMax() {
    if (size == 0) return -1;
    return pq[1];
}

int deleteMax() {
    if (size == 0) return -1;
    int max = pq[1];
    pq[1] = pq[size--];
    heapifyDown(1);
    return max;
}

void display() {
    for (int i = 1; i <= size; i++)
        printf("%d ", pq[i]);
    printf("\n");
}

int main() {
    int choice, val;
    while (1) {
        printf("\n1.Insert\n2.Delete Max\n3.Peek\n4.Display\n5.Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter value: ");
            scanf("%d", &val);
            insert(val);
        }
        else if (choice == 2) {
            printf("Deleted: %d\n", deleteMax());
        }
        else if (choice == 3) {
            printf("Max: %d\n", getMax());
        }
        else if (choice == 4) {
            display();
        }
        else if (choice == 5) {
            break;
        }
        else {
            printf("Invalid choice\n");
        }
    }
    return 0;
}
