#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";

    // Write your code here

    int num;   // Declaring positive number variable.
    cin >> num;
    if(num <= 0)    // You can't factor zero so program will stop here.
    {
        cout << "Only positive numbers accepted" << endl;
        return 0;
    }

    for(int factor = round(sqrt(num)); factor >= 1; factor--)
    {
        if(num % factor == 0)
        {
            cout << num << " = " << factor << " * " << num / factor << endl;
            return 0;
        }
    }

}
