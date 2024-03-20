#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


#define PATH "output.txt"
#define SIZE 10240
#define OPERATIONS 100

void write_to_file(const char *path, int size, int operations) {
    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        perror("Error fopen");
        return;
    }

    for (int i = 0; i < operations; i++) {
        char *buffer = malloc(size);    //allocate buffer for writing
        if (buffer == NULL) {
            perror("Error malloc");
            return;
        }

        for (int j = 0; j < size; j++) {
            buffer[j] = (char)(rand() % 256);   //generate random byte
        }

        fwrite(buffer, 1, size, file);
        free(buffer);
    }

    fclose(file);
}

int main() {
    srand((unsigned int)time(NULL));

    FILE *file = fopen(PATH, "wb");
    if (file == NULL) {
        perror("Error fopen");
        return 1;
    }
    fclose(file);

    while (1)
    {
        write_to_file(PATH, SIZE, OPERATIONS);

    }
    return 0;
}