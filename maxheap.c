#include <stdio.h>

#define MAX 100

int heap[MAX], size = 0;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapify(int i) {
    int l = 2*i, r = 2*i + 1, largest = i;
    if (l <= size && heap[l] > heap[largest])
        largest = l;
    if (r <= size && heap[r] > heap[largest])
        largest = r;
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(largest);
    }
}

void insert(int val) {
    if (size == MAX-1) return;
    heap[++size] = val;
    int i = size;
    while (i > 1 && heap[i/2] < heap[i]) {
        swap(&heap[i], &heap[i/2]);
        i /= 2;
    }
}

int deleteMax() {
    if (size == 0) return -1;
    int max = heap[1];
    heap[1] = heap[size--];
    heapify(1);
    return max;
}

void buildHeap(int arr[], int n) {
    size = n;
    for (int i = 1; i <= n; i++)
        heap[i] = arr[i];
    for (int i = n/2; i >= 1; i--)
        heapify(i);
}

int peek() {
    if (size == 0) return -1;
    return heap[1];
}

void display() {
    for (int i = 1; i <= size; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

int main() {
    int choice, val, n, arr[MAX];

    while (1) {
        printf("\n1.Insert\n2.Delete Max\n3.Peek Max\n4.Build Heap\n5.Display Heap\n6.Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            scanf("%d", &val);
            insert(val);
        }
        else if (choice == 2) {
            printf("Deleted: %d\n", deleteMax());
        }
        else if (choice == 3) {
            printf("Max: %d\n", peek());
        }
        else if (choice == 4) {
            printf("Enter number of elements: ");
            scanf("%d", &n);
            for (int i = 1; i <= n; i++)
                scanf("%d", &arr[i]);
            buildHeap(arr, n);
        }
        else if (choice == 5) {
            display();
        }
        else if (choice == 6) {
            break;
        }
        else {
            printf("Invalid\n");
        }
    }
    return 0;
}
