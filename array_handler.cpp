#include <iostream>
#include "array_handler.h"


void ArrayHandler::generate_array(int *arr, int size){
  // generate random integers in some range and put them in the array
  for(int i=0; i< size; i++){
    arr[i] = std::rand(); // Random number to be put
  }
}

void ArrayHandler::generate_simple_array(int *arr, int size){
  // generate random integers in some range and put them in the array
  for(int i=0; i< size; i++){
    arr[i] = size-i; // Random number to be put
  }
}

void ArrayHandler::print_array(int *arr, int size){
  std::cout << "[";
  if(size < 10){
    for(int i=0; i<size; i++){
      std::cout << arr[i];
      if(i!=size-1){
        std::cout << ", ";
      }
    }
  }else{
    std::cout << arr[0] << ", ";
    std::cout << arr[1] << ", ";
    std::cout << "..., ";
    std::cout << arr[size-2] << ", ";
    std::cout << arr[size-1];
  }
  std::cout << "]" << std::endl;
}
