#include <iostream>
#include <string>
#include <vector>

using namespace std;

// TODO: Implement split function here
// Do not change main function
std::vector<std::string> split(std::string line, char merkki, bool empty_space = false)
{
    string::size_type paikka;
    string::size_type last_paikka = 0;
    vector<string> pilkottu;
    while(line.find(merkki) != string::npos)
    {
        if(line.find(merkki) == 0 && empty_space == true)
        {
            line.erase(0,1);
        }
        else if(line.find(merkki) == 0 && empty_space == false)
        {
            pilkottu.push_back("");
            line.erase(0,1);
        }
        else
        {
        
        paikka = line.find(merkki);
        pilkottu.push_back(line.substr(last_paikka, paikka));
        line.erase(last_paikka, paikka + 1);
        
        }

    }
    if(line.size() == string::npos)
    {
        return pilkottu;
    }
    else if(empty_space == true)
    {
        return pilkottu;
    }
    else
    {
        pilkottu.push_back(line);
        return pilkottu;
    }
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
