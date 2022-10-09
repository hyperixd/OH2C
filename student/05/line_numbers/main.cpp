#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string tiedoston_nimi = "";
    string output_name = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);
    cout << "Output file: ";
    getline(cin, output_name);

    ifstream tiedosto_olio(tiedoston_nimi);
    if ( not tiedosto_olio )
    {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } 
    else 
    {
        ofstream output_file(output_name);
        int line = 1;
        string rivi;
        while ( getline(tiedosto_olio, rivi) )
        {
            output_file << line << " " << rivi << endl;
            line++;
        }
        tiedosto_olio.close();
        output_file.close();
    }

    return EXIT_SUCCESS;
}
