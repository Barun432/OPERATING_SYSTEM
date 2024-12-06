//////////////////////////// FIF0//////////////////////////////////
#include <stdio.h>
#include <stdbool.h>

int fifo_page_replacement(int frames, int requests[], int n) {
    int page_faults = 0;
    int memory[frames];
    int front = 0;

    // Initialize memory slots to -1 (indicating empty slots)
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        bool found = false;
        // Check if the page is already in memory
        for (int j = 0; j < frames; j++) {
            if (memory[j] == requests[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            // Page fault occurs
            page_faults++;
            memory[front] = requests[i]; // Replace the oldest page
            front = (front + 1) % frames; // Move to the next slot in FIFO order
        }
    }
    return page_faults;
}

int main() {
    int frames, n;

    printf("Enter number of frames available: ");
    scanf("%d", &frames);
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter requested page numbers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int page_faults = fifo_page_replacement(frames, requests, n);
    printf("Total number of page faults: %d\n", page_faults);

    return 0;
}
//////////////////////////LRU/////////////
#include <stdio.h>
#include <stdbool.h>

int find_lru(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}
int lru_page_replacement(int frames, int requests[], int n) {
    int page_faults = 0;
    int memory[frames];
    int time[frames];
    int count = 0;

    // Initialize memory slots to -1 (indicating empty slots)
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        bool found = false;

        // Check if the page is already in memory
        for (int j = 0; j < frames; j++) {
            if (memory[j] == requests[i]) {
                found = true;
                time[j] = ++count; // Update usage time
                break;
            }
        }

        if (!found) {
            // Page fault occurs
            page_faults++;
            int pos;
            if (i < frames) {
                pos = i; // Initially fill empty slots
            } else {
                pos = find_lru(time, frames); // Find the least recently used page
            }
            memory[pos] = requests[i];
            time[pos] = ++count; // Update usage time
        }
    }

    return page_faults;
}

int main() {
    int frames, n;

    printf("Enter number of frames available: ");
    scanf("%d", &frames);
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter requested page numbers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int page_faults = lru_page_replacement(frames, requests, n);
    printf("Total number of page faults: %d\n", page_faults);

    return 0;
}
//////////////////////firstfit/////////////
#include <stdio.h>
void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n]; 
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) { 
            if (blockSize[j] >= processSize[i]) { 
                allocation[i] = j; 
                blockSize[j] -= processSize[i]; 
                break; 
            }
        }}
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }}
int main() {
    int m, n;
    printf("Enter number of free blocks available: ");
    scanf("%d", &m);

    int blockSize[m];
    printf("Enter sizes of blocks: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processSize[n];
    printf("Enter sizes of processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }
    firstFit(blockSize, m, processSize, n);

    return 0;
}
////////////////////bestfit//////
#include <stdio.h>

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;

        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIndex == -1 || blockSize[j] < blockSize[bestIndex]) {
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blockSize[bestIndex] -= processSize[i];
        }
    }

    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int m, n;

    printf("Enter number of free blocks available: ");
    scanf("%d", &m);

    int blockSize[m];
    printf("Enter sizes of blocks: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processSize[n];
    printf("Enter sizes of processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    bestFit(blockSize, m, processSize, n);

    return 0;
}
///////////////////worst///////////////
#include <stdio.h>

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int worstIndex = -1;

        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex]) {
                    worstIndex = j;
                }
            }
        }

        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }

    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int blockSize[m];
    printf("Enter sizes of blocks: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int processSize[n];
    printf("Enter sizes of processes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    worstFit(blockSize, m, processSize, n);

    return 0;
}


////////////////////////////////////sequential.///////////
#include <stdio.h>
#include <string.h>

struct file {
    char name[20];  // File name
    int sb;         // Starting block of the file
    int nob;        // Number of blocks allocated for the file
} f[30];            // Array to hold up to 30 files

int main() {
    int n;
    char searchFile[20];

    // Input the number of files
    printf("Enter the number of files: ");
    scanf("%d", &n);

    // Input file details
    for (int i = 0; i < n; i++) {
        printf("Enter the file name %d: ", i + 1);
        scanf("%s", f[i].name);

        printf("Enter the starting block of file %d: ", i + 1);
        scanf("%d", &f[i].sb);

        printf("Enter the number of blocks in file %d: ", i + 1);
        scanf("%d", &f[i].nob);
    }

    // Input file name to search
    printf("\nEnter the file name to be searched: ");
    scanf("%s", searchFile);

    // Search for the file
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(searchFile, f[i].name) == 0) {
            break;
        }
    }

    // Display the result
    if (i == n) {
        printf("\nFile not found.\n");
    } else {
        printf("\nFILE NAME\tSTART BLOCK\tNO. OF BLOCKS\tBLOCK NUMBERS\n");
        printf("%s\t\t%d\t\t%d\t\t", f[i].name, f[i].sb, f[i].nob);
        for (int j = 0; j < f[i].nob; j++) {
            printf("%d ", f[i].sb + j);
        }
        printf("\n");
    }

    return 0;
}
///////////////// indexed///////////

