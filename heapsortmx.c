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

void buildHeap(int arr[], int n) {
    size = n;
    for (int i = 1; i <= n; i++)
        heap[i] = arr[i];
    for (int i = n/2; i >= 1; i--)
        heapify(i);
}

int deleteMax() {
    int max = heap[1];
    heap[1] = heap[size--];
    heapify(1);
    return max;
}

void heapSort(int arr[], int n) {
    buildHeap(arr, n);
    for (int i = n; i >= 1; i--) {
        arr[i] = deleteMax();
    }
}

int main() {
    int n, arr[MAX];
    printf("Enter number of elements: ");
    scanf("%d", &n);

    for(int i=1;i<=n;i++)
        scanf("%d",&arr[i]);

    heapSort(arr, n);

    printf("Sorted: ");
    for(int i=1;i<=n;i++)
        printf("%d ", arr[i]);

    return 0;
}
