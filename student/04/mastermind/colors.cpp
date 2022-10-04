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



bool Colors::game(string guess)
{

    secret_str_ = "";
    string str_rights = "";
    for(auto sec_index : secret_)
    {
        secret_str_.push_back(sec_index);
    }


    //Converting the string to upper case.
    for(basic_string<char>::size_type x = 0; x < guess.length(); x++)
    {
        guess.at(x) = toupper(guess.at(x));
    }


    //Formatting right guesses:
    string temp_guess = "";
    string temp_sec = "";
    right_guess_ = 0;
    almost_right_ = 0;
    int already_removed = 0;
    int remove_2 = 0;
    string guess_temp = guess;
    vector<char> secret_temp = secret_;
    //vector<char>::iterator p = secret_temp.begin();

    for(int i = 0; i < 4; ++i)
    {
        if(guess.at(i) == secret_.at(i))
        {
            secret_str_.erase(i-already_removed,1);
            guess_temp.erase(i-already_removed,1);
            //p = secret_temp.begin()+ i - already_removed;
            already_removed++;
            right_guess_++;

            //secret_temp.erase(p);




        }
    }

    temp_sec = secret_str_;
    temp_guess = guess_temp;

    for(int x = 0; x < 4-already_removed; ++x)
    {
        if(secret_str_.find(guess_temp.at(x)) != string::npos)
        {
            int k = secret_str_.find(guess_temp.at(x- remove_2 ));
            temp_sec.erase(k,1);
            temp_guess.erase(x-remove_2,1);
            already_removed++;
            remove_2++;
            almost_right_++;
            continue;
        }
    }


    str_rights = to_string(right_guess_);
    str_rights += to_string(almost_right_);

    guess += str_rights;
    every_guess_.push_back(guess);

    if(right_guess_ == 4)
    {
        return true;
    }
    else
    {
        return false;
    }



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

void Colors::print() const
{


    for(auto evry_guess_idx : every_guess_)
    {
        int counter = 1;
        cout << "| ";
        for(auto sing_gues_idx : evry_guess_idx)
        {
            if(counter >= 5)
            {
                cout << " | " << sing_gues_idx;
            }
            else
            {
                cout << sing_gues_idx << " ";
                counter++;
            }


        }
        cout << " | " << endl;
    
    }

}


