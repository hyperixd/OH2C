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
 *  The main game works by saving secret color sequence to vector, where first
 * it checks if the players guesses are exactly right and removing right
 * guesses from temporary guess string and secret color string.
 *  After that the game checks if any of the guesses colors are anywhere in the
 * secret sequence and saves those up.
 *  Then the program saves the original guess and right and almost right
 * guesses to a vector, where it prints those.
 *
 * */


#include "colors.hh"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Maximum number of guesses

const unsigned int GUESS_MAX = 10; 

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
            //Checks if given list is eligible:
            if(secret_color.is_listed(colors))
            {
                accepted = true;
            }
        }
    }
    else
    {
        // If user input something other that L or R repeat get_input():
        cout << "Bad input" << endl;
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

// Prints game status:

void print_all( Colors& secret_colors)
{
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
    //Most of the printing is happening in class:
    secret_colors.print();
     print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
}


//Asking player for colors or if they want to stop playing:
bool play_game(Colors& secret_colors)
{
    //Formatting variables:
    bool win = false;
    string guess;
    bool not_invalid = false;

    // prints row until player gives eligible guess:
    
    while(not_invalid == false)
    {
        cout << "ROW> ";
        cin >> guess;
        
        if(guess == "q" or guess == "Q")
        {
            exit(EXIT_SUCCESS);
        }
        else if(secret_colors.input_check(guess, false))
        {
            not_invalid = true;
        }
    }
    //Goes to the class file where the game function is:
    win = secret_colors.game(guess);
    //Prints game status
    print_all(secret_colors);
    return win;

    
}


int main()
{
    //formatting variables:
    unsigned int playtimes = 0;
    bool win = false;
    vector<char>secret_col = {'B', 'R', 'Y', 'G', 'O', 'V'};
    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());
    //Creating the secret color class:
    Colors secret_colors(secret_col);
    
    get_input(secret_colors);
    //Repeating the game until 10 guesses or win:
    while(playtimes < GUESS_MAX && win == false)
    {
        win = play_game(secret_colors);
        playtimes++;
    }
    if(win)
    {
        cout << "You won: Congratulations!" << endl;
        
    }
    else
    {
        cout << "You lost: Maximum number of guesses done" << endl;
    }

    return EXIT_SUCCESS;
}

