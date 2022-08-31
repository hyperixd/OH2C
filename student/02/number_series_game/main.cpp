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

    while(game_lft >= 1)
    {
        std::cout << game_num << std::endl;
        game_num += 1;
        game_lft -= 1;
    }

    return 0;
}
