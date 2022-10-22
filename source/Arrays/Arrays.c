// Quick sort in C
#include <stdio.h>
#include <stdlib.h>
#include "Arrays.h"

//------------------QuickSort--------------------------------------------

// function to swap elements
void swap(int* a, int* b) { //change the contents of memory address
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {
  
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void array_quicksort(int array[], int low, int high) {
  if (low < high) {
    
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);
    
    // recursive call on the left of pivot
    array_quicksort(array, low, pi - 1);
    
    // recursive call on the right of pivot
    array_quicksort(array, pi + 1, high);
  }
}
//the quicksort code is from: https://www.programiz.com/dsa/quick-sortt that helped with optimizing sorting an array in the other structs
//-----------------BubbleSort--------------------------------------------

void array_bubblesort(int* arr, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) //for every element (last one already sorted, thats why -1)
    {
        // Last i elements are already in place
        for (j = 0 ; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1]) //swap woth the next if current greater
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }  
}