#include <stdio.h>

int main() {
    int n, i, currentTime = 0, completed = 0, shortest = 0, finishTime;
    int at[101], bt[101], remainingBt[101], wt[101], tat[101], ct[101];
    int min_time = 9999, is_completed = 0;
    float totalWt = 0, totalTat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival times and burst times:\n");
    for (i = 0; i < n; i++) {
        printf("Process[%d] Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process[%d] Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        remainingBt[i] = bt[i];  // Initialize remaining B.T
    }
    int complete = 0, min = 9999, shortestProcess = -1;
    int finish = 0, isAnyProcessRunning = 0;

    // Iterate over all processes until all are completed
    while (completed != n) {
        // Find the process with the shortest remaining B.T
        for (i = 0; i < n; i++) {
            if (at[i] <= currentTime && remainingBt[i] < min && remainingBt[i] > 0) {
                min = remainingBt[i];
                shortestProcess = i;
                isAnyProcessRunning = 1;
            }
        }

        if (!isAnyProcessRunning) {
            currentTime++;
            continue;
        }

        // Reduce the remaining burst time of the selected process
        remainingBt[shortestProcess]--;

        // If a process gets completely executed
        if (remainingBt[shortestProcess] == 0) {
            completed++;
            isAnyProcessRunning = 0;
            finishTime = currentTime + 1;

            // Calculate completion, WT, and TAT
            ct[shortestProcess] = finishTime;
            tat[shortestProcess] = ct[shortestProcess] - at[shortestProcess]; // TAT = C.T - A.T
            wt[shortestProcess] = tat[shortestProcess] - bt[shortestProcess]; // WT = TAT- BT

            // Accumulate wt and TAT for avg calc.
            totalWt += wt[shortestProcess];
            totalTat += tat[shortestProcess];

            if (wt[shortestProcess] < 0) {
                wt[shortestProcess] = 0;
            }

            min = 9999; // Reset min for next process
        }

        currentTime++;
    }
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", totalWt / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTat / n);

    return 0;
}
