// TODO: Include your header file of the class describing a series of four colors


/* Mastermind
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Mastermind-pelin. Pelissä annetaan tai arvotaan
 * ensin salainen neljän värin sarja. Sama väri voi esiintyä sarjassa
 * useita kertoja, mutta mikään neljästä positiosta ei voi olla tyhjä.
 * Käyttäjä yrittää arvata, mitkä värit esiintyvät sarjassa ja missä
 * järjestyksessä. Tätä varten käyttäjä antaa oman neljän värin sarjansa,
 * ja ohjelma ilmoittaa, kuinka monta väriarvausta meni täysin oikein
 * (oikea väri oikeassa positiossa) sekä kuinka monta arvausta meni
 * pelkästään värin osalta oikein (oikea väri väärässä positiossa).
 * Tämän jälkeen käyttäjä voi tehdä uuden arvauksen jne.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla väreillä vai käyttäjän luettelemilla väreillä.
 * (Jälkimmäinen tapa ei ole kovin järkevä, mutta se on hyödyllinen
 * testauksen kannalta.) Ensimmäisessä vaihtoehdossa käyttäjältä kysytään
 * satunnaislukugeneraattorin siemenlukua ja jälkimmäisessä häntä
 * pyydetään syöttämään neljä väriä (värien alkukirjaimet eli neljän
 * merkin mittainen merkkijono).
 *   Joka kierroksella käyttäjältä kysytään uutta arvausta. Peli päättyy
 * pelaajan voittoon, jos arvaus menee jokaisen värin kohdalta täysin
 * oikein. Peli päättyy pelaajan häviöön, jos hän ei ole arvannut oikein
 * maksimimäärällä (10) arvauskertoja.
 *   Ohjelma tarkistaa, että annetut värit kuuluvat sallittujen värien
 * joukkoon. Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 * Ohjelman kirjoittaja
 * Nimi: August Laulainen
 * Opiskelijanumero: 50077795
 * Käyttäjätunnus: nbaula
 * E-Mail: august.laulainen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */


#include <iostream>
#include <vector>
#include <string>
#include "colors.hh"

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
void get_input(Colors secret_color)
{
    cout << "Enter an input way (R = random, L = list): ";
    string input_str = "";
    cin >> input_str;
    if(input_str == "R" or input_str == "r")
    {
        cout << "Enter a seed value: ";
        int seed = 0;
        cin >> seed;
        

        secret_color.random(seed);
    }
    else if(input_str == "L" or input_str == "l")
    {
        bool accepted = false;
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
void print_all(/* a vector including color series */)
{
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
    //for(/* go through the vector */)
    {
        // TODO: print each vector element (color series)
    }
    print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
}

// Implements the actual game loop, where user-given guesses are read
// and compared to the secret row.
// On each round, all rows given so far are printed.
int main()
{
    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());
    Colors secret_colors({'B', 'R', 'Y', 'G', 'O', 'V'});
    // TODO: Declare an object for a color series (the secret one)
    get_input(secret_colors);
    



    //debug
    cout << "yey" << endl;
    //debug..................
    //secret_colors.random(1);
    //.......................


    // TODO: Play the game, i.e. repeatedly read a user given number series
    // and compare it with the secret one

    return 0;
}

