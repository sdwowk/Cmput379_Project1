typedef struct{
  int size;
  int capacity;
  int* data;
} dynamicArray;

void dArrayInit(dynamicArray* dynamicArray);
void dArrayDoubleCapacity(dynamicArray* dynamicArray);
void dArrayAdd(dynamicArray* dynamicArray, int value);
int dArrayGet(dynamicArray* dynamicArray, int index);
void dArrayFree(dynamicArray* dynamicArray);
