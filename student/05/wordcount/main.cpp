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
        
        map<string,vector<int>> sanat;
        string::size_type separator;
        vector<string> unique_word;
        string rivi;
        int last_stop = 0;
        string sana;
        vector<int> rivin_num_total;
        int rivin_num = 1;
        while( getline(tiedosto_olio, rivi))
        {
            separator = rivi.find(" ");
            while(separator != string::npos)
            {

                if(rivi.length() != 0 && separator != string::npos)  //TODO: make function that removes all the same words from rivi
                {
                    sana = rivi.substr(last_stop, separator);
                    sanat.insert( {sana, {}} );
                    sanat.at(sana).push_back(rivin_num);
                    rivi.erase(0,separator + 1);
                    unique_word.push_back(sana);
                    separator = rivi.find(' ');

                    sana += ' ';
                    while(rivi.find(sana) != string::npos)
                    {
                        rivi.erase(rivi.find(sana), sana.length());
                    }
                }


                
            }
            sana = rivi;
            sanat.insert( {sana, {}} );
            sanat.at(sana).push_back(rivin_num);
            rivi.erase(0);
            unique_word.push_back(sana);
            rivin_num++;
        }

        for (auto test : sanat)
        {
            cout << test.first << " " << test.second.size() << ": ";
            int koko = test.second.size();
            for(auto test_vec : test.second)
            {
                if(koko == 1)
                {
                    cout << test_vec << endl;
                }
                else
                {
                    cout << test_vec << ", ";
                    koko--;
                }

            }
        }
    }
    return EXIT_SUCCESS;
}
