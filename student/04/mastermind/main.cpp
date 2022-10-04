// TODO: Include your header file of the class describing a series of four colors


/* Mastermind
 *
 * Desc:
 *   This program implements a Mastermind game. First a secret series of
 * four colors is either given or drawn. The series can have several
 * identical colors, but none of the four positions can be empty.
 * The user tries to guess which colors the secret series has and in which
 * order they occur there. For this purpose, the user gives their own
 * series of four colors, and the program tells how many colors in the
 * guess was totally correct (correct color in correct position) and how
 * many of them were correct in color (but incorrect in position). After
 * that the user guesses again and so on.
 *   At first, the user is asked, if the game board will be filled with
 * randomly drawn colors, or with user-given ones. (The latter way is not
 * very sensible, but it is useful in testing purposes.) In the first
 * option, a seed value for the random number generator will be asked next.
 * In the latter option, the user is asked to input four colors (the first
 * letters of the colors, i.e. a string consisting of four characters).
 *   On each round, the user is asked for a new guess. The player wins if
 * all colors in the guess are totally correct. The player loses if they
 * have used the maximum number (10) of guesses without the right one.
 *   The program checks if the user-given colors are among accepted ones.
 * When the game ends, the program tells if the player won or lost.
 *
 * Program author ( Fill with your own info )
 * Name: August Laulainen
 * Student number: 50077795
 * UserID: nbaula ( Necessary due to gitlab folder naming. )
 * E-Mail: august.laulainen@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */


#include "colors.hh"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Maximum number of guesses
// (Not used in the template code)
const unsigned int GUESS_MAX = 10; // Not in use, yet

// Number of colors in a series
const unsigned int SIZE = 4;

// Length of the suffix part when printing a row.
// The suffix consists of three vertical lines ('|') and two digits, where one
// tells the amount of totally correct colors and the other tells the amount
// of correct colors in incorrect positions.
const unsigned int SUFFIX_LENGTH_IN_PRINT = 5;

// Text printed at the beginning of the program
const string INFO_TEXT = "Colors in use: \
B = Blue, R = Red, Y = Yellow, G = Green, O = Orange, V = Violet";

// TODO: Do you need more constants?

// Reads the input way, either random or listing way,
// and fills the color series in the user-desired way.
// Repeats the question until the user enters either R or L.
void get_input(Colors& secret_color)
{
    cout << "Enter an input way (R = random, L = list): ";
    string input_str = "";
    cin >> input_str;
    if(input_str == "R" or input_str == "r")
    {
        cout << "Enter a seed value: ";
        int seed = 0;
        cin >> seed;
        
        //Generates secret color list:
        secret_color.random(seed);
    }
    else if(input_str == "L" or input_str == "l")
    {
        bool accepted = false;

        //If user input wrong colors or wrong number of colors, repeat
        
        while(not accepted)
        {
            cout << "Enter four colors (four letters without spaces): ";
            string colors = "";
            cin >> colors;
            if(secret_color.is_listed(colors))
            {
                accepted = true;
            }

            
        }
    }
    else
    {
        cout << "Bad input" << endl;
        // Below the function itself is called recursively, which makes the
        // above code executed until an acceptable input_str is given,
        // but instead you can enclose the above code inside a loop structure.
        get_input(secret_color);
    }
}

// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Prints all color series.
// (Not called in the template code.)
void print_all(string guess, Colors& secret_color)
{
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
    cout << "| ";

    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
}

// Implements the actual game loop, where user-given guesses are read
// and compared to the secret row.
// On each round, all rows given so far are printed.


bool play_game(Colors& secret_colors)
{
    bool win = false;
    bool all_right = false;
    string guess;
    bool not_invalid = false;
    while(not_invalid == false)
    {
        cout << "ROW> ";

        cin >> guess;
        if(secret_colors.input_check(guess, false))
        {
            not_invalid = true;
        }
    }
    



        win = secret_colors.game(guess);



        //play_game(secret_colors);
        print_all(guess, secret_colors);
        return win;

    
}


int main()
{
    int playtimes = 0;
    bool win = false;
    vector<char>sec_clr = {'B', 'R', 'Y', 'G', 'O', 'V'};
    vector<char> seccc = {};
    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());
    Colors secret_colors(sec_clr);
    // TODO: Declare an object for a color series (the secret one)
    get_input(secret_colors);
    while(playtimes <= 10 && win == false)
    {
        win = play_game(secret_colors);
        playtimes++;
    }
    if(win == false)
    {
        cout << "You lost: Maximum number of guesses done" << endl;
    }
    else
    {
        cout << "You won: Congratulations!" << endl;
    }


    // TODO: Play the game, i.e. repeatedly read a user given number series
    
    
    // and compare it with the secret one

    return 0;
}

