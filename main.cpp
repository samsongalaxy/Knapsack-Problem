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
  k.openFile(argv[2]);
  //cout << "algorithm_flag should be " << argv[3] << "\n";
  int algorithm_flag = stoi(argv[3]);
  //cout << "algorithm_flag is " << algorithm_flag << "\n";
  ifstream fin;
  fin.open(argv[1]);
  while(!fin.eof()){
    //int n, c;
    string temp;
    stringstream ss;
    ss.clear();
    getline(fin, temp, ' ');
    ss.str(temp);
    //ss >> n;
    ss.clear();
    int n = stoi(temp);
    getline(fin, temp, '\n');
    ss.str(temp);
    //ss >> c;
    ss.clear();
    int c = stoi(temp);
    cout << "n is " << n << " and c is " << c << "\n";
    k.setCapacity(n, c);
    for(int i = 0; i < n; i++){
      //int w, p;
      getline(fin, temp, ' ');
      ss.str(temp);
      //ss >> w;
      ss.clear();
      int w = stoi(temp);
      getline(fin, temp, '\n');
      ss.str(temp);
      //ss >> p;
      ss.clear();
      int p = stoi(temp);
      cout << "w is " << w << " and p is " << p << "\n";
      k.addItem(w, p, i+1);
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
  cout << "Test complete! Results are in " << argv[2] << "\n";
  return 0;
}
