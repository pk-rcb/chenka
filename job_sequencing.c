#include <stdio.h>

struct Job {
    int id;        // Job ID
    int deadline;  // Deadline of the job
    int profit;    // Profit if job is completed
};

// Sort jobs by profit (descending)
void sortByProfit(struct Job jobs[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(jobs[i].profit < jobs[j].profit) {
                struct Job temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of jobs: ");
    scanf("%d", &n);

    struct Job jobs[n];
    printf("Enter Job ID, Deadline, Profit:\n");
    for(int i=0; i<n; i++) {
        scanf("%d %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    sortByProfit(jobs, n);

    int slot[n];        // Time slots
    int result[n];      // Sequence of jobs
    for(int i=0; i<n; i++)
        slot[i] = 0;    // all slots initially empty

    int totalProfit = 0;

    // Job Scheduling
    for(int i=0; i<n; i++) {
        // find a free slot from min(deadline, n)-1 to 0
        for(int j = (jobs[i].deadline < n ? jobs[i].deadline : n) - 1; j >= 0; j--) {
            if(slot[j] == 0) {
                slot[j] = 1;
                result[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("\nScheduled Jobs: ");
    for(int i=0; i<n; i++) {
        if(slot[i] == 1)
            printf("J%d ", result[i]);
    }

    printf("\nTotal Profit = %d\n", totalProfit);
    return 0;
}
