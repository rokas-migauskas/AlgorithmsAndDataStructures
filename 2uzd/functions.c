//
// Created by Rokas Migauskas
//
#include "functions.h"

// Raises given base to exponent exp
int power(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        result *= base;
        exp--;
    }
    return result;
}
// Separates integer array into two sub-arrays with the closest possible sum
void separateArray(int arr[], int n) {
    int i, j;
    int minDiff = INT_MAX;
    int minIndex = 0;

    int numCombinations = power(2, n);

    for (i = 0; i < numCombinations; i++) {
        int sum1 = 0, sum2 = 0;
        int temp = i;
        for (j = 0; j < n; j++) {
            if (temp % 2 == 1)
                sum2 += arr[n - 1 - j];
            else
                sum1 += arr[n - 1 - j];
            temp /= 2;
        }
        int diff = abs(sum1 - sum2);
        if (diff < minDiff) {
            minDiff = diff;
            minIndex = i;
        }
    }

    printf("Minimum difference between two subarrays is: %d\n", minDiff);

    printf("First subarray: ");
    for (i = 0; i < n; i++) {
        if (minIndex / power(2, n - 1 - i) % 2 == 0)
            printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Second subarray: ");
    for (i = 0; i < n; i++) {
        if (minIndex / power(2, n - 1 - i) % 2 == 1)
            printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function used for input, asks for file input and reads all integers until end of file
int readIntegersFromFile(int arr[]) {
    char filename[100];
    int count = 0;
    printf("Enter filename: \n");
    scanf("%s", filename);
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: cannot open file %s\n", filename);
        exit(1);
    }
    while (fscanf(fp, "%d", &arr[count]) != EOF) {
        count++;
        if (count >= MAX_SIZE) {
            printf("Error: array size exceeds maximum allowed\n");
            exit(1);
        }
    }
    fclose(fp);
    return count;
}

