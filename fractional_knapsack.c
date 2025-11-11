#include<stdio.h>

int main() {
    int n, capacity;
    double maxprofit = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int weight[n], value[n];
    float ratio[n];

    printf("Enter the weight and value of items:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &weight[i], &value[i]);
        ratio[i] = (float)value[i] / weight[i];
    }

    printf("Enter the knapsack capacity: ");
    scanf("%d", &capacity);

    // Sorting by ratio (descending)
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(ratio[i] < ratio[j]) {
                float tempRatio = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = tempRatio;

                int tempW = weight[i];
                weight[i] = weight[j];
                weight[j] = tempW;

                int tempV = value[i];
                value[i] = value[j];
                value[j] = tempV;
            }
        }
    }

    // Applying Greedy
    for(int i = 0; i < n; i++) {
        if(weight[i] <= capacity) {
            maxprofit += value[i];
            capacity -= weight[i];
        } else {
            maxprofit += ratio[i] * capacity;
            break;
        }
    }

    printf("Total profit after greedy = %.2lf\n", maxprofit);
    return 0;
}
