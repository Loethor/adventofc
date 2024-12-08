#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COLUMNS 10

bool is_safe_report(int *report, int num_elements) {
    bool is_increasing = true;
    bool is_decreasing = true;

    for (int i = 0; i < num_elements - 1; i++) {
        int diff = abs(report[i] - report[i+1]);

        // fail fast if the difference is greater than 3 or lesser than 1
        if (diff < 1 || diff > 3) {
            return false;
        }

        // if increasing -> decreasing to false
        // if decreasing -> increasing to false 
        if (report[i] < report[i+1]) {
            is_decreasing = false;
        } else if (report[i] > report[i+1]) {
            is_increasing = false;
        }
    }

    return is_increasing || is_decreasing;
}


bool is_safe_with_dampener(int *report, int num_elements) {

    // do the previous safe check
    if (is_safe_report(report, num_elements)) {
        return true;
    }

    //  try all the permutations removing 1 element
    for (int i = 0; i < num_elements; i++) {
        int temp[MAX_COLUMNS];
        int k = 0;

        // add elements to temp, except for the j that is equal to i
        for (int j = 0; j < num_elements; j++) {
            if (j != i) {
                temp[k++] = report[j];
            }
        }

        // check if temp is safe
        if (is_safe_report(temp, num_elements - 1)) {
            return true;
        }
    }

    // if no temp is safe, the whole is unsafe
    return false;
}


void solve(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int row[MAX_COLUMNS]; // Fixed-size array to hold integers per row
    int column_count = 0;
    int safe_reports = 0;
    int safe_dampened_reports = 0;

    while (!feof(file)) {
        column_count = 0;

        while (fscanf(file, "%d", &row[column_count]) == 1) {
            column_count++;

            // Check if we exceed the fixed column capacity
            if (column_count >= MAX_COLUMNS) {
                fprintf(stderr, "Error: Row exceeds maximum column capacity of %d\n", MAX_COLUMNS);
                fclose(file);
                exit(EXIT_FAILURE);
            }

            int ch = fgetc(file);
            if (ch == '\n' || ch == EOF) {
                break;
            }
            ungetc(ch, file);
        }

        if (column_count > 0) {
            if (is_safe_report(row, column_count)) {
                safe_reports++;
            }

            if (is_safe_with_dampener(row, column_count)) {
                safe_dampened_reports++;
            }
        }
    }
    fclose(file);

    printf("The A result: %d\n", safe_reports);
    printf("The B result: %d\n", safe_dampened_reports);
    printf("\n");
}

int main(void){
    solve("2024/day02/data/example.txt");
    solve("2024/day02/data/data.txt");
    return 0;
}