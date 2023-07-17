#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int main() {
    FILE *file;
    int matrix[MAX_SIZE][MAX_SIZE];
    int numVertices, i, j;
    char filename[100];

    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    // Read the number of vertices
    fscanf(file, "%d", &numVertices);

    // Initialize the adjacency matrix with zeros
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            matrix[i][j] = 0;
        }
    }

    // Read the edges and populate the adjacency matrix
    while (!feof(file)) {
        int vertex1, vertex2;
        fscanf(file, "%d %d", &vertex1, &vertex2);
        matrix[vertex1][vertex2] = 1;
        matrix[vertex2][vertex1] = 1;
    }

    // Close the file
    fclose(file);

    // Print the adjacency matrix
    printf("Adjacency Matrix:\n");
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
