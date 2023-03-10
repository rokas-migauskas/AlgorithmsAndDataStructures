//
// Created by Rokas Migauskas
//
#include "functions.h"


int main()
{
    int arr[MAX_SIZE];
    int n = readIntegersFromFile(arr);
    separateArray(arr, n);
    return 0;
}
