#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <iterator>
#include "Knapsack.h"

using namespace std;

Knapsack::Knapsack(){
  profit = 0;
  weight = 0;
  num_of_items = 0;
  capacity = 0;
  location = 0;
  profit_weight_ratio = 0;
  maxprofit = 0;
  numbest = 0;
  iter = 0;
  curr_profit = 0;
  curr_weight = 0;
}

void Knapsack::openFile(string fn){
  fileName = fn;
  ofstream fout;
  fout.open(fileName, ios::out | ios::trunc);
  fout << "";
  fout.close();
}

void Knapsack::setCapacity(int n, int c){
  num_of_items = n;
  capacity = c;
}

void Knapsack::addItem(double w, double p, int l){
  Knapsack k;
  k.weight = w;
  k.profit = p;
  k.location = l;
  k.profit_weight_ratio = p/w;
  knapsack_vec.push_back(k);
}

void Knapsack::clearVec(){
  knapsack_vec.clear();
}

void Knapsack::greedy1(int will_print){
  clock_t start = clock();
  int swap;
  bestset.clear();
  Knapsack k;
  for(int i = 0; i < knapsack_vec.size(); i++){
    k = knapsack_vec[i];
    swap = i;
    for(int j = i + 1; j < knapsack_vec.size(); j++){
        if(k.profit_weight_ratio < knapsack_vec[j].profit_weight_ratio){
          k = knapsack_vec[j];
          swap = j;
        }
    }
    if(swap != i){
      knapsack_vec[swap] = knapsack_vec[i];
      knapsack_vec[i] = k;
    }
  }
  int current_weight = 0;
  maxprofit = 0;
  for(int i = 0; i < knapsack_vec.size(); i++){
    if((current_weight + knapsack_vec[i].weight) <= capacity){
      current_weight += knapsack_vec[i].weight;
      maxprofit += knapsack_vec[i].profit;
      bestset.push_back(knapsack_vec[i].location);
    }
  }
  if(will_print == 1){
    ofstream fout;
    fout.open(fileName, ios::app);
    fout << num_of_items << " " << maxprofit << " " << (double)clock()-start;
    for(int i = 0; i < bestset.size(); i++) fout << " " << bestset[i];
    fout << "\n";
    fout.close();
  }
}

void Knapsack::greedy2(int will_print){
  clock_t start = clock();
  Knapsack pmax = knapsack_vec[0];
  for(int i = 0; i < knapsack_vec.size(); i++) if((knapsack_vec[i].profit > pmax.profit) && (pmax.weight <= capacity)) pmax = knapsack_vec[i];
  if(will_print == 1){
    ofstream fout;
    fout.open(fileName, ios::app);
    if(maxprofit > pmax.profit){
      fout << num_of_items << " " << maxprofit << " " << (double)clock()-start;
      for(int i = 0; i < bestset.size(); i++) fout << " " << bestset[i];
      fout << "\n";
    }
    else{
      fout << "1 " << pmax.profit << " " << (double)clock()-start << " " << pmax.location << "\n";
      maxprofit = pmax.profit;
    }
    fout.close();
  }
  else{
    if(maxprofit < pmax.profit) maxprofit = pmax.profit;
  }
}

void Knapsack::backtracking(){
  clock_t start = clock();
  ofstream fout;
  fout.open(fileName, ios::app);
  numbest = 0;
  for(int i = 0; i < num_of_items + 1; i++) include.push_back("no");
  iter = 0, curr_profit = 0, curr_weight = 0;
  bt_helper(0, capacity, 0);
  fout << num_of_items << " " << maxprofit << " " << (double)clock()-start;
  for(int i = 0; i < bestset.size(); i++) fout << " " << bestset[i];
  fout << "\n";
  fout.close();
}

void Knapsack::bt_helper(int i, int max, int p){
  for (int j = i; j < knapsack_vec.size(); j++) {
    if (max > 0){
      if (knapsack_vec[j].weight <= max){
        temp.push_back(j);
        if ((p + knapsack_vec[j].profit) >= maxprofit){
          maxprofit = p + knapsack_vec[j].profit;
          promising = true;
        }
      }
      if ((j + 1) < knapsack_vec.size()) bt_helper(j+1, max - knapsack_vec[j].weight, p + knapsack_vec[j].profit);
      else{
        if (promising == true){
          bestset.clear();
          move(temp.begin(), temp.end(), back_inserter(bestset));
          temp.clear();
          promising = false;
        }
        else temp.clear();
        return;
      }
    }
    else{
      if (promising == true){
        bestset.clear();
        move(temp.begin(), temp.end(), back_inserter(bestset));
        temp.clear();
        promising = false;
      }
      else temp.clear();
      return;
    }
  }
}

/*void Knapsack::bt_helper(int i, int curr_weight, int curr_profit){
  cout << "curr_weight is " << curr_weight << " and capacity is " << capacity << "\n";
  cout << "curr_profit is " << curr_profit << " and max profit is " << maxprofit << "\n";
  if((curr_weight <= capacity) && (curr_profit > maxprofit)){
    maxprofit = curr_profit;
    numbest = i;
    bestset.clear();
    for(int j = 0; j < include.size(); i++) if(include[j] == "yes") bestset.push_back(knapsack_vec[j].location);
  }
  if(promising(i, curr_weight, curr_profit)){
    include[i+1] = "yes";
    bt_helper(i+1, curr_weight + knapsack_vec[i+1].weight, curr_profit + knapsack_vec[i].profit);
    /*include[i+1] = "no";
    bt_helper(i+1, curr_weight, curr_profit);
  }
}*/

/*double Knapsack::KWF2(int i, int curr_weight, int curr_profit){
  double bound = curr_profit;
  int x[num_of_items];
  for(int j = i; i < num_of_items; i++) x[j] = 0;
  while((curr_weight < capacity) && (i <= num_of_items)){
    if((curr_weight + knapsack_vec[i].weight) <= capacity){
      x[i] = 1;
      curr_weight += knapsack_vec[i].weight;
      bound += knapsack_vec[i].profit;
    }
    else{
      x[i] = (capacity - curr_weight)/knapsack_vec[i].weight;
      curr_weight = capacity;
      bound = bound + knapsack_vec[i].profit * knapsack_vec[i].weight;
    }
    i++;
  }
  return bound;
}

bool Knapsack::promising(int i, int curr_weight, int curr_profit){
  if(curr_weight >= capacity) return false;
  double bound = KWF2(i, curr_weight, curr_profit);
  return (bound > maxprofit);
}*/
