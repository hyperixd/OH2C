#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Enter a number: ";

    int num;
    cin >> num;
    // num = selected number
    // pow_num = selected number cubed
    int pow_num = num * num * num;

    if(pow_num < num)  // If cubed number is smaller than the original number, there has been integer overflow.
    {
        cout << "Error! The cube of " << num << " is not " << pow_num << "." << endl;

    }

    else    // There haven't been integer overflow.
    {
        cout << "The cube of " << num << " is " << pow_num << "." << endl;
    }
    return 0;
}
