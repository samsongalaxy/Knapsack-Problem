#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Knapsack.h"

using namespace std;

Knapsack::Knapsack(){
  price = 0;
  weight = 0;
  num_of_items = 0;
  capacity = 0;
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

void Knapsack::addItem(int w, int p){
  Knapsack k;
  k.weight = w;
  k.price = p;
  knapsack_vec.pushback(k);
}
