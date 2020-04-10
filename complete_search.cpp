#include <iostream>
#include <vector>

using namespace std;

void search(int, int, vector<int>, vector<vector<int>>&);
void search_bitwise(int, vector<vector<int>>&);
void search_permutation(int, vector<bool>&, vector<int>&, vector<vector<int>>&);
void print_vector_vector(vector<vector<int>>);
void queen_backtracking(int, int, vector<bool>&, vector<bool>&, vector<bool>&, int&);

int main(int argv, char **argc){
  // Complete search: generate all possible solutions and use brute-force.o
  // Then can find the specific solution or count the number of solutions.
  // If complete search is too time/resources-consuming, then greedy serch
  // or dynamic programming is a better way to go.

  // Problem 1: Generate all possible subsets (powerset)
  if(argv < 2) return 1;
  vector<int> sub;
  vector<vector<int>> pset;

  search(0, atoi(argc[1]), sub, pset);
  //print_vector_vector(pset);

  vector<vector<int>> pset2;
  //search_bitwise(atoi(argc[1]), pset2);
  //print_vector_vector(pset2);
  
  // Problem 2: Generate all possible permutations
  int size = atoi(argc[1]);
  vector<bool> chosen(size);
  vector<int> permutation;
  vector<vector<int>> permutations;
  search_permutation(size, chosen, permutation, permutations);
  //print_vector_vector(permutations);

  // Problem 3: Backtracking.
  // An algorithm that goes through all the solutions to a problem.
  // For example, in the classic queen chess problem, placing n queens in
  // an nxn board, the algorithm would try to find a solution by firstly 
  // placing a random queen in the first row, and then check the possible 
  // legal places where to put the second queen, and so on. 
  int n_rows = atoi(argc[1]);
  int n_diagonals = n_rows+n_rows;
  vector<bool> col(n_rows);  //////// keep track of columns
  vector<bool> diag1(n_diagonals); // keep track of left to right diagonals
  vector<bool> diag2(n_diagonals); // keep track of right to left diagonals
  int number_of_solutions = 0;
  int start_looking_from = 0;
  queen_backtracking(n_rows, start_looking_from, col, diag1, diag2, number_of_solutions); 
  cout << "There're " << number_of_solutions << " possible solutions." << endl;

}
void queen_backtracking(int n, int p_row, vector<bool> &col, vector<bool> &diag1, vector<bool> &diag2, int &n_solutions){
  // p_row should be first 0, so that it can start looking for a solution
  if(n == p_row) {
    n_solutions++;
    return;
  }
  for(int i=0; i<n; i++){
    if(col[i] || diag1[i+p_row] || diag2[i-p_row+n-1]) continue;
    col[i] = diag1[i+p_row] = diag2[i-p_row+n-1] = 1; // occupied
    queen_backtracking(n, p_row + 1, col, diag1, diag2, n_solutions); // after occupation, call next row (next queen)
    col[i] = diag1[i+p_row] = diag2[i-p_row+n-1] = 0; // after solution was not/found, refresh and keep looking.
  }
}

void search_permutation(int n, vector<bool>& chosen, vector<int>& p, vector<vector<int>>& ps){
  if(p.size()==n){
    ps.push_back(p);
  } else {
    for(int i=0; i<n; i++){
      if(chosen[i]) continue;
      chosen[i] = true;
      p.push_back(i);
      search_permutation(n, chosen, p, ps);
      chosen[i] = false;
      p.pop_back();
    }
  }
}

void search(int k, int n, vector<int> subset, vector<vector<int>> &pset){
  if(k == n){
    pset.push_back(subset);
  } else {
    search(k+1, n, subset, pset);
    subset.push_back(k);
    search(k+1, n, subset, pset);
    subset.pop_back();
  }
}

void search_bitwise(int n, vector<vector<int>> &pset){
  for(int i=0; i<(1<<n); i++){
    vector<int> s;
    for(int j=0; j<n; j++){
      if(i&(1<<j)) s.push_back(j);
    }
    pset.push_back(s);
  }
}

void print_vector_vector(vector<vector<int>> vv){
  for(int i=0; i<vv.size(); i++){
    cout << "{";
    for(int j=0; j<vv[i].size(); j++){
      cout << vv[i][j] << ", ";
    }
    cout << "}" << endl;
  }
}
