#include "colors.hh"

Colors::Colors(const vector<char>& secret_colors):
    secret_colors_(secret_colors)

{

}

void list_colors();


void Colors::game(string guess)
{
    int i = 0;
}

void Colors::random(int seed)           
{
    // Generating random numbers between 0 and 5 to pick a color from the vector.
    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(0,5);
    for(int i = 0 ; i < 4 ; ++i)
    {
        // picking the colors
        secret_.push_back(secret_colors_.at(distr(gen)));

    }

}

bool Colors::is_listed(string list)
{
    //check if the list is right size:
    //if not, return false and ask for new list in main
    if(list.size() != 4)
    {
        cout << "Wrong size" << endl;
        return false;
    }


    //Converting the string to upper case.
    for(basic_string<char>::size_type x = 0; x < list.length(); x++)
    {
		list.at(x) = toupper(list.at(x));
	}

    // Making a string from the secret_colors vector to check characters more easily
    string secret_colors_string;
    for(auto secret_colors_index : secret_colors_)
    {
        secret_colors_string += secret_colors_index;
    }

    
    //Check if the colors are in secret list:
    
    for(auto list_index : list)
    {
        if(secret_colors_string.find(list_index) != string::npos)
        {
            continue;
        }
        else
        {
            // If the color is not in secret list return false and ask for new list in main
            cout << "Unknown color" << endl;
            return false;
        }
    }

    return true;
}
