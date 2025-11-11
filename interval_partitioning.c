#include <stdio.h>

struct Interval {
    int start, end;
};

void sortByStart(struct Interval arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i].start > arr[j].start) {
                struct Interval temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Interval arr[n];

    printf("Enter start and end times:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }

    // Step 1: Sort by start time
    sortByStart(arr, n);

    int rooms[n];   // stores end time of each room
    int roomCount = 0;

    for(int i = 0; i < n; i++) {
        int assigned = 0;

        for(int r = 0; r < roomCount; r++) {
            // If current room is free
            if(rooms[r] <= arr[i].start) {
                rooms[r] = arr[i].end; // assign interval to this room
                assigned = 1;
                break;
            }
        }

        // If no room is free --> create new room
        if(!assigned) {
            rooms[roomCount++] = arr[i].end;
        }
    }

    printf("Minimum number of resources required = %d\n", roomCount);

    return 0;
}
