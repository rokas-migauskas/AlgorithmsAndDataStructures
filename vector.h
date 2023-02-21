//
// Created by Rokas Migauskas on 2023-02-13.
//
#include <stdio.h>
#include <stdlib.h>
#ifndef MAIN_C_VECTOR_H

struct Vector{
    int *data;
    int capacity;
    int size;
};
typedef struct Vector Vector;

Vector createVector(int size, int capacity);

void fillVector(Vector vector);

void insertElementAt(Vector *vector, int element, int index);

void deleteElementAt(Vector *vector, int index);

void printVector(Vector vector);

void addElement(Vector *vector, int element);

void setElementAt(Vector *vector, int element, int index);

void removeAllElements(Vector *vector);

int isVectorEmpty(Vector vector);

int elementAt(Vector vector, int index);


#define MAIN_C_VECTOR_H

#endif //MAIN_C_VECTOR_H
