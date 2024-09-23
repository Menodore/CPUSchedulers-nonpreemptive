#include <stdio.h>

int n, p[20], at[20], bt[20], ct[20], wt[20], tat[20], rt[20];

void nonPreemptivePriorityScheduler() {
    int i, j, time = 0, min_priority, x, total_completed = 0;
    float avgwt = 0, avgtt = 0;

    for (i = 0; i < n; i++) {
        rt[i] = 0; // Incomplete process
    }

    while (total_completed < n) {
        min_priority = 9999;
        x = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] == 0 && p[i] < min_priority) {
                min_priority = p[i];
                x = i;
            }
        }

        if (x != -1) {
            // Process selected
            time += bt[x];
            ct[x] = time;
            tat[x] = ct[x] - at[x];
            wt[x] = tat[x] - bt[x];
            rt[x] = 1;
            total_completed++;

            avgwt += wt[x];
            avgtt += tat[x];

            printf("\nP%d\t%d\t%d\t%d\t%d\t%d", x + 1, p[x], at[x], bt[x], wt[x], tat[x]);
        } else {
            time++;  // If no process is ready to execute, increment time
        }
    }

    avgwt /= n;
    avgtt /= n;

    printf("\n\nAverage WT: %.2f", avgwt);
    printf("\nAverage TAT: %.2f", avgtt);
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter the priority, arrival time, and burst time for process P%d respectively: ", i + 1);
        scanf("%d %d %d", &p[i], &at[i], &bt[i]);
    }

    printf("\nPID\tPt\tAT\tBT\tWT\tTAT");
    nonPreemptivePriorityScheduler();

    return 0;
}
