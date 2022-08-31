#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    // Write your code here
    
    double temp;   //Adding temperature variable and reading it.
    cin >> temp;

    // Printing temperatures
    cout << temp << " degrees Celsius is " << temp * 1.8 + 32 << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << (temp - 32)/1.8 << " degrees Celsius" << endl;
    return 0;
}
