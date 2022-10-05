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
    bool game(string guess);
    void random(int seed);
    bool is_listed(string list);
    bool input_check(string guess, bool format = true);
    void print() const;



private:

    // Private methdos
    string is_upper(string text);
    
    vector<char> guess_;
    vector<char> secret_;
    string secret_str_;
    int right_guess_ = 0;
    int almost_right_ = 0;
    const vector<char> secret_colors_;
    string secret_colors_string_;
    vector<string> every_guess_;


};

#endif // COLORS_HH
