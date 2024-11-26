#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WIDTH 1000
#define HEIGHT 1000
#define SOURCE_X 500
#define SOURCE_Y 0

// Grid elements
#define AIR '.'
#define ROCK '#'
#define SAND 'o'
#define SOURCE '+'

void initializeGrid(char grid[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = AIR;
        }
    }
    grid[SOURCE_Y][SOURCE_X] = SOURCE;
}

// Parse a rock path and draw it on the grid
void drawRockPath(char grid[HEIGHT][WIDTH], const char *path) {
    int x1, y1, x2, y2;
    char *pathCopy = strdup(path);
    char *token = strtok(pathCopy, " -> ");
    sscanf(token, "%d,%d", &x1, &y1);

    while ((token = strtok(NULL, " -> ")) != NULL) {
        sscanf(token, "%d,%d", &x2, &y2);

        if (x1 == x2) { // Vertical line
            for (int y = y1 < y2 ? y1 : y2; y <= (y1 > y2 ? y1 : y2); y++) {
                grid[y][x1] = ROCK;
            }
        } else { // Horizontal line
            for (int x = x1 < x2 ? x1 : x2; x <= (x1 > x2 ? x1 : x2); x++) {
                grid[y1][x] = ROCK;
            }
        }

        x1 = x2;
        y1 = y2;
    }

    free(pathCopy);
}

// Simulate falling sand
int simulateSand(char grid[HEIGHT][WIDTH]) {
    int sandUnits = 0;

    while (true) {
        int x = SOURCE_X;
        int y = SOURCE_Y;

        while (true) {
            if (y + 1 >= HEIGHT || x - 1 < 0 || x + 1 >= WIDTH) {
                // Sand falls into the abyss
                return sandUnits;
            }

            if (grid[y + 1][x] == AIR) {
                // Move down
                y++;
            } else if (grid[y + 1][x - 1] == AIR) {
                // Move down-left
                y++;
                x--;
            } else if (grid[y + 1][x + 1] == AIR) {
                // Move down-right
                y++;
                x++;
            } else {
                // Sand comes to rest
                grid[y][x] = SAND;
                sandUnits++;
                break;
            }
        }
    }
}

// Read paths from a file
void readPathsFromFile(const char *filename, char **paths, int *pathCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    *pathCount = 0;

    while (fgets(line, sizeof(line), file)) {
        paths[*pathCount] = strdup(line);
        (*pathCount)++;
    }

    fclose(file);
}

// Solve the problem for a given file
void solve(const char *filename) {
    char grid[HEIGHT][WIDTH];
    initializeGrid(grid);

    // Read rock paths
    char *paths[100];
    int pathCount = 0;
    readPathsFromFile(filename, paths, &pathCount);

    // Draw rock paths
    for (int i = 0; i < pathCount; i++) {
        drawRockPath(grid, paths[i]);
        free(paths[i]); // Free allocated memory for path
    }

    // Simulate sand and print result
    int sandUnits = simulateSand(grid);
    printf("File: %s, Units of sand at rest: %d\n", filename, sandUnits);
}

int main() {
    solve("2022/day14/data/example.txt");
    solve("2022/day14/data/data.txt");
    return 0;
}
