#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int min, max, count, i;
    printf("Enter the minimum value: ");
    scanf("%d", &min);
    printf("Enter the maximum value: ");
    scanf("%d", &max);
    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &count);

    srand(time(NULL)); // seed the random number generator

    FILE *fp;
    fp = fopen("random_numbers.txt", "w"); // open file for writing

    for (i = 0; i < count; i++) {
        int num = (rand() % (max - min + 1)) + min; // generate random number
        fprintf(fp, "%d\n", num); // write to file
    }

    fclose(fp); // close file

    printf("%d random numbers generated and saved to file 'random_numbers.txt'.\n", count);

    return 0;
}
