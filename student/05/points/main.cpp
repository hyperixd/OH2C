#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int main()
{
    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto_olio(tiedoston_nimi);
    if ( not tiedosto_olio )
    {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } 
    else 
    {
        map<string, int> users;
        string rivi;
        int separator;
        string nimi;
        int pisteet;
        vector<string> unique_names;
        while ( getline(tiedosto_olio, rivi) )
        {
            separator = rivi.find(":");
            nimi = rivi.substr(0,separator);
            pisteet = stoi(rivi.substr(separator + 1));
            if(users.find(nimi) == users.end())
            {
                users.insert( {nimi, pisteet});
                unique_names.push_back(nimi);
            }
            else
            {
                users.at(nimi) += pisteet;
            }
            


        }

        cout << "Final scores:" << endl;
        sort(unique_names.begin(), unique_names.end());
        for(auto uname : unique_names)
        {
            cout << uname << ": " << users.at(uname) << endl;
        }
        tiedosto_olio.close();
        
    }

    return EXIT_SUCCESS;
}
