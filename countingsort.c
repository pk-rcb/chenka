#include <stdio.h>

int main() {
    int n, max = 0;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] > max)
            max = arr[i];
    }

    int count[max + 1];
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    // Count frequency
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    printf("\nCount Array (After Counting Frequency):\n");
    for (int i = 0; i <= max; i++)
        printf("%d ", count[i]);
    printf("\n");

    // Cumulative sum (prefix sum) to find positions
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    printf("\nCount Array (After Cumulative Sum / Prefix Sum):\n");
    for (int i = 0; i <= max; i++)
        printf("%d ", count[i]);
    printf("\n");

    int output[n];

    // Build output array (stable sorting, so traverse from end)
    printf("\nPasses while placing elements:\n");
    for (int i = n - 1; i >= 0; i--) {
        output[ count[arr[i]] - 1 ] = arr[i];
        count[arr[i]]--;

        for (int j = 0; j < n; j++)
            printf("%d ", output[j]);
        printf("\n");
    }

    printf("\nFinal Sorted Array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", output[i]);

    return 0;
}
