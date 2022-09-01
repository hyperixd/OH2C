#include <iostream>
#include <cmath>
using namespace std;

unsigned long long int fact(int luku)   // Calculating the factorials
{   
    unsigned long long int pal_luku = 1;

    for(int i = 1; i <= luku; i++)
    {
        pal_luku *= i;
    }

    return pal_luku;
}

unsigned long long int lasku(int ball_total, int ball_draw) // Calculating total possibilities
{
    unsigned long long int vastaus = fact(ball_total) / (fact(ball_total - ball_draw) * fact(ball_draw));
    return vastaus;
}


int main()
{
    int ball_total; // Number of total balls
    cout << "Enter the total number of lottery balls: ";
    cin >> ball_total;

    int ball_draw;  // Number of balls that are drawn
    cout << "Enter the number of drawn balls: ";
    cin >> ball_draw;

    if(ball_total < 1  || ball_draw < 1)
    {
        cout << "The number of balls must be a positive number." << endl;
    }

    else if(ball_draw > ball_total)
    {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    }

    else
    {
        cout << "The probability of guessing all " << ball_draw << " balls correctly is 1/" << lasku(ball_total, ball_draw) << endl;
    }
    
    return EXIT_SUCCESS;
}
