#include<stdio.h>
#include<stdlib.h>
int main(){
    int n, i, j, temp, total = 0, currentTime = 0, completed = 0, minIndex;
    int at[101], bt[101], process[101], wt[101], tat[101], ct[101], isCompleted[101] = {0};
    float avgWt = 0, avgTat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival times and burst times:\n");
    for (i = 0; i < n; i++) {
        printf("Process[%d] Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("Process[%d] Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        process[i] = i + 1;  // Store process ID
    }

    // Initialize all W.T, TAT, and C.T to 0
    for (i = 0; i < n; i++) {
        wt[i] = 0;
        tat[i] = 0;
        ct[i] = 0;
    }

    // Start scheduling
    while (completed != n) {
        // Find the process with the smallest B.T among the processes that have arrived
        minIndex = -1;
        for (i = 0; i < n; i++) {
            if (at[i] <= currentTime && !isCompleted[i]) {
                if (minIndex == -1 || bt[i] < bt[minIndex]) {
                    minIndex = i;
                }
            }
        }

        // If a process is found, execute it
        if (minIndex != -1) {
            currentTime += bt[minIndex];
            ct[minIndex] = currentTime;  // Completion time
            tat[minIndex] = ct[minIndex] - at[minIndex];  // Turnaround time
            wt[minIndex] = tat[minIndex] - bt[minIndex];  // W.T
            isCompleted[minIndex] = 1;  // Mark process as completed
            completed++;
        } else {
            // If no process is available, move the time forward (idle time)
            currentTime++;
        }
    }

    // Cal. total W.t and TAT time
    for (i = 0; i < n; i++) {
        total += wt[i];
    }
    avgWt = (float)total / n;

    total = 0;
    for (i = 0; i < n; i++) {
        total += tat[i];
    }
    avgTat = (float)total / n;

    // Gantt Chart
    printf("\nGantt Chart:\n");
    printf("------------------------------------------------\n|");
    currentTime = 0;
    for (i = 0; i < n; i++) {
        if (isCompleted[i]) {
            printf(" P%d |", process[i]);
        }
    }
    printf("\n------------------------------------------------\n");

    // Show C.T markers below the chart
    currentTime = 0;
    printf("0");
    for (i = 0; i < n; i++) {
        if (isCompleted[i]) {
            currentTime = ct[i];
            printf("    %d", currentTime);
        }
    }

    // Print 
    printf("\n\nProcess\t    Arrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", process[i], at[i], bt[i], wt[i], tat[i], ct[i]);
    }


    printf("\n\nAverage Waiting Time: %.2f", avgWt);
    printf("\nAverage Turnaround Time: %.2f\n", avgTat);

    return 0;
}
