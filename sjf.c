#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
    int completed = 0, time = 0, min_bt = 10000;
    int shortest = 0, finish_time;
    int remaining_bt[n];

    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }

    while (completed != n) {
        for (int j = 0; j < n; j++) {
            if ((at[j] <= time) && (remaining_bt[j] < min_bt) && remaining_bt[j] > 0) {
                min_bt = remaining_bt[j];
                shortest = j;
            }
        }

        time += remaining_bt[shortest];
        wt[shortest] = time - bt[shortest] - at[shortest];
        if (wt[shortest] < 0) {
            wt[shortest] = 0;
        }

        remaining_bt[shortest] = 0;
        min_bt = 10000;
        completed++;
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt, at);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("PID\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];

        printf("P%d\t%d\t%d\t%d\t%d\n", processes[i], at[i], bt[i], wt[i], tat[i]);
    }

    float avg_wt = (float)total_wt / (float)n;
    float avg_tat = (float)total_tat / (float)n;

    printf("Average waiting time = %f\n", avg_wt);
    printf("Average turn around time = %f\n", avg_tat);
}

int main() {
    int processes[] = {1, 2, 3, 4, 5};
    int n = sizeof(processes) / sizeof(processes[0]);

    int burst_time[] = {7, 4, 1, 4, 3};
    int arrival_time[] = {0, 2, 4, 5, 6};

    findAvgTime(processes, n, burst_time, arrival_time);

    return 0;
}
