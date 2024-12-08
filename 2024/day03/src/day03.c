#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pcre.h>


void handle_mul(const char *line, bool *enabled, int *total) {
    const char *pattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)";
    const char *error;
    int erroffset;
    pcre *re = pcre_compile(pattern, 0, &error, &erroffset, NULL);
    if (re == NULL) {
        fprintf(stderr, "PCRE compilation failed: %s\n", error);
        return;
    }

    int ovector[64];
    int rc = 0;
    int offset = 0;
    

    while ((rc = pcre_exec(re, NULL, line, (int)strlen(line), offset, 0, ovector, sizeof(ovector) / sizeof(ovector[0]))) >= 0) {
        
        // matches x and y
        char x_str[4] = {0}, y_str[4] = {0};
        snprintf(x_str, ovector[3] - ovector[2] + 1, "%.*s", ovector[3] - ovector[2], line + ovector[2]);
        snprintf(y_str, ovector[5] - ovector[4] + 1, "%.*s", ovector[5] - ovector[4], line + ovector[4]);

        if (*enabled) {
            int x = atoi(x_str);
            int y = atoi(y_str);
            *total += x * y;
            printf("Found match: X = %d, Y = %d, Current Total: %d\n", x, y, *total);
        }

        // moves the offset
        offset = ovector[1];
    }

    pcre_free(re);
}

void solve(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[4096];
    bool is_enabled = true;
    int total = 0;

    while (fgets(line, sizeof(line), file)) {
        handle_mul(line, &is_enabled, &total);

        if (strstr(line, "do()")) {
            is_enabled = true;
        }
        else if (strstr(line, "don't()")) {
           is_enabled = false;
        }
    }

    fclose(file);

    printf("Final Total Result: %d\n", total);
}

int main(void) {
    solve("2024/day03/data/example.txt");
    solve("2024/day03/data/data.txt");
    return EXIT_SUCCESS;
}
