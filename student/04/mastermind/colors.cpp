#include "colors.hh"

//Secret_colors is the eligible colors that can be picked:
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

//Playing one round of the mastermind:
bool Colors::game(string guess)
{
    // Formatting variables
    secret_str_ = "";
    string str_rights = "";
    
    //Making a string from the secret color vector for easier processing:
    for(auto sec_index : secret_)
    {
        secret_str_.push_back(sec_index);
    }

    //Converting the string to upper case.
    guess = is_upper(guess);


    //Formatting right guesses and variables:
    right_guess_ = 0;
    almost_right_ = 0;
    int already_removed = 0;
    //Making variable for guess so we can remove parts from it.
    string guess_temp = guess;

    //Goes through the guessed colors and checks if it's exactly right:
    for(int i = 0; i < 4; ++i)
    {
        if(guess.at(i) == secret_.at(i))
        {
            secret_str_.erase(i-already_removed,1);
            guess_temp.erase(i-already_removed,1);
            already_removed++;
            right_guess_++;

        }
    }

    //After removing exactly right guesses, find if some of the colors
    // are at all in secret colors:
    for(auto test_str : guess_temp)
    {
        if(secret_str_.find(test_str) != string::npos)
        {
            int k = secret_str_.find(test_str);
            secret_str_.erase(k,1);
            almost_right_++;
        }
    }

    //Add the right and almost right guesses in the end of the guess string
    // and save that to vector for printing:

    str_rights = to_string(right_guess_);
    str_rights += to_string(almost_right_);

    guess += str_rights;
    every_guess_.push_back(guess);

    // If function returns 4 right guesses, player has won.
    if(right_guess_ == 4)
    {
        return true;
    }
    else
    {
        return false;
    }

}
//Generates ranom secret color sequence and adds it to secret vector:
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

//If player wants to give the sescret colors themselves, this function
// adds the string to the secret vector:
bool Colors::is_listed(string list)
{

    //Formatting secret list if user have inputted invalid answers before
    secret_ = {};

    //Converting the string to upper case.
    list = is_upper(list);

    //Check if the given colors are in eligible secret list:
    if(input_check(list, true))
    {
        return true;
    }
    else
    {
        return false;
    }
}


//Checks if input is right and if format == true -> add the guess to vector:
bool Colors::input_check(string guess, bool format)
{
    //Converting the string to upper case.
    guess = is_upper(guess);

    if(guess.size() != 4)
    {
        cout << "Wrong size" << endl;
        return false;
    }

    //Check if the colors are in secret list:

    for(auto list_index : guess)
    {
        //If player is giving the secret list themselves, add it to secret_:
        if(secret_colors_string_.find(list_index)
            != string::npos && format == true)
        {
            secret_.push_back(list_index);
            continue;
        }
        // Only checking if input is right:
        else if(secret_colors_string_.find(list_index)
                != string::npos && format == false)
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
//Prints the guesses and how many are right or almost right.
void Colors::print() const
{
    
    const int PRINT_NUM = 5;

    for(basic_string<char> every_guess_index : every_guess_)
    {
        //In start print the vertical bar and reset counter.
        int counter = 1;
        cout << "|";
        for(auto sing_gues_idx : every_guess_index)
        {
            //If counter is PRINT_NUM, starts printing the guess part, 
            //which is different from char part:
            if(counter >= PRINT_NUM)
            {
                cout << " | " << sing_gues_idx;
            }
            //Normally print this:
            else
            {
                cout << " " << sing_gues_idx;
                counter++;
            }


        }
        //In the end of the column print vertical bar:
        cout << " | " << endl;
    
    }

}

//Converts text to uppercase:
string Colors::is_upper(string text)
{
    for(basic_string<char>::size_type x = 0; x < text.length(); x++)
    {
        text.at(x) = toupper(text.at(x));
    }
    return text;
}


