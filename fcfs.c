#include <stdio.h>
#include <stdbool.h>

int current_time = 0;

struct Process {
    int at, bt, ct, tat, wt;
    bool complete;
};

struct Process p[100];

void FCFS(int n);
void calculate_Average(int n);

int main() {
    int n;
    printf("\nEnter the number of processes you want to enter: ");
    scanf("%d", &n);
    while (n > 100) {
        printf("\nNumber exceeds the max limit, try again: ");
        scanf("%d", &n);
    }

    for (int i = 0; i < n; i++) {
        printf("\nEnter AT (Arrival Time) and BT (Burst Time) respectively for Process P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].complete = false;  // Mark the process as not completed
    }

    printf("\nPID\tAT\tBT");
    for (int i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d", i + 1, p[i].at, p[i].bt);
    }

    FCFS(n);
    calculate_Average(n);

    return 0;
}

void FCFS(int n) {
    int completed = 0;

    while (completed < n) {
        int idx = -1;

        // Find the first process that is not completed and has arrived
        for (int i = 0; i < n; i++) {
            if (!p[i].complete && p[i].at <= current_time) {
                if (idx == -1 || p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }

        // If no process has arrived yet, increment the time
        if (idx == -1) {
            current_time++;
            continue;
        }

        // Execute the selected process
        p[idx].ct = current_time + p[idx].bt;  // Completion Time
        p[idx].tat = p[idx].ct - p[idx].at;    // Turnaround Time
        p[idx].wt = p[idx].tat - p[idx].bt;    // Waiting Time
        current_time = p[idx].ct;              // Update current time
        p[idx].complete = true;                // Mark as completed
        completed++;
    }

    // Display process execution results
    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT");
    for (int i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d", i + 1, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

void calculate_Average(int n) {
    float total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++) {
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }

    printf("\n\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
}
