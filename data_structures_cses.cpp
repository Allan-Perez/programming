#include <iostream>
#include <vector>

int main(){
  // Dynamic arrays. Standard vectors are okay.
  std::vector<int> k(10,5);
  k.push_back(2);
  k.push_back(3);
  k.push_back(4);

  for(int i=0; i< k.size(); i++){
    std::cout << k[i] << std::endl;
  }

}
