#include <stdio.h>
#define MAX_PROCESSES 10
typedef struct {
    int pid;      
    int burst;     
} Process;

// F cal and display wait and turn-around times
void scheduleFCFS(Process queue[], int n, const char *queueName) {
    int waitTime[MAX_PROCESSES], turnAroundTime[MAX_PROCESSES];
    float totalWait = 0, totalTurnAround = 0;

    waitTime[0] = 0; 
    turnAroundTime[0] = queue[0].burst;

    printf("\n--- %s Processes ---\n", queueName);
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 1; i < n; i++) {
        waitTime[i] = waitTime[i - 1] + queue[i - 1].burst;
        turnAroundTime[i] = waitTime[i] + queue[i].burst;
    }

    for (int i = 0; i < n; i++) {
        totalWait += waitTime[i];
        totalTurnAround += turnAroundTime[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", queue[i].pid, queue[i].burst, waitTime[i], turnAroundTime[i]);
    }

    printf("\nAverage %s Waiting Time: %.2f", queueName, totalWait / n);
    printf("\nAverage %s Turnaround Time: %.2f\n", queueName, totalTurnAround / n);
}

int main() {
    Process systemQueue[MAX_PROCESSES], userQueue[MAX_PROCESSES];
    int sysCount, userCount;

    //  system processes
    printf("Enter number of system processes: ");
    scanf("%d", &sysCount);
    for (int i = 0; i < sysCount; i++) {
        systemQueue[i].pid = i + 1;
        printf("Enter burst time for system process %d: ", systemQueue[i].pid);
        scanf("%d", &systemQueue[i].burst);
    }

    // user processes
    printf("\nEnter number of user processes: ");
    scanf("%d", &userCount);
    for (int i = 0; i < userCount; i++) {
        userQueue[i].pid = i + 1;
        printf("Enter burst time for user process %d: ", userQueue[i].pid);
        scanf("%d", &userQueue[i].burst);
    }
    scheduleFCFS(systemQueue, sysCount, "System");

    scheduleFCFS(userQueue, userCount, "User");
    return 0;
}
