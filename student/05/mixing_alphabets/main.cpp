#include <iostream>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;
    string::iterator sec_letter = word.begin() + 1;
    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // TODO: implement your solution here
        
        string::iterator sec_last_letter = word.end() - 1;
        if(word.size() <= 2)
        {
            std::cout << word << std::endl;
        }
        else
        {

        
        shuffle(sec_letter, sec_last_letter, generator);
	
        std::cout << word << std::endl;

        }
    }
}
