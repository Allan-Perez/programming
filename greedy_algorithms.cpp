#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void greedy_coins(int, vector<int>&, vector<int>&);
void print_vector(vector<int>);
void greedy_schedule(vector<vector<int>>& events, vector<int> &scheadule);

int main(int argv, char **argc){
  // In a nutshell: Choose the apparently best option at each step. 
  // Optimise for short term reward. 
  // Directly tries to construct its final solution. It may be efficient.
  // Problem: Looks for local optima. Maybe local optima is not global. 

  // Example: Coin problem. Given a set of coins {c1, c2, ..., ck}, find 
  // the minimum number of coins needed to get a sum of money n.
  // The greedy algorithm finds a solution only for canonical currencies
  // like EUR or USD that have a standard set of coins. But the algo
  // doest yield the optimal solution or even cant deliver a valid
  // solution for non-standard sets. 
  // The general case (given ANY set of coins) is solved using dynamic 
  // programming, altough it remains unkown if a valid greedy algorithm
  // exists. 
  if(argv < 2) return 1;
  vector<int> euro_coins = {1,2,5,10,20,50,100,200};
  vector<int> n_coins;
  int amount  = atoi(argc[1]);
  greedy_coins(amount, n_coins, euro_coins);
  cout << "Number of coins: " << n_coins.size() << endl;
  cout << "The coins needed: " << endl;
  //print_vector(n_coins);

  // A way of seeing how many greedy algorithms can be there for a single problem
  // is throught the scheaduling problem. If you have n events that have a starting
  // and ending time, and they are able to overlap each other, the algorithm
  // has to find a way of suiting the max amount of events to fit in one scheadule.
  // It has many approaches: 
  //   1. To look for the shortest tasks. A counter example is when thre's only 1 
  //    such short event and all the rest are long. 
  //   2. Select the next event that begins as early as possible. This has a 
  //    counter example such as when there's one task that lasts for the 
  //    whole day, but many other that last for a lot less. 
  //   3. Select the next event that _ends_ as early as possible. This
  //     is proven to be the one that yields the optimal value always. 
  // Here's an attempt to implement this problem
  // Scheduling
  vector<vector<int>> events{ { 1, 3 },
    { 2, 5 },
    { 3, 9 },
    { 6, 8 }
  };
  vector<int> schedule;
  greedy_schedule(events, schedule);
  cout << "The optimal scheadule: " << endl;
  print_vector(schedule);

  // The more general problem of having n tasks with deadlines and durations
  // and a score that depends on the deadline and the days it took to complete
  // after the deadline (d-x) happens to have a similar optimal greedy solution: to always 
  // pick first the tasks with less duration, regardless of the deadline. 
  // This is because, given two successive tasks, if we do first the shortest
  // we will have a better score than doing the opposite, regardless of the deadline.

  return 0;
}

void greedy_schedule(vector<vector<int>>& events, vector<int> &scheadule){
  // Sort events by ending time (second item)
  // start from the first element after sorting (the one ending the soonest)
  // then look for the next one ending the soonest that hasn't already started
  // keep going until there's no more such events.  
  sort(events.begin(), events.end(), [](const vector<int>& a, const vector<int>& b){
    return a[1] < b[1];
  });

  scheadule.push_back(events[0][1]); // scheadule vector stores ending time of tasks
  for(int i=1; i<events.size() ; i++){
    if(events[i][0] >= scheadule.back()){
      scheadule.push_back(events[i][1]);
    }
  }
}

void greedy_coins(int amount, vector<int> &n_coins, vector<int> &set_coins){
  if(amount == 0) return;
  for(int i=set_coins.size()-1; i>=0; i--){
    int r = amount - set_coins[i];

    if(r>=0){
      n_coins.push_back(set_coins[i]);
      greedy_coins(r, n_coins, set_coins); 
      return;
    }
  }
}

void print_vector(vector<int> v){
  cout << "{ ";
  for(int i=0; i < v.size(); i++){
    cout << v[i] << ", ";
  }
  cout << "}" << endl;
}
