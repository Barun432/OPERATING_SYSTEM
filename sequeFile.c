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

