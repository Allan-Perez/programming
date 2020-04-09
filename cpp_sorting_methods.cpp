#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
#include "array_handler.h"

template<typename T>
void print_vector(std::vector<T>);
struct vect3d{
  float x, y, z;

  bool operator<(const vect3d &v) const{
    float my_mag = x*x + y*y + z*z;
    float her_mag = v.x*v.x + v.y*v.y + v.z*v.z;
    return my_mag < her_mag;
  }

};

int main(void){
  std::vector<int> l{5, 4, 3, 2, 1};
  std::cout << "The initial vector ";
  print_vector(l);
  std::sort(l.begin(), l.end()); 
  print_vector(l);

  int s = 10000;
  int arr[s];
  ArrayHandler::generate_array(arr, s);
  std::cout << "The initial array ";
  ArrayHandler::print_array(arr, s);
  std::sort(arr, arr + s);
  std::cout << "The final array ";
  ArrayHandler::print_array(arr, s);
  
  std::vector<std::tuple<int, int>> vp;
  vp.push_back({1,2});
  vp.push_back({3,3});
  vp.push_back({3,4});
  vp.push_back({3,5});
  vp.push_back({4,3});

  std::sort(vp.begin(), vp.end());
  std::cout << "The vector " << get<0>(vp.at(3)) << std::endl;

  // User defined structures - sort function
  vect3d v1;
  v1.x = 1.0;
  v1.y = 2.0;
  v1.z = 3.0;
  vect3d v2;
  v2.x = 4.0;
  v2.y = 5.0;
  v2.z = 6.0;
  vect3d v[2];
  v[0] = v1;
  v[1] = v2;
  std::sort(v, v + 2);
  std::cout << "The custom vect " << v[1].x;


}

template<typename T>
void print_vector(std::vector<T> l){
  std::cout << "[ ";
  for(int i=0; i < l.size(); i++)
    std::cout << l.at(i) << ", ";
  std::cout << "]" << std::endl;
}
