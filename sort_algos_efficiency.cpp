#include <iostream>
#include <chrono>
#include <cstdlib>
#include "array_handler.h"
using namespace std;

void bubble_sort(int*, int);
void merge_sort(int*, int, int);
void merge(int*, int, int, int);
void swap_subarrays(int*, int, int, int);
template<typename T>
void swap(T*, T*);
bool inversion(int, int);

int main(int argc, char* argv[]){
  if(argc < 2){
    cout << "Please, specify the length of the array." << endl;
    return 1;
  }
  int size = atoi(argv[1]);
  int arr[size];
  
  ArrayHandler::generate_array(arr, size);
  cout << "The inital array: ";
  ArrayHandler::print_array(arr, size);
  auto start_1 = chrono::high_resolution_clock::now(); 
  bubble_sort(arr, size);
  auto stop_1 = chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration_1 = stop_1-start_1;
  cout << "The final sorted array: ";
  ArrayHandler::print_array(arr, size);
  cout << "It took " << duration_1.count() << " ms" << endl;

  ArrayHandler::generate_simple_array(arr, size);
  cout << "The inital array: ";
  ArrayHandler::print_array(arr, size);
  auto start_2 = chrono::high_resolution_clock::now(); 
  merge_sort(arr, 0, size-1);
  auto stop_2 = chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration_2 = stop_2-start_2;
  cout << "The final sorted array: ";
  ArrayHandler::print_array(arr, size);
  cout << "It took " << duration_2.count() << " ms" << endl;


  return 0;
}

// O(n^2) sorting algo: bubble sort. Check for inversions.
void bubble_sort(int *arr, int arr_size){
  for(int i=0; i<arr_size; i++){
    for(int j=0; j<arr_size-1; j++){
      if( inversion(arr[j], arr[j+1]) ){
        swap(&arr[j], &arr[j+1]);
      }
    }  
  }
}

// O(n log n) sorting algo: merge sort.
// If an inversion happens, swap them. If not, continue.
void merge_sort(int *arr, int idx0, int idx1){
  if(idx0 < idx1){
    int k = idx0 + (idx1 - idx0)/2;
    merge_sort(arr, idx0, k);
    merge_sort(arr, k+1, idx1);
    merge(arr, idx0, k, idx1);
  }
  return;
}

void merge(int arr[], int l, int m, int r) { 
  int i, j, k; 
  int n1 = m - l + 1; 
  int n2 =  r - m; 

  /* create temp arrays */
  int L[n1], R[n2]; 

  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++) 
      L[i] = arr[l + i]; 
  for (j = 0; j < n2; j++) 
      R[j] = arr[m + 1+ j]; 

  /* Merge the temp arrays back into arr[l..r]*/
  i = 0; // Initial index of first subarray 
  j = 0; // Initial index of second subarray 
  k = l; // Initial index of merged subarray 
  while (i < n1 && j < n2) { 
      if (L[i] <= R[j]) { 
          arr[k] = L[i]; 
          i++; 
      } 
      else{ 
          arr[k] = R[j]; 
          j++; 
      } 
      k++; 
  } 

  /* Copy the remaining elements of L[], if there 
     are any */
  while (i < n1) { 
      arr[k] = L[i]; 
      i++; 
      k++; 
  } 

  /* Copy the remaining elements of R[], if there 
     are any */
  while (j < n2) { 
      arr[k] = R[j]; 
      j++; 
      k++; 
  } 
} 

// Useful functions
template<typename T>
void swap(T* el0, T* el1){
  T _ = *el0; 
  *el0 = *el1;
  *el1 = _;
  
}

bool inversion(int el0, int el1){
  // return true if inversion
  return el0>el1;
}
