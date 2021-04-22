#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Knapsack{
  public:
    Knapsack();
    void openFile(string fn);
    void setCapacity(int n, int c);
    void addItem(int w, int p);
    int num_of_items, capacity, price, weight;
    std::vector<Knapsack> knapsack_vec;
    std::string fileName;
};

#endif
