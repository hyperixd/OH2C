#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>


// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.
void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);
        
    }
}

// TODO: Implement your solution here

bool same_values(std::vector < int >& ints)
{
    if ( std::equal(ints.begin() + 1, ints.end(), ints.begin()) )
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool is_ordered_non_strict_ascending(std::vector <int>& ints)
{
    return std::is_sorted(ints.begin(), ints.end());
    
}

bool is_arithmetic_series(std::vector <int>& ints)
{
    int how_many = ints.size();
    int sub = ints.at(how_many - 1) - ints.at(how_many - 2); 
    for(int i = 0; i < how_many - 2; ++i)
    {
        if (ints.at(i + 1) - ints.at(i) == sub)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool is_geometric_series(std::vector <int>& ints)
{
    if(same_values(ints) == true && ints.at(0) == 0)
    {
        return false;
    }
    
    int how_many = ints.size();
   
    if(ints.at(how_many - 2) == 0 && how_many == 2)
    {
        return false;
    }


    double sub = ints.at(how_many - 1) / ints.at(how_many - 2);

    
    
    
    
    for(int i = 0; i < how_many - 2; ++i)
    {
        if (ints.at(i) != 0 && ints.at(i + 1) / ints.at(i) == sub)
        {
            
            std::cout << ints.at(i + 1) / ints.at(i) << std::endl;
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
