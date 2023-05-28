#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int n, i, j, temp;

  printf("Enter the number of elements to be sorted: ");
  scanf("%d", &n);

  int arr[n];

  // Seed the random number generator
  srand(time(NULL));

  // Generate 'n' random numbers between 1 and 100
  printf("Generating %d random numbers...\n", n);
  for (i = 0; i < n; i++) {
    arr[i] = rand() % 100 + 1;
  }

  // Perform bubble sort
  for (i = 0; i < n-1; i++) {
    for (j = 0; j < n-i-1; j++) {
      if (arr[j] > arr[j+1]) {
        temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }

  // Print sorted array
  printf("Sorted array:\n");
  for (i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }

  // Save sorted array to file
  FILE *fp;
  fp = fopen("sorted_numbers.txt", "w");

  if (fp == NULL) {
    printf("Unable to create file.\n");
    return 1;
  }

  fprintf(fp, "Sorted array:\n");
  for (i = 0; i < n; i++) {
    fprintf(fp, "%d ", arr[i]);
  }

  fclose(fp);

  return 0;
}
