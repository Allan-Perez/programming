#include <iostream>

template<typename T>
typedef struct node{
  T value;
  struct node* next;
};
template<typename T>
void print_linked_list(node<T>* list);
template<typename T>
void free_linked_list(node<T>* list);


int main(){
  node<int> *list = NULL;

  node<int> *n0 = (node<int>*)malloc(sizeof(node<int>));
  if(n0 != NULL){
    n0->value = 2;
    n0->next  = NULL;
  }
  list = n0;

  n0 = (node<int>*)malloc(sizeof(node<int>));
  if(n0 != NULL){
    n0->value = 3;
    n0->next = NULL;
  }
  list->next = n0;

  n0 = (node<int>*)malloc(sizeof(node<int>));
  if(n0 != NULL){
    n0->value = 4;
    n0->next = NULL;
  }
  list->next->next = n0;
  
  print_linked_list(list);
  free_linked_list(list);

  return 0;
}

template<typename T>
void print_linked_list(node<T>* list){
  std::cout << "[";
  for(node<T> *t = list; t != NULL; t = t->next){
    std::cout << t->value;
    std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

template<typename T>
void free_linked_list(node<T>* list){
  while(list != NULL){
    node<T>* tmp = list->next;
    free(list);
    list = tmp;
  }
}