#include <stdio.h>
#include <string.h>

struct file {
    char name[20]; // File name
    int nob;       // Number of blocks
    int blocks[30]; // Array of blocks
} f[30];

int main() {
    int n;            // Number of files
    char sear[20];    // File name to search

    // Input number of files
    printf("Enter the number of files: ");
    scanf("%d", &n);

    // Input file details
    for (int i = 0; i < n; i++) {
        printf("Enter the file name %d: ", i + 1);
        scanf("%s", f[i].name);

        printf("Enter the number of blocks in file %d: ", i + 1);
        scanf("%d", &f[i].nob);

        printf("Enter the blocks of the file %d: ", i + 1);
        for (int j = 0; j < f[i].nob; j++) {
            scanf("%d", &f[i].blocks[j]); // Correct indexing for block input
        }
    }

    // Input file name to search
    printf("Enter the file name to be searched: ");
    scanf("%s", sear);

    // Search for the file
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(sear, f[i].name) == 0) {
            break;
        }
    }

    // If the file is not found
    if (i == n) {
        printf("File not found.\n");
    } else {
        // Display the file details
        printf("\nFILE NAME\tNO OF BLOCKS\tBLOCK NUMBERS\n");
        printf("%s\t\t%d\t\t", f[i].name, f[i].nob);
        for (int j = 0; j < f[i].nob; j++) {
            printf("%d ", f[i].blocks[j]);
        }
        printf("\n");
    }

    return 0;
}
/////////////////////LINKED/////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct block {
    int bno;               // Block number
    struct block *next;    // Pointer to the next block
};

struct file {
    char name[20];         // File name
    int nob;               // Number of blocks
    struct block *sb;      // Pointer to the starting block
} f[30];

int main() {
    int n;
    struct block *temp;
    char s[20];            // String for the file name to search

    // Input number of files
    printf("Enter the number of files: ");
    scanf("%d", &n);

    // Input file details
    for (int i = 0; i < n; i++) {
        printf("Enter the file name %d: ", i + 1);
        scanf("%s", f[i].name);

        printf("Enter the number of blocks in file %d: ", i + 1);
        scanf("%d", &f[i].nob);

        // Create the linked list for blocks
        printf("Enter the blocks of the file: ");
        f[i].sb = (struct block *)malloc(sizeof(struct block)); // Allocate the first block
        temp = f[i].sb;
        scanf("%d", &temp->bno); // Input the first block number
        temp->next = NULL;

        for (int j = 1; j < f[i].nob; j++) { // Loop for remaining blocks
            temp->next = (struct block *)malloc(sizeof(struct block)); // Allocate memory
            temp = temp->next;
            scanf("%d", &temp->bno); // Input block number
            temp->next = NULL;
        }
    }

    // Search for a file by name
    printf("Enter the file name to be searched: ");
    scanf("%s", s);

    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(s, f[i].name) == 0) {
            break; // File found
        }
    }

    if (i == n) {
        printf("File not found.\n");
    } else {
        // Display file details
        printf("\nFILE NAME\tNO OF BLOCKS\tBLOCK NUMBERS\n");
        printf("%s\t\t%d\t\t", f[i].name, f[i].nob);
        temp = f[i].sb;
        while (temp != NULL) { // Traverse the linked list of blocks
            printf("%d -> ", temp->bno);
            temp = temp->next;
        }
        printf("NULL\n"); // ++++Indicate the end of the block chain
    }

    return 0;
}
