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
  bt_helper(0, capacity, 0);
  fout << num_of_items << " " << maxprofit << " " << (double)clock()-start;
  for(int i = 0; i < bestset.size(); i++) fout << " " << bestset[i];
  fout << "\n";
  fout.close();
}

void Knapsack::bt_helper(int i, int max, int p){
  vector<int> temp;
  for(int j = i; j < knapsack_vec.size(); j++) {
    if(max > 0){
      if(knapsack_vec[j].weight <= max){
        temp.push_back(j);
        if((p + knapsack_vec[j].profit) >= maxprofit){
          maxprofit = p + knapsack_vec[j].profit;
          promising = true;
        }
      }
      if((j + 1) < knapsack_vec.size()) bt_helper(j+1, max - knapsack_vec[j].weight, p + knapsack_vec[j].profit);
      else{
        if(promising){
          //bestset.clear();
          //move(temp.begin(), temp.end(), back_inserter(bestset));
          for(int k = 0; k < temp.size(); k++) bestset.push_back(temp[k]);
          promising = false;
        }
        temp.clear();
        return;
      }
    }
    else{
      if(promising){
        //bestset.clear();
        //move(temp.begin(), temp.end(), back_inserter(bestset));
        for(int k = 0; k < temp.size(); k++) bestset.push_back(temp[k]);
        promising = false;
      }
      temp.clear();
      return;
    }
  }
}
