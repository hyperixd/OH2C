#ifndef COLORS_HH
#define COLORS_HH
#include <string>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

class Colors
{
public:
    // Constructor
    Colors(const vector<char>& secret_colors);

    // Methods
    void game(string guess);
    void random(int seed);
    bool is_listed(string list);
    


private:



    // Private methdos
    vector<char> guess_;
    vector<char> secret_;
    vector<int> right_guess_;
    const vector<char> secret_colors_;

};

#endif // COLORS_HH
