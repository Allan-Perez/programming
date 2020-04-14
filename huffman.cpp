#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

void count_characters(string m, vector<pair<char,int>>& count);
void build_heap(struct HHeap&, vector<pair<char,int>>&);


struct Node{
  int weight;
  char character;

  struct Node* left;
  struct Node* right;

};

typedef struct HHeap{
  struct vector<pair<Node, Node>> nodes_arr;
  // Vector of 2 nodes have the nodes of the heap
  // The first element (0) will be the lowest weight, and the 
  // the first Node of the second element(1) will be the sum
  // of the two Nodes of the element above, and the spare node
  // will be the "inserted" one.
public:
  void getCharacterCodeWord(int idx, char c, vector<bool>& codeword){
    // To get the codeword, start from the first node (first node of
    // last element in nodes_arr), and each right choice is 1, and
    // each left choice is 0.
    int cidx = nodes_arr.size() - idx - 1;
    
    if(nodes_arr[cidx].first.character == c){
      // if character reached, add 0 and finish search
      codeword.push_back(0);
      return; 
    } else if(nodes_arr[cidx].second.character == c){
      codeword.push_back(1);
      return;
    } else {
      if(cidx== nodes_arr.size()-1){
        cout << "Reached end of heap and the character was not found." << endl;
        return;
      }
      codeword.push_back(1); // Effectively choose the second node (right node) to keep looking
      getCharacterCodeWord(idx+1, c, codeword);
    }
    
    
  }
  void newNode(char c, int w){
    // if there's a space to fill in the current height, fill it
    // and create next el with the node being the sum of the two previous
    if(!isElementFilled(nodes_arr.back())){
      pair<Node, Node> el = nodes_arr.back();
      nodes_arr.pop_back();

      Node new_node;
      pair<Node, Node> prev_el = nodes_arr.back();
      new_node.weight = w;
      new_node.character = c;
      new_node.left = &prev_el.second;
      new_node.right = &prev_el.first;

      if(el.first.weight == NULL){
        el.first = new_node;
      }else{
        el.second = new_node;
      }
      nodes_arr.push_back(el);
      addSummingNode();
    }else{
      cout << "Can't add a node in an unitialized heap. Sorry!" << endl;
    }
    
  }
  void initializeHeap(Node nodeLeft, Node nodeRight){
    if(nodes_arr.size() != 0){
      cout << "Cannot initialize an initialized heap." << endl;
    }
    pair<Node, Node> new_el;
    new_el.first = nodeRight;
    new_el.second = nodeLeft;
    nodes_arr.push_back(new_el);    
    addSummingNode();
  }

  void printHeap(){
    cout << "The heap: " << endl;
    for(int i=0; i< nodes_arr.size(); i++){
      cout << nodes_arr[i].first.character << " " << nodes_arr[i].first.weight << endl;
      cout << nodes_arr[i].second.character << " " << nodes_arr[i].second.weight << endl;
      cout << endl;

    }
  }
  
private:
  bool isElementFilled(pair<Node, Node>& el){
    return el.first.weight != NULL && el.second.weight != NULL;
  }
  void addSummingNode(){
    // To be called only after adding a new node. If the previous node is not filled, error.
    // node.first is always summing node (apart from last character).
    if(!isElementFilled(nodes_arr.back())){
      cout << "Internal Error. Tried to add summing node without filling previous element of Heap." << endl;
      return;
    }
    Node sum;
    pair<Node, Node> pre = nodes_arr.back();
    sum.weight = pre.first.weight + pre.second.weight;
    sum.left  = &pre.second;
    sum.right = &pre.first;
    sum.character = NULL;
    pair<Node, Node> new_el;
    Node null;
    null.weight = NULL;
    new_el.first = sum;
    new_el.second = null;
    nodes_arr.push_back(new_el);
  }
};


int main(int argv, char ** argc){
  if(argv < 2){
    cout << "I need a message to encode." << endl;
    return 1;
  }
  string message = argc[1];
  vector<pair<char, int>> elements;

  count_characters(message, elements);
  // Todo: build the huffman tree from elements pair vector
  // Reverse sort by int element in pair vectors.
  // Change: Needed to build heap, not tree. 
  // From that vector, build the tree.
  // Then output the characters and the codeword. E.g.
  // a 0
  // b 10
  // c 110
  // d 1110
  // ...
  HHeap heap;
  string to_compress = "abcaadbbbedd";

  build_heap(heap, elements);
  cout << "Elements: " << endl;
  for(int i=0 ; i<elements.size(); i++){
    cout << elements[i].first << " "<< elements[i].second << endl;
  }
  cout << "Heap build" << endl;
  heap.printHeap();

  vector<bool> cw;
  heap.getCharacterCodeWord(0,'a',cw);
  cout << "Codeword of a: <" ;
  for(int i=0; i<cw.size(); i++){
    int c = (cw[i])?1:0; 
    cout << c << ", ";
  }
  cout << ">" << endl;
  return 0;
  

}

void build_heap(struct HHeap& h, vector<pair<char, int>>& el){
  // Reverse sort by int element. First element is the one with lowest frequency
  sort(el.rbegin(), el.rend(), [](const pair<char, int>& a, const pair<char, int>& b){
    return a.second < b.second;
  });
  Node first;
  Node second;
  first.character = el[0].first;
  first.weight = el[0].second;
  second.character = el[1].first;
  second.character = el[1].second;
  h.initializeHeap(first, second);

  for(int i=2; i<el.size(); i++){
    h.newNode(el[i].first, el[i].second);
  }
}

void count_characters(string m, vector<pair<char,int>>& count){
  sort(m.begin(), m.end());
  for(int i=0; i< m.length(); i++){ 
    cout << endl;
    if(count.empty()){
      cout << "doing empty" << m[i];
      auto p = make_pair(m[i], 1);
      count.push_back(p);
      continue;
    }
    if(count.back().first != m[i]){
      cout << "new count: "<< m[i];
      auto p = make_pair(m[i], 1);
      count.push_back(p);
    }else{
      cout << "plus one count: "<< m[i];
      auto _p = count.back();
      count.pop_back();
      int char_count = _p.second + 1;
      auto p  = make_pair(m[i], char_count);
      count.push_back(p);
    }
    cout << endl;
  }
}
