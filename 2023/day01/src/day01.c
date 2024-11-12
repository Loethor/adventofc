// day01.c - Solution code for 2023, day01
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"


int calculate_sum(const char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int total_sum = 0;

    // Read the file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        int first_digit = -1, last_digit = -1;

        for (int i = 0; line[i] != '\0'; i++) {
            if (isdigit(line[i])) {
                first_digit = line[i] - '0';  // Convert character to integer
                break;
            }
        }

        for (int i = strlen(line) - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                last_digit = line[i] - '0';  // Convert character to integer
                break;
            }
        }

        if (first_digit != -1 && last_digit != -1) {
            int calibration_value = first_digit * 10 + last_digit;
            total_sum += calibration_value;
        }
    }

    fclose(file);
    return total_sum;
}

void run_example01() {
    const char *filename = "2023/day01/data/example.txt";
    int result = calculate_sum(filename);
    printf("The sum of all calibration values is: %d\n", result);
}

void run_day01a() {
    const char *filename = "2023/day01/data/data.txt";
    int result = calculate_sum(filename);
    printf("The sum of all calibration values is: %d\n", result);
}

int main(void){
    run_example01();
    run_day01a();
    return 0;
}