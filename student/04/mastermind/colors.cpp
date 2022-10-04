#include "colors.hh"

Colors::Colors(const vector<char>& secret_colors):
  secret_colors_(secret_colors)

{
    // Making a string from the secret_colors vector
    // to check characters more easily
    string secret_colors_string;
    for(auto secret_colors_index : secret_colors_)
    {
        secret_colors_string_ += secret_colors_index;
    }
}



void Colors::game(string guess)
{
    
}

void Colors::random(int seed)           
{
    // Generating random numbers between
    // 0 and 5 to pick a color from the vector.
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
    
    //Formatting secret list if user have inputted invalid answers before
    secret_ = {};
    
    

    //Converting the string to upper case.
    for(basic_string<char>::size_type x = 0; x < list.length(); x++)
    {
		list.at(x) = toupper(list.at(x));
	}



    
    //Check if the colors are in secret list:       .......secret_.push_back(list_index);
    if(input_check(list, true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Colors::input_check(string guess_two, bool format)
{
    //Converting the string to upper case.
    for(basic_string<char>::size_type x = 0; x < guess_two.length(); x++)
    {
		guess_two.at(x) = toupper(guess_two.at(x));
	}
    
    if(guess_two.size() != 4)
    {
        cout << "Wrong size" << endl;
        return false;
    }


    
    //Check if the colors are in secret list:       .......secret_.push_back(list_index);
    
    for(auto list_index : guess_two)
    {
        if(secret_colors_string_.find(list_index) != string::npos && format == true)
        {
            secret_.push_back(list_index);
            continue;
        }
        else if(secret_colors_string_.find(list_index) != string::npos && format == false)
        {
            continue;
        }
        else
        {
            // If the color is not in secret list
            // return false and ask for new list in main
            cout << "Unknown color" << endl;

            return false;
        }
    }

    return true;

}
