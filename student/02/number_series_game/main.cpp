#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";

    // Write your code here

    // Variable that stores how many numbers will be printed.
    int game_lft;
    // Variable that stores current game number.
    int game_num = 1;
    std::cin >> game_lft;

    while(game_lft >= 1)    // Printing numbers when games left is bigger that 0
    {
        if(game_num % 3 == 0)   // If our number is divisible with 3, print "zip"
        {
            std::cout << "zip" << std::endl;
            game_num += 1;
            game_lft -= 1;
            continue;
        }
        std::cout << game_num << std::endl; //Printing game number.
        game_num += 1;
        game_lft -= 1;
    }

    return 0;
}
