#include <iostream> 
#include <algorithm>
#include <string>
#include "array_handler.h" 

int binary_search(int*, int, int, int);

int main(int argc, char **argv){
  // Binary search: the motivation is to have better than O(n)
  // This is possible for a sorted array, because the magnitude
  // of each element guides the search. Search O(log n).
  if(argc < 3){
    std::cout << "Sorry mate, I need the length of the array and target." << std::endl;
    return 1;
  }
  int s = std::atoi(argv[1]);
  int arr[s];
  ArrayHandler::generate_simple_array(arr, s);
  std::sort(arr, arr+s);
  std::cout << "Current arr: ";
  ArrayHandler::print_array(arr, s);

  int target = std::atoi(argv[2]);
  std::cout << "Looking for " << target << std::endl;
  int idx = binary_search(arr, 0, s, target);
  std::cout << "The index: " << idx << std::endl;

}

int binary_search(int *arr, int a, int b, int target){
  int k = ((b+a % 2) == 0 || b+a == 1)?(b+a)/2: (b+a+1)/2;
  std::cout << "Parms " << a << " " << k << " " << b << " " << std::endl;
  std::cout << "B " << arr[k] << " and " << target << std::endl;
  
  if(arr[k] == target) return k;
  else if(a == b) return -1;
  else if(arr[k]<target) return binary_search(arr, k, b, target);
  else return binary_search(arr, a, k, target);
}
