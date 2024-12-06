/////////// FCFS//////////////
#include <stdio.h>
#include <stdlib.h>
int main() {
    int Request[100]; 
    int travel=0; 
    int n;            
    int initialHead;   
    printf("Enter the number of Requests: ");
    scanf("%d", &n);
  
    printf("Enter the Request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &Request[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);
    for (int i = 0; i < n; i++) {
        travel += abs(Request[i] - initialHead);
        initialHead = Request[i];               // Update the head position
    }
    printf("Total number of head movements: %d\n", travel);
    return 0;
}

//////////////////////////////////////// CSCAN///////////////////////////
#include <stdio.h>
#include <stdlib.h>

int main() {
    int request[100];
    int n;
    int travel = 0;
    int size;
    int move;
    int index = -1;
    int initialHead;

    printf("Enter the number of Requests: ");
    scanf("%d", &n);

    printf("Enter the sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    printf("Enter the disk size: ");
    scanf("%d", &size);

    printf("Enter the head movement direction (1 for high, 0 for low): ");
    scanf("%d", &move);

    // Sort the requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (request[j] > request[j + 1]) {
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    // Find the index of the first request greater than or equal to the initial head
    for (int i = 0; i < n; i++) {
        if (initialHead < request[i]) {
            index = i;
            break;
        }
    }

    if (index == -1) { // If all requests are less than the initial head
        index = n;
    }

    // Handle movement towards high values
    if (move == 1) {
        for (int i = index; i < n; i++) {
            travel += abs(request[i] - initialHead);
            initialHead = request[i];
        }
        // Last movement to maximum disk size
        travel += abs(size - 1 - initialHead);
        initialHead = 0; // Wrap around to the start of the disk

        for (int i = 0; i < index; i++) {
            travel += abs(request[i] - initialHead);
            initialHead = request[i];
        }
    }
    // Handle movement towards low values
    else {
        for (int i = index - 1; i >= 0; i--) {
            travel += abs(request[i] - initialHead);
            initialHead = request[i];
        }

        // Last movement to minimum disk size
        travel += abs(initialHead - 0);
        initialHead = size - 1; // Wrap around to the end of the disk

        for (int i = n - 1; i >= index; i--) {
            travel += abs(request[i] - initialHead);
            initialHead = request[i];
        }
    }
    printf("Total travel movement is %d\n", travel);
    return 0;
}
///////////////////////////////////SCAN/////////////////////////
#include <stdio.h>
#include <stdlib.h>

int main() {
    int request[100];
    int travel = 0;
    int initialHead;
    int move, n; // `move`: 0 -> backward, 1 -> forward
    int index = -1; // To find the index of the initial head position
    int size;

    // Input number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    // Input request sequence
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    // Input initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    // Input total disk size
    printf("Enter the total disk size: ");
    scanf("%d", &size);

    // Input head movement direction
    printf("Enter the head movement direction (0 for backward, 1 for forward): ");
    scanf("%d", &move);

    // Sort the requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (request[j] > request[j + 1]) {
                int temp = request[j];
                request[j] = request[j + 1];
                request[j + 1] = temp;
            }
        }
    }

    // Find the index of the first request greater than or equal to the initial head
    for (int i = 0; i < n; i++) {
        if (initialHead <= request[i]) {
            index = i;
            break;
        }
    }

    // Logic for head movement
    if (move == 1) { // Moving forward
        // Process requests towards the end of the disk
        for (int i = index; i < n; i++) {
            travel += abs(request[i] - initialHead);
            initialHead = request[i];
        }
        // Travel to the end of the disk
        travel += abs(size - 1 - initialHead);
        initialHead = size - 1;

        // Process requests in reverse direction
        for (int i = index - 1; i >= 0; i--) {
            travel += abs(request[i] - initialHead);
            initialHead = request[i];
        }
    } else { // Moving backward
        // Process requests towards the start of the disk
        for (int i = index - 1; i >= 0; i--) {
            travel += abs(request[i] - initialHead);
            initialHead = request[i];
        }
        // Travel to the start of the disk
        travel += abs(initialHead - 0);
        initialHead = 0;

        // Process requests in forward direction
        for (int i = index; i < n; i++) {
            travel += abs(request[i] - initialHead);
            initialHead = request[i];
        }
    }

    // Output the total travel movement
    printf("Total head movement: %d\n", travel);

    return 0;
}
