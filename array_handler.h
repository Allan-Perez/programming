#ifndef ARRAY_HANDLER_H
#define ARRAY_HANDLER_H
class ArrayHandler{
  public:
    static void generate_array(int* arr, int size);
    static void generate_simple_array(int* arr, int size);
    static void print_array(int* arr, int size);

  private:
    ArrayHandler(){}
};
#endif
