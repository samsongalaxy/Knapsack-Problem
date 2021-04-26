#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include "Knapsack.h"

using namespace std;

Knapsack::Knapsack(){
  price = 0;
  weight = 0;
  num_of_items = 0;
  capacity = 0;
  location = 0;
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

void Knapsack::addItem(int w, int p, int l){
  Knapsack k;
  k.weight = w;
  k.price = p;
  k.location = l;
  knapsack_vec.push_back(k);
}

void Knapsack::clearVec(){
  knapsack_vec.clear();
}

void Knapsack::greedy1(){
  cout << "Printing knapsack_vec:\n";
  for(int i = 0; i < knapsack_vec.size(); i++) cout << knapsack_vec[i].price << " " << knapsack_vec[i].weight << "\n";
  clock_t start = clock();
  ofstream fout;
  fout.open(fileName, ios::app);
  int swap;
  vector<int> vec_to_print;
  cout << "1\n";
  for(int i = 0; i < knapsack_vec.size(); i++){
    Knapsack temp = knapsack_vec[i];
    cout << "2\n";
    for(int j = 0; j < knapsack_vec.size(); j++){
        if((temp.price/temp.weight) > (knapsack_vec[j].price/knapsack_vec[j].weight)){
          temp = knapsack_vec[j];
          cout << "3\n";
          swap = j;
          cout << "4\n";
        }
    }
    knapsack_vec[swap] = knapsack_vec[i];
    cout << "5\n";
    knapsack_vec[i] = temp;
    cout << "6\n";
  }
  cout << "Printing knapsack_vec in descending order:\n";
  for(int i = 0; i < knapsack_vec.size(); i++) cout << knapsack_vec[i].price << " " << knapsack_vec[i].weight << "\n";
  int current_weight = 0, current_profit = 0;
  for(int i = 0; i < knapsack_vec.size(); i++){
    if((current_weight + knapsack_vec[i].weight) <= capacity){
      current_weight += knapsack_vec[i].weight;
      current_profit += knapsack_vec[i].price;
      vec_to_print.push_back(knapsack_vec[i].location);
    }
  }
  fout << num_of_items << " " << current_profit << " " << ((double)clock()-start)/(double)CLOCKS_PER_SEC;
  for(int i = 0; i < vec_to_print.size(); i++) fout << " " << vec_to_print[i];
  fout << "\n";
  fout.close();
}
