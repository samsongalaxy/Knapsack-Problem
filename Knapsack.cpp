#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
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
  Knapsack pmax;
  for(int i = 0; i < knapsack_vec.size(); i++){
    //cout << "knapsack_vec[i].profit is " << knapsack_vec[i].profit << " and pmax.profit is " << pmax.profit << "\n";
    if(knapsack_vec[i].profit > pmax.profit){
      //cout << "knapsack_vec[i].weight is " << knapsack_vec[i].weight << " and capacity is " << capacity << "\n";
      if(knapsack_vec[i].weight <= capacity) pmax = knapsack_vec[i];
    }
  }
  if(will_print == 1){
    ofstream fout;
    fout.open(fileName, ios::app);
    if(maxprofit > pmax.profit){
      fout << num_of_items << " " << maxprofit << " " << (double)clock()-start;
      for(int i = 0; i < bestset.size(); i++) fout << " " << bestset[i];
      fout << "\n";
    }
    else{
      fout << num_of_items << " " << pmax.profit << " " << (double)clock()-start << " " << pmax.location << "\n";
      maxprofit = pmax.profit;
    }
    fout.close();
  }
  else{
    if(maxprofit < pmax.profit){
      maxprofit = pmax.profit;
      bestset.clear();
      bestset.push_back(pmax.location);
    }
  }
}

void Knapsack::backtracking(){
  clock_t start = clock();
  ofstream fout;
  fout.open(fileName, ios::app);
  vector<int> greedybestset = bestset;
  int greedymax = maxprofit;
  bt_helper(0, capacity, 0);
  fout << num_of_items << " " << maxprofit << " " << (double)clock()-start;
  if(greedymax > maxprofit){
    maxprofit = greedymax;
    bestset.clear();
    bestset = greedybestset;
  }
  for(int i = 0; i < bestset.size(); i++) fout << " " << bestset[i];
  fout << "\n";
  fout.close();
}

void Knapsack::bt_helper(int i, int max, int p){
  for(int j = i; j < knapsack_vec.size(); j++) {
    if(max > 0){
      if(knapsack_vec[j].weight <= max){
        //cout << "adding " << knapsack_vec[j].location << " to temp\n";
        temp.push_back(knapsack_vec[j].location);
        if((p + knapsack_vec[j].profit) >= maxprofit){
          maxprofit = p + knapsack_vec[j].profit;
          solution = true;
        }
      }
      if((j + 1) < knapsack_vec.size()) bt_helper(j+1, max - knapsack_vec[j].weight, p + knapsack_vec[j].profit);
      else{
        if(solution){
          bestset.clear();
          for(int k = 0; k < temp.size(); k++) bestset.push_back(temp[k]);
          solution = false;
        }
        temp.clear();
        return;
      }
    }
    else{
      if(solution){
        bestset.clear();
        for(int k = 0; k < temp.size(); k++) bestset.push_back(temp[k]);
        solution = false;
      }
      temp.clear();
      return;
    }
  }
}

//*** DYNAMIC PROGRAMMING CODE STARTS HERE ***
void Knapsack::dynamicprogramming(){
  clock_t start = clock();
  ofstream fout;
  fout.open(fileName, ios::app);
  int P[2][capacity];
  int maxprofit = 0;
  for(int c = 0; c < capacity; c++) P[0][c] = 0;
  for(int i = 1; i < num_of_items; i++){
    P[i%2][0] = 0;
    for(int c = 1; c < capacity; c++){ //items in columns 1 to capacity
      if((knapsack_vec[i].weight < capacity) && ((P[(i-1)%2][c-knapsack_vec[i].weight] + knapsack_vec[i].profit) > P[(i-1)%2][c])) P[i%2][c] = P[(i-1)%2][c-knapsack_vec[i].weight] + knapsack_vec[i].profit;
      else P[i%2][c] = P[(i-1)%2][c];
      if(P[i%2][c] > maxprofit) maxprofit = P[i%2][c];
    }
  }
  fout << num_of_items << " " << maxprofit << " " << (double)clock()-start << "\n";
  fout.close();
}
