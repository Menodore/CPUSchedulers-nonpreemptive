#include <stdio.h>

int n;
int at[10], bt[10], ct[10], wt[10], tt[10], completed[10];

void swap(int a , int b) {
	int temp;
	temp = a;
	a = b;
	b = temp;
}
void sortByArrival() {
    int i, j, temp;
    char temp_char;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
		swap(at[i],at[j]);
		swap(bt[i],bt[j]);
               
            }
        }
    }
}

int main() {
    int i, t, sum_bt = 0;
    float avgwt = 0, avgtt = 0;
    n = 5;

    int arriv[] = { 0, 2, 4, 6, 8 };

    int burst[] = { 3, 6, 4, 5, 2 };

    for (i = 0; i < n; i++) {
        at[i] = arriv[i];
        bt[i] = burst[i];
        completed[i] = 0;  //all processes incomplete
        sum_bt += bt[i];
    }

    sortByArrival();
    printf("\nPID\tAT\tBT\tWT\tTAT\tRR");

    for (t = at[0]; t < sum_bt;) {
        float hrr = -9999; // Highest Response Ratio
        float temp_rr;
        int loc = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= t && completed[i] == 0) { 
                temp_rr = (float)(bt[i] + (t - at[i])) / bt[i];  //response ratio

                if (hrr < temp_rr) {
                    hrr = temp_rr;
                    loc = i;
                }
            }
        }

        if (loc != -1) {
            t += bt[loc];
            wt[loc] = t - at[loc] - bt[loc];
            tt[loc] = t - at[loc];
            completed[loc] = 1;  //process completed

            avgwt += wt[loc];
            avgtt += tt[loc];

            printf("\nP%d\t%d\t%d\t%d\t%d\t%f",loc+1, at[loc], bt[loc], wt[loc], tt[loc], hrr);
        }
    }

    printf("\nAverage Waiting Time: %f\n", avgwt / n);
    printf("Average Turnaround Time: %f\n", avgtt / n);

    return 0;
}
