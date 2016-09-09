#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

void mergesort(int* unSortedArray,int iend);
void splitAndMerge(int* unsortedArray,int iStart, int iend);
void  merge(int* sortedArray,int iStart,int iMiddle,int iend);
