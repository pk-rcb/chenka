#include <stdio.h>
#include <stdlib.h>

int *heap;
int size = 0;
int capacity;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifydown(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] > heap[largest])
        largest = left;
    if (right < size && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapifydown(largest);
    }
}

void heapifyup(int i) {
    int parent = (i - 1) / 2;
    if (i > 0 && heap[i] > heap[parent]) {
        swap(&heap[i], &heap[parent]);
        heapifyup(parent);
    }
}

void insert(int data) {
    if (size == capacity) {
        printf("Heap full!\n");
        return;
    }
    heap[size] = data;
    size++;
    heapifyup(size - 1);
}

void deleteRoot() {
    if (size <= 0) {
        printf("Heap empty!\n");
        return;
    }
    printf("Deleted root: %d\n", heap[0]);
    heap[0] = heap[size - 1];
    size--;
    heapifydown(0);
}

void buildheap() {
    printf("Enter number of elements: ");
    int n;
    scanf("%d", &n);
    if (n > capacity) {
        printf("Too many elements!\n");
        return;
    }
    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &heap[i]);
    size = n;

    for (int i = (size / 2) - 1; i >= 0; i--)
        heapifydown(i);
}

void heapsort() {
    int original_size = size;
    for (int i = size - 1; i > 0; i--) {
        swap(&heap[0], &heap[i]);
        size--;
        heapifydown(0);
    }
    size = original_size;
}

void display() {
    for (int i = 0; i < size; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

int main() {
    printf("Enter heap capacity: ");
    scanf("%d", &capacity);
    heap = (int *)malloc(capacity * sizeof(int));

    buildheap();

    printf("Heap built: ");
    display();

    insert(99);
    printf("After inserting 99: ");
    display();

    deleteRoot();
    printf("After deleting root: ");
    display();

    heapsort();
    printf("After Heap Sort: ");
    display();

    free(heap);
    return 0;
}
