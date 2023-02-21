//
// Created by Rokas Migauskas on 2023-02-13.
//

#include "vector.h"



Vector createVector(int size, int capacity){
    if(size>capacity){
        printf("Vector size exceeds capacity\n");
        exit(1);
    }
    Vector temp;
    temp.size=size;
    temp.capacity=capacity;
    temp.data= malloc(capacity*sizeof(int));
    return temp;
}

void fillVector(Vector vector){
    for(int i=0; i<vector.size; ++i){
        vector.data[i]=i+1;
    }
}

void insertElementAt(Vector *vector, int element, int index){
    vector->size++;
    if(vector->size>vector->capacity){
        vector->data=(int *)realloc(vector->data, (vector->size)*2*sizeof(int));
        vector->capacity=vector->size*2;
    }
    if(vector->data==NULL){
        printf("Could not reallocate memory in insertElementAt function\n");
        exit(1);
    }
    for(int i=vector->size;i>index;--i){
        vector->data[i]=vector->data[i-1];
    }
    vector->data[index]=element;
}

void deleteElementAt(Vector *vector, int index){
    if(index>vector->size-1){
        printf("Invalid index in deleteElementAt function\n");
        exit(1);
    }
    vector->size--;
    for(int i=index; i<vector->size-1; ++i){
        vector->data[i]=vector->data[i+1];
    }
    if(vector->size<vector->capacity/2){
        vector->data=(int *)realloc(vector->data, (vector->size*sizeof(int))/2);
    }
    if(vector->data==NULL){
        printf("Could not reallocate memory in deleteElementAt function\n");
        exit(1);
    }
}

void printVector(Vector vector){
    for(int i=0; i<vector.size; ++i){
        printf("%d. %d\n", i+1, vector.data[i]);
    }
    printf("\n");
}

void addElement(Vector *vector, int element){
    vector->size++;
    if(vector->size>vector->capacity){
        vector->data=(int *)realloc(vector->data, vector->size*2*sizeof(int));
        vector->capacity=vector->size*2;
    }

    if(vector->data==NULL){
        printf("Could not reallocate memory in addElement function\n");
        exit(1);
    }
    vector->data[vector->size-1]=element;
}

void setElementAt(Vector *vector, int element, int index){
    vector->data[index]=element;
}

void removeAllElements(Vector *vector){
    free(vector->data);
    vector->size=0;
}

int isVectorEmpty(Vector vector){
    if(vector.size==0){
        return 1;
    }
    return 0;
}

int elementAt(Vector vector, int index){
    if(index>vector.size-1){
        printf("Invalid index in elementAt function\n");
        exit(1);
    }
    return vector.data[index];
}