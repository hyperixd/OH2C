#include "colors.hh"

Colors::Colors(const vector<char>& varit):
    varit_(varit)

{

}

void list_colors();


void Colors::game(string guess)
{

}

void Colors::random(int seed)           //distr(0,5);
{
    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(0,5);
    for(int i = 0 ; i < 4 ; ++i)
    {
        secret_.push_back(varit_.at(distr(gen)));
        cout << secret_.at(i) << endl;
    }


}

void Colors::listed(string list)
{

}
