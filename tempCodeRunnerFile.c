#include <stdio.h>

int main() {
    int disk[100] = {0}, disk_size, num_files, start, size;

    printf("Enter total number of disk blocks: ");
    scanf("%d", &disk_size);

    printf("Enter number of files to allocate: ");
    scanf("%d", &num_files);

    for (int i = 0; i < num_files; i++) {
        printf("Enter start block and size for file %d: ", i + 1);
        scanf("%d %d", &start, &size);

        int can_allocate = 1;
        for (int j = start; j < start + size; j++) {
            if (j >= disk_size || disk[j] == 1) {
                can_allocate = 0;
                break;
            }
        }

        if (can_allocate) {
            for (int j = start; j < start + size; j++) disk[j] = 1;
            printf("File %d allocated from block %d to block %d.\n", i + 1, start, start + size - 1);
        } else {
            printf("File %d could not be allocated.\n", i + 1);
        }
    }
    return 0;
}
