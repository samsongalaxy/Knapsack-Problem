#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

class Knapsack{
  public:
    Knapsack();
    void openFile(std::string fn);
    void setCapacity(int n, int c);
    void addItem(double w, double p, int l);
    void clearVec();
    void greedy1(int will_print);
    void greedy2(int will_print);
    void backtracking();
    void bt_helper(int i, int curr_weight, int curr_profit);
    double KWF2(int i, int curr_weight, int curr_profit);
    boolean promising(int i, int curr_weight, int curr_profit);
    int num_of_items, capacity, profit, weight, location, maxprofit, numbest;
    double profit_weight_ratio;
    std::vector<Knapsack> knapsack_vec;
    std::string fileName;
    std::vector<int> bestset;
    std::vector<std::string> include;
};

#endif
