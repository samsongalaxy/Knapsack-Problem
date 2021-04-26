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
  k.openFile(argv[1]);
  cout << "algorithm_flag should be " << argv[2] << "\n";
  int algorithm_flag = stoi(argv[2]);
  cout << "algorithm_flag is " << algorithm_flag << "\n";
  ifstream fin;
  fin.open(argv[0]);
  while(!fin.eof()){
    int n, c;
    string temp;
    stringstream ss;
    ss.clear();
    getline(fin, temp, ' ');
    ss.str(temp);
    ss >> n;
    ss.clear();
    getline(fin, temp, '\n');
    ss.str(temp);
    ss >> c;
    ss.clear();
    k.setCapacity(n, c);
    for(int i = 0; i < n; i++){
      int w, p;
      getline(fin, temp, ' ');
      ss.str(temp);
      ss >> w;
      ss.clear();
      getline(fin, temp, '\n');
      ss.str(temp);
      ss >> p;
      ss.clear();
      k.addItem(w, p);
    }
    if(algorithm_flag == 0){
      k.greedy1();
    }
    else if(algorithm_flag == 1){

    }
    else if(algorithm_flag == 2){

    }
    else cout << "ERROR: INCORRECT algorithm_flag VALUE!\n";
    k.clearVec();
  }
  cout << "Test complete! Results are in " << argv[1] << "\n";
  return 0;
}
