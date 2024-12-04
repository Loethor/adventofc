#include <stdio.h>
#include <stdlib.h>

// I need this for qsort. It takes a pointer to a function 
// with const void signature
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void solve(const char *filename) {

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int *array1 = NULL;
    int *array2 = NULL;

    // I allocate to some initial size of memory
    int number_of_allocated_rows = 10;

    array1 = malloc(number_of_allocated_rows * sizeof(int));
    array2 = malloc(number_of_allocated_rows * sizeof(int));
    if (array1 == NULL || array2 == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (fscanf(file, "%d %d", &array1[i], &array2[i]) == 2) {
        i++;

        // If i exceds the number of allocated rows, double them
        if (i >= number_of_allocated_rows) {
            number_of_allocated_rows *= 2;
            array1 = realloc(array1, number_of_allocated_rows * sizeof(int));
            array2 = realloc(array2, number_of_allocated_rows * sizeof(int));

            if (array1 == NULL || array2 == NULL) {
                perror("Error reallocating memory");
                free(array1);
                free(array2);
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(file);


    // Explicit size
    int size = i;


    // Sort the arrays
    qsort(array1, size, sizeof(int), compare);
    qsort(array2, size, sizeof(int), compare);

    // Calculate the differences (part A)
    int result_a = 0;

    int max_b = 0;
    for (int i = 0; i < size; i++)
    {
        if(array2[i] > max_b)
        {
            max_b = array2[i];
        }
        result_a += abs(array1[i] - array2[i]);
    }

    // Calculate similarity (part B)
    int result_b = 0;
    int *frequency = calloc(max_b + 1, sizeof(int));
    for (int i = 0; i < size; i++) {
        frequency[array2[i]]++;
    }

    for (int i = 0; i < size; i++) {
        result_b += array1[i] * frequency[array1[i]];
    }


    free(frequency);
    free(array1);
    free(array2);

    printf("The A result: %d\n", result_a);
    printf("The B result: %d\n", result_b);

}

int main(void){
    solve("2024/day01/data/example.txt");
    solve("2024/day01/data/data.txt");
    return 0;
}