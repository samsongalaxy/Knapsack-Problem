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
  /*cout << "Printing knapsack_vec:\n";
  for(int i = 0; i < knapsack_vec.size(); i++) cout << knapsack_vec[i].profit << " " << knapsack_vec[i].weight << "\n";*/
  clock_t start = clock();
  int swap;
  vec_to_print.clear();
  Knapsack temp;
  for(int i = 0; i < knapsack_vec.size(); i++){
    temp = knapsack_vec[i];
    swap = i;
    for(int j = i + 1; j < knapsack_vec.size(); j++){
      /*cout << "First value to be compared: " << temp.profit_weight_ratio << "\n";
      cout << "Second value to be compared: " << knapsack_vec[j].profit_weight_ratio << "\n";*/
        if(temp.profit_weight_ratio < knapsack_vec[j].profit_weight_ratio){
          temp = knapsack_vec[j];
          swap = j;
        }
    }
    if(swap != i){
      knapsack_vec[swap] = knapsack_vec[i];
      knapsack_vec[i] = temp;
    }
  }
  /*cout << "Printing knapsack_vec in descending order:\n";
  for(int i = 0; i < knapsack_vec.size(); i++) cout << knapsack_vec[i].profit << " " << knapsack_vec[i].weight << "\n";*/
  int current_weight = 0;
  maxprofit = 0;
  for(int i = 0; i < knapsack_vec.size(); i++){
    if((current_weight + knapsack_vec[i].weight) <= capacity){
      current_weight += knapsack_vec[i].weight;
      maxprofit += knapsack_vec[i].profit;
      vec_to_print.push_back(knapsack_vec[i].location);
    }
  }
  if(will_print == 1){
    ofstream fout;
    fout.open(fileName, ios::app);
    fout << num_of_items << " " << maxprofit << " " << ((double)clock()-start)/(double)CLOCKS_PER_SEC;
    for(int i = 0; i < vec_to_print.size(); i++) fout << " " << vec_to_print[i];
    fout << "\n";
    fout.close();
  }
}

void Knapsack::greedy2(int will_print){
  clock_t start = clock();

  int swap;
  vec_to_print.clear();
  Knapsack temp, pmax = knapsack_vec[0];
  for(int i = 0; i < knapsack_vec.size(); i++){
    temp = knapsack_vec[i];
    swap = i;
    for(int j = i + 1; j < knapsack_vec.size(); j++){
        if(temp.profit_weight_ratio < knapsack_vec[j].profit_weight_ratio){
          temp = knapsack_vec[j];
          swap = j;
        }
    }
    if(swap != i){
      knapsack_vec[swap] = knapsack_vec[i];
      knapsack_vec[i] = temp;
    }
    if((knapsack_vec[i].profit > pmax.profit) && (pmax.weight <= capacity)) pmax = knapsack_vec[i];
  }
  int current_weight = 0;
  maxprofit = 0;
  for(int i = 0; i < knapsack_vec.size(); i++){
    if((current_weight + knapsack_vec[i].weight) <= capacity){
      current_weight += knapsack_vec[i].weight;
      maxprofit += knapsack_vec[i].profit;
      vec_to_print.push_back(knapsack_vec[i].location);
    }
  }
  if(will_print == 1){
    ofstream fout;
    fout.open(fileName, ios::app);
    if(maxprofit > pmax.profit){
      fout << num_of_items << " " << maxprofit << " " << ((double)clock()-start)/(double)CLOCKS_PER_SEC;
      for(int i = 0; i < vec_to_print.size(); i++) fout << " " << vec_to_print[i];
      fout << "\n";
    }
    else{
      fout << "1 " << pmax.profit << " " << ((double)clock()-start)/(double)CLOCKS_PER_SEC << " " << pmax.location << "\n";
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


  fout.close();
}
