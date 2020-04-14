#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

const int INF = 99999999;

int coins1(int, vector<int>&);
int coins2(int x, vector<int>& C, bool* ready, int* value);

int main(int argv, char** argc){
  // Dynamic programming is a way of solving a computation problem with optimal solutions.
  // Other ways are complete search and greedy algorithms for example, but either of those
  // fail to perform optimally for every input set. For example, complete search works 
  // but takes too much resources (it basically looks for every possibility). In order to 
  // make it useful, we have to manually prune the search by setting some hard rules 
  // of when to stop searching. Greedy algorithms, in the other hand, always look for the
  // biggest immediate reward, even if its the worst decision. 
  // This mathematical optimization tool (Dynamic Programming) is based on these two methods
  // and by splitting the problem into subproblems that are attainable (divide et impera).
  // Generally speaking, DP has two uses:
  // -- Finding an optimal solution (numerically minimum or maximum)
  // -- Counting the number of solutions (counting)

  // In this example, we're going to solve the coin problem for the general case of 
  // any given set of coins. 
  // The dynamic programming approach for this problem is a recursive approach, where it 
  // tries every possible sum of coins, like a brute force algorithm. But DP is efficient
  // because it calculates the answer to a problem only once ("memory").
  // Essentially, by storing the results from the subproblems (assuming that the main
  // problem has an optimal substructure), we bring the time complexity from exponential
  // to polynomial 
  // For the coin problem, the intuition is the following: Let the optimal amount of coins
  // from a set C and the sum to fulfill be x. Then, the DP approach is based on the principle
  // that we can store the subproblems' optimal solutions.
  // Let sol(x) be the minimum number of coins needed. Ten let sol(x) will be calculated from sol(x-c)
  // for every possible value of c \in C. Therefore, a possible solution psol(x) can be
  // represented as psol(x) = psol(x-c)+1 (+1 because using up "c" is already using 1 coin).
  // Therefore, the optimal solution sol(x) = min_{c \in C} (psol(x-c)+1). We do this computationally
  // By trying the possible solutions, but storing the results and comparing new trials with 
  // the best answer so far. 
  vector<int> C{1, 3, 4};
  int x = 10;
  
  // Approach 1 (less efficient) but work for any C
  int sol = coins1(x, C);
  cout << "Solution: " << sol << endl;

  // It's obvious that using a loop inside a recursive function that executes by default is not
  // efficient, rapidly leading to exponential complexities. 
  // The key in efficient dynamic programming is in memoization: remembering the already visited solutions.
  // This is achieved by storing the values of the function in an array, to compute their recursion only once.
  // Approach 2 (memoization)
  bool ready[x]; // Stores whether sol(x) has already been calculated
  int  value[x]; // Contains the value of the calculated sol(x).
  int sol2 = coins2(x, C, ready, value);
  cout << "Solution2: " << sol2 << endl;


}

int coins1(int x, vector<int>& C){
  // Complexity: O(c^c)(?)
  if(x==0) return 0;
  if(x<0)  return INF;
  int sol = INF;
  for(int c : C){
    sol = min(sol, coins1(x-c, C)+1);
  }
  return sol;
}

int coins2(int x, vector<int>& C, bool* ready, int* value){
  // Complexity: O(c^c)(?)
  if(x==0) return 0;
  if(x<0)  return INF;
  if(ready[x]) return value[x];
  int sol = INF;
  cout << "x " << x << endl;
  for(int c : C){
    cout << "sol c " << x << " " << c << " NEXT X SHOULD BE " << x-c << endl;
    sol = min(sol, coins2(x-c, C, ready, value)+1);
  }
  ready[x] = true;
  value[x] = sol;
return sol; }
