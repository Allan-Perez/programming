#include <iostream>
#include <chrono>
#include <stdlib.h>

using namespace std;

int algo2(int*, int);
int algo3(int*, int);
int generate_array(int*, int);
void print_array(int*, int);

int main(void){
  // Find the maximum value of the sum of the elements of an array of integers
  int size_arr = rand() + 10;
  int arr[size_arr];

  generate_array(arr, size_arr);
  // print_array(arr, size_arr); 
  
  auto start_1 = chrono::high_resolution_clock::now(); 
  int ans_1 = algo2(arr, size_arr);
  auto stop_1 = chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::micro> duration_1 = stop_1-start_1;
  cout << "Algo 1 took " << duration_1.count() << " us" << endl;
  cout << "Output of Algo 1 " << ans_1 << endl;


  auto start_2 = chrono::high_resolution_clock::now(); 
  int ans_2= algo3(arr, size_arr);
  auto stop_2 = chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::micro> duration_2 = stop_2-start_2;
  cout << "Algo 2 took " << duration_2.count() << " us" << endl;
  cout << "Output of Algo 2 " << ans_2 << endl;


  return 0;
}


int algo2(int *arr, int size){
  // O(n**2). Same as above, but compute the sum as it iterates.
  int best = 0;
  for(int i=0; i<size; i++){
    int sum =0;
    for(int j=i; j<size; j++){
      sum += arr[j];
      best = (best<sum)?sum:best;
    }
  }

  return best;
}

int algo3(int *arr, int size){
  // O(n). Iterate through all of the elements once, keep the sum
  // and take the maximum between current sum and prev sum at each
  // iteration
  int sum=0;
  int best=0;
  for(int i=0; i<size; i++){
    sum = ((sum+arr[i])<arr[i])?arr[i]:sum+arr[i];
    best = (best<sum)?sum:best;
  }
  return best;
}

int generate_array(int *arr, int size){
  // generate random integers in some range and put them in the array
  for(int i=0; i< size; i++){
    arr[i] = rand(); // Random number to be put
  }
  return 0;
}

void print_array(int *arr, int size){
  for(int i=0; i<size; i++){
    cout << arr[i] << endl;
  }
}
