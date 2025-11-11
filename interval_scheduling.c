#include <stdio.h>

// structure to store activity (start & finish time)
struct Activity {
    int start, finish;
};

int main() {
    int n;
    printf("Enter number of activities: ");
    scanf("%d", &n);

    struct Activity act[n];

    printf("Enter start and finish time of activities:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &act[i].start, &act[i].finish);
    }

    // Sort activities by finish time (ascending)
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(act[i].finish > act[j].finish) {
                struct Activity temp = act[i];
                act[i] = act[j];
                act[j] = temp;
            }
        }
    }

    printf("\nSelected activities:\n");
    
    // Always select first activity
    int last = 0;
    printf("(%d, %d) ", act[last].start, act[last].finish);

    // Check rest of the activities
    for(int i = 1; i < n; i++) {
        if(act[i].start >= act[last].finish) {
            printf("(%d, %d) ", act[i].start, act[i].finish);
            last = i;
        }
    }

    printf("\n");
    return 0;
}
