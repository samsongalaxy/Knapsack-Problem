#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "Knapsack.h"

using namespace std;

int main(int argc, char **argv){
  cout << "Beginning test...\n";
  Knapsack k;
  int algorithm_flag = stoi(argv[3]);
  cout << "algorithm_flag is " << algorithm_flag << "\n";
  ifstream fin;
  fin.open(argv[1]);
  int n, c;
  getline(fin, n, ' ');
  getline(fin, c, '\n');
  k.setCapacity(n, c);
  for(int i = 0; i < n; i++){
    int w, p;
    getline(fin, w, ' ');
    getline(fin, p, '\n');
    k.addItem(w, p);
  }
  if(algorithm_flag == 0){

  }
  else if(algorithm_flag == 1){

  }
  else if(algorithm_flag == 2){

  }
  else cout << "ERROR: INCORRECT algorithm_flag VALUE!\n";
  return 0;
}
