#include<stdio.h>
int main() {    
    int p[101], bt[101], wt[101], tat[101], pr[101], i, j, n, total = 0, pos, temp;
    float avgWt, avgTat;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the burst time and priority for each process:\n");
    for (i = 0; i < n; i++) {
        printf("\nP[%d]\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority: ");
        scanf("%d", &pr[i]);
        p[i] = i + 1;  
    }
    // Sort processes based on priority (lower value means higher priority)
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (pr[j] < pr[pos]) {
                pos = j;
            }
        }
        // Swap priority
        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;

        // Swap burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap process number
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Calculate W.T for each process
    wt[0] = 0;  // W.T for the first process is 0
    total = 0;

    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
        total += wt[i];
    }

    // Cal. avg. WT
    avgWt = (float)total / n;

    // Cal. TAT for each process
    total = 0;
    printf("\nProcess\t    Burst Time\t    Waiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];  // TAT = B.T + W.T
        total += tat[i];

        // Print process Details
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d", p[i], bt[i], wt[i], tat[i]);
    }
    // Cal. avg TAT
    avgTat = (float)total / n;

    printf("\n\nAverage Waiting Time = %.2f", avgWt);
    printf("\nAverage Turnaround Time = %.2f\n", avgTat);

    return 0; 
}
