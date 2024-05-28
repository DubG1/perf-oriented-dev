#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void read(int index, void* array, size_t elem_size, size_t num_elements) {
    if (index < 0 || index >= (int)num_elements) {
    fprintf(stderr, "read: Invalid index %d for array with %zu elements\n", index, num_elements);
    return;
  }
    void* element = (char*)array + index * elem_size;   //calc element address
    volatile int value = *(int*)element; 
}

void write(int index, int value, void* array, size_t elem_size) { 
    void* element = (char*)array + index * elem_size;
    memcpy(element, &value, elem_size); //copy value to element
}

void insertion(int index, int value, void* array, size_t size, size_t elem_size) {
    void* element = (char*)array + index * elem_size;
    memmove((char*)element + elem_size, element, (size - index - 1) * elem_size); //move elements foward
    memcpy(element, &value, elem_size);
}

void deletion(int index, void* array, size_t size, size_t elem_size) {
    void* element = (char*)array + index * elem_size;
    memmove(element, (char*)element + elem_size, (size - index - 1) * elem_size);   //move elements backward
}

void benchmark_array(size_t iterations, double ins_del_ratio, double read_write_ratio, size_t elem_size, size_t num_elements) { //parameters iterations, insertion/deletion ratio, read/write ratio, element size, number of elements
    void* array = malloc((num_elements + 1) * elem_size);

    if (array == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    //fill array
    for (size_t i = 0; i < num_elements; ++i) {
        write(i, i, array, elem_size);
    }

    //calc number of iterations
    size_t ins_del_operations = (size_t)(iterations * ins_del_ratio);
    size_t read_write_operations = iterations - ins_del_operations;
    size_t read_operations = (size_t)(read_write_operations * read_write_ratio);
    size_t write_operations = read_write_operations - read_operations;

    clock_t start_time = clock();
    double time_taken = 0.0;

    size_t i = 0;
    while (i < iterations) {
        size_t index = i % num_elements;

        if (i < ins_del_operations / 2) {
            insertion(index, i, array, num_elements, elem_size);
        } else if (i < ins_del_operations) {
            deletion(index, array, num_elements, elem_size);
        } else if (i < ins_del_operations + read_operations) {
            read(index, array, elem_size, num_elements);
        } else {
            write(index, i, array, elem_size);
        }

        // calculate elapsed time
        clock_t current_time = clock();
        time_taken = ((double)(current_time - start_time)) / CLOCKS_PER_SEC;

        if (time_taken >= 5.0) {
            break;
        }

        i++;
    }

    printf("%zu, %f\n", iterations, time_taken);

    free(array);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s ins_del_ratio read_write_ratio element_size num_elements\n", argv[0]);
        return 1;
    }
 
    int ins_del_ratio = atoi(argv[1]);
    int read_write_ratio = atoi(argv[2]);
    int elem_size = atoi(argv[3]);
    int num_elements = atoi(argv[4]);

    size_t iterations = 100000;

    benchmark_array(iterations, ins_del_ratio, read_write_ratio, elem_size, num_elements);

    return 0;
}