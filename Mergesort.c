#include "Mergesort.h"
#include "dynamicArray.h"

int main(int argc, char *argv[]){
  int number_file;
  dynamicArray fileAsInts;
  FILE* fileStream;
  int tempNumber;
  int* unSortedArray;
  int* dest;

  //initialize dynamic array
  dArrayInit(&fileAsInts);
  
  if((number_file = open(argv[1], O_RDWR))<0){
    perror("error opeing file");
  }

  fileStream = (FILE*)fdopen(number_file, "r");
  
  while(fscanf(fileStream, "%d", &tempNumber) == 1){
    dArrayAdd(&fileAsInts, tempNumber);
  }

  unSortedArray = malloc(sizeof(int)*fileAsInts.size);

  if((dest = mmap(0, sizeof(int)*((size_t)fileAsInts.size), PROT_WRITE|PROT_READ, MAP_ANONYMOUS|MAP_SHARED, -1, 0)) == MAP_FAILED){
    perror("memory map error");
  }
  int i;
  for(i = 0; i < fileAsInts.size; i++){
    unSortedArray[i] = fileAsInts.data[i];
  }
  
  memcpy(dest, unSortedArray, (fileAsInts.size)*sizeof(int));

  printf("\n");
  printf("Input Numbers:\n");
  /* Write INPUT Numbers HERE */

  for(i = 0; i < fileAsInts.size; i++){
    printf(" %d", dest[i]);
  }
  
  printf("\n");

 
  mergesort(dest, fileAsInts.size);
  printf("Sorted Numbers:\n");
  /* Write OUTPUT Numbers HERE */
  
  int j;
  for(j = 0; j < fileAsInts.size; j++){
    printf(" %d", dest[j]);
  }
  
  fclose(fileStream);
  close(number_file);
  dArrayFree(&fileAsInts);
  munmap(dest, sizeof(int)*((size_t)fileAsInts.size));
  free(unSortedArray);

  return 0;
}

void mergesort(int* unSortedArray,int iend){
  splitAndMerge(unSortedArray,0,iend);
    
}

void splitAndMerge(int* unSortedArray,int iStart, int iend){
  int leftChildID, rightChildID;

  if((iend - iStart) < 2){
    /* Gotta return to parent thread */
    return;
  }
  
  int iMiddle = (iStart + iend)/2;
  leftChildID = fork();
  if(leftChildID == 0){
    splitAndMerge(unSortedArray, 0, iMiddle);
    exit(0);
  }
  waitpid(leftChildID, NULL, 0);
  
  rightChildID = fork();
  
  if(rightChildID == 0){
    splitAndMerge(unSortedArray, iMiddle, iend);
    exit(0);
  }
  
  waitpid(rightChildID, NULL, 0);
  
  merge(unSortedArray, iStart, iMiddle, iend);

  
}

void  merge(int* sortedArray, int iStart,int iMiddle,int iend){
  int* unSortedArray;
  unSortedArray = malloc((iend+1)*sizeof(int));
  memcpy(unSortedArray, sortedArray, (iend+1)*sizeof(int));

  int unsortedIndex = iStart;
  int workIndex = iMiddle;
  int i;
  for(i = iStart; i < iend; i++){
    if(unsortedIndex < iMiddle && (workIndex >= iend || unSortedArray[unsortedIndex] <= unSortedArray[workIndex])){
      sortedArray[i] = unSortedArray[unsortedIndex];
      unsortedIndex++;
    }else{
      sortedArray[i] = unSortedArray[workIndex];
      workIndex++;
    }
  }

  free(unSortedArray);
}
