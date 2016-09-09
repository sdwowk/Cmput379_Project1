#include "Mergesort.h"
#include "dynamicArray.h"

/***
 Dynamic Array is based mostly off of https://www.happybearsoftware.com/implementing-a-dynamic-array

 ***/
void dArrayInit(dynamicArray* dynamicArray){
  dynamicArray->size = 0;
  dynamicArray->capacity = 500;
  dynamicArray->data = malloc(sizeof(int) * dynamicArray->capacity);
}

void dArrayDoubleCapacity(dynamicArray* dynamicArray){
  if(dynamicArray->size >= dynamicArray->capacity){
    dynamicArray->capacity *= 2;
    dynamicArray->data = realloc(dynamicArray->data, sizeof(int) * dynamicArray->capacity);
  }
    
}

void dArrayAdd(dynamicArray* dynamicArray, int value){
  dArrayDoubleCapacity(dynamicArray);
  dynamicArray->data[dynamicArray->size] = value;
  dynamicArray->size +=1;
}

int dArrayGet(dynamicArray* dynamicArray, int index){
  int value = dynamicArray->data[index];
  return value;
}

void dArrayFree(dynamicArray* dynamicArray){
  free(dynamicArray->data);
}
