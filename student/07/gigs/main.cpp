/* COMP.CS.110 Project 2: GIGS
 * ===========================
 * EXAMPLE SOLUTION
 * ===========================
 *
 *  Acts as a simple gig calendar with n commands:
 * ARTISTS - Prints all known artist names
 * ARTIST <artist name> - Prints single artist's gigs
 * STAGES - Prints all known stage names and their locations
 * STAGE <stage name> - Prints all artists having a gig at the given stage
 * ADD_ARTIST <artist name> - Adds a new artist
 * ADD_GIG <artist name> <date> <town name> <stage name> - Adds a new gig for
 * an artist with the given date, town, and stage (the artist can't already
 * have a gig on the same date and there can't be other gigs at the same stage
 * at the same time)
 * CANCEL <artist name> <date> - Cancels artist's gigs after the given date
 *
 *  The data file's lines should be in format
 * artist_name;date;town_name;stage_name.
 * Otherwise the program execution terminates instantly (but still gracefully).
 *
 * Program author
 * Name: August Laulainen
 * Student number: 50077795
 * UserID: nbaula
 * E-Mail: august.laulainen@tuni.fi
 * 
 * Notes about the program and it's implementation:
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <algorithm>
#include <set>

using namespace std;

// Farthest year for which gigs can be allocated
const std::string FARTHEST_POSSIBLE_YEAR = "2030";

const int DATE = 0;
const int CITY = 1;
const int STAGE = 2;


// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split(const std::string& str, char delim = ';')
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for ( char current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quotation = not inside_quotation;
        }
        else if ( current_char == delim and not inside_quotation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Checks if the given date_str is a valid date, i.e. if it has the format
// dd-mm-yyyy and if it is also otherwise possible date.
bool is_valid_date(const std::string& date_str)
{
    std::vector<std::string> date_vec = split(date_str, '-');
    if ( date_vec.size() != 3 )
    {
        return false;
    }

    std::string year = date_vec.at(0);
    std::string month = date_vec.at(1);
    std::string day = date_vec.at(2);
    std::vector<std::string> month_sizes
            = { "31", "28", "31", "30", "31", "30",
                "31", "31", "30", "31", "30", "31" };

    if ( month < "01" or month > "12" )
    {
        return false;
    }
    if ( year < "0001" or year > FARTHEST_POSSIBLE_YEAR )
    {
        return false;
    }
    unsigned int year_int = stoi(year);
    bool is_leap_year = (year_int % 400 == 0) or
                        (year_int % 100 != 0 and year_int % 4 == 0);
    if ( day >= "01" and
        (day <= month_sizes.at(stoi(month) - 1) or
        (month == "02" and is_leap_year and day <= "29")) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_valid(multimap<string, vector<string>> gigs)
{
    vector<string> day;
    multimap<string,vector<string>>::iterator gigs_iter = gigs.begin();
    multimap<string,vector<string>>::iterator test_iter = gigs.begin();
    day.push_back(gigs_iter->second.at(DATE));
    gigs_iter++;
    while(gigs_iter != gigs.end())
    {
        if(gigs_iter->first == test_iter->first)
        {
            
            if(find(day.begin(), day.end(), gigs_iter->second.at(DATE)) == day.end())
            {
                day.push_back(gigs_iter->second.at(DATE));
            }
            else
            {
                cout << "Error: Already exists." << endl;
                return EXIT_FAILURE;
            }

        }
        else
        {
            day.clear();
            
        }
            test_iter = gigs_iter;
            gigs_iter++;
    }
    multimap<string,vector<string>>::iterator stage_iter = gigs.begin();
    multimap<string, multimap<string,vector<string>>::iterator> versus;
    versus.insert({stage_iter->second.at(STAGE), gigs_iter});
    stage_iter++;
    while(stage_iter != gigs.end())
    {
        versus.insert({stage_iter->second.at(STAGE), stage_iter});
        stage_iter++;
    }
    multimap<string, multimap<string,vector<string>>::iterator>::iterator versus_itr = versus.begin();
    multimap<string, multimap<string,vector<string>>::iterator>::iterator versus_test = versus.begin();
    day.clear();
    day.push_back(versus_itr->second->second.at(DATE));
    versus_itr++;
    while(versus_itr != versus.end())
    {
        if(versus_itr->first == versus_test->first)
        {
            
            if(find(day.begin(), day.end(), versus_itr->second->second.at(DATE)) == day.end())
            {
                day.push_back(versus_itr->second->second.at(DATE));
            }
            else
            {
                cout << "Error: Already exists." << endl;
                return EXIT_FAILURE;
            }

        }
        else
        {
            day.clear();
            
        }
            versus_test = versus_itr;
            versus_itr++;



    }



    return EXIT_SUCCESS;

}

bool read_file(multimap<string, vector<string>>& gigs )
{
    string tiedoston_nimi = "";
    vector<string> splitted;
    string artist = "";
    cout << "Give a name for input file: ";
    getline(cin, tiedoston_nimi);
    ifstream tiedosto_olio(tiedoston_nimi);
    if ( not tiedosto_olio )
    {
        cout << "Error: File could not be read." << endl;
        return EXIT_FAILURE;
    } 
    else
    {
        string rivi;
        while ( getline(tiedosto_olio, rivi) )
        {
            splitted = split(rivi);
            for(auto str : splitted)
            {
                if(str.size() == 0)
                {
                    cout << "Error: Invalid format in file." << endl;
                    return EXIT_FAILURE;
                }
            }
            if(splitted.size() != 4)
            {
                cout << "Error: Invalid format in file." << endl;
                return EXIT_FAILURE;
            }
            else if(!is_valid_date(splitted.at(1)))
            {
                cout << "Error: Invalid date." << endl;
                return EXIT_FAILURE;
            }
            artist = splitted.at(0);
            splitted.erase(splitted.begin());
            gigs.insert({artist, splitted});
        }
        tiedosto_olio.close();
    }
    if(is_valid(gigs))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
    
}

void print_all_artists(multimap<string,vector<string>> gigs)
{
    multimap<string,vector<string>>::iterator artist_begin = gigs.begin();
    multimap<string,vector<string>>::iterator artist_test = gigs.begin();

 
    cout << "All artists in alphabetical order:" << endl;
    cout << artist_begin->first << endl;
    while ( artist_begin != gigs.end() ) 
    {
        if(artist_begin->first == artist_test->first)
        {
            ++artist_begin;
        }
        else
        {
            cout << artist_begin->first;
            //for(int i = 0; i <= 2; i++)
            //{
            //    cout << " " << gigs_begin->second.at(i);
            //}
            cout << endl;
            ++artist_begin;
            artist_test = artist_begin;
        }
    }
 

}

void print_artist(multimap<string,vector<string>> gigs, string artist)
{
    int num = gigs.count(artist);
    if(num == 0)
    {
        cout << "Error: Not found." << endl;
    }
    else if(gigs.find(artist)->second.size() == 0)
    {

    }
    else
    {
        multimap<string,vector<string>>::iterator artist_begin = gigs.find(artist);
        cout << "Artist "<< artist <<" has the following gigs in the order they are listed:" << endl;
        map<string, multimap<string,vector<string>>::iterator> versus;
        for(int i = 0; i < num; i++)
        {
            versus.insert({artist_begin->second.at(DATE), artist_begin});

            artist_begin++;

        }
        map<string, multimap<string,vector<string>>::iterator>::iterator versus_itr = versus.begin();
        while(versus_itr != versus.end())
        {
            cout << " - " << versus_itr->first << " : " << versus_itr->second->second.at(CITY) << ", " << versus_itr->second->second.at(STAGE) << endl;
            versus_itr++;
        }

    }
    

}

void print_all_stages(multimap<string,vector<string>> gigs)
{
    multimap<string,vector<string>>::iterator stage_test = gigs.begin();

    multimap<string, multimap<string,vector<string>>::iterator> versus;
    multimap<string, multimap<string,vector<string>>::iterator>::iterator versus_itr = versus.begin();
    
    versus.insert({stage_test->second.at(CITY), stage_test});
    stage_test++;
    while(stage_test != gigs.end())
    {
        if(versus.find(stage_test->second.at(CITY)) == versus.end() )
        {
            versus.insert({stage_test->second.at(CITY), stage_test});
            stage_test++;
        }
        else
        {
            int num = versus.count(stage_test->second.at(CITY));
            for(int i = 0; i < num; i++)
            {
                versus_itr = versus.find(stage_test->second.at(CITY));
                if(versus_itr->second->second.at(STAGE) != stage_test->second.at(STAGE))
                {
                    versus.insert({stage_test->second.at(CITY), stage_test});
                    stage_test++;
                }
                else
                {
                    stage_test++;
                }
                
            }
            
        }

    }
    cout << "All gig places in alphabetical order:" << endl;
    
    versus_itr = versus.begin();
    while(versus_itr != versus.end())
    {
        cout << versus_itr->first << ", " << versus_itr->second->second.at(STAGE) << endl;
        versus_itr++;
    }
}

void print_stage(multimap<string,vector<string>> gigs, string input)
{
    multimap<string,vector<string>>::iterator stage_test = gigs.begin();

    multimap<string, multimap<string,vector<string>>::iterator> versus;

    
    versus.insert({stage_test->second.at(STAGE), stage_test});

    stage_test++;
    while(stage_test != gigs.end())
    {
        
        
        
        versus.insert({stage_test->second.at(STAGE), stage_test});
        stage_test++;
        

    }
    multimap<string, multimap<string,vector<string>>::iterator>::iterator versus_itr = versus.find(input);
    if(versus_itr == versus.end())
    {
        cout << "Error: Not found." << endl;
    }
    else
    {
        int num = versus.count(input);
        cout << "Stage "<< versus_itr->first <<" has gigs of the following artists:" << endl;
        for(int i = 0;i < num; i++)
        {
            cout << " - " <<versus_itr->second->first << endl;
            versus_itr++;
        }

    }
}

int main()
{
    multimap<string,vector<string>> gigs = {};
    if(read_file(gigs))
    {
        return EXIT_FAILURE;
    }

    while(true)
    {
        string input = " ";
        cout << "gigs> ";
        getline(cin,input);

        if(input == "QUIT" || input == "quit")
        {
            return EXIT_SUCCESS;
        }
        else if(input == "ARTISTS" || input == "artists")
        {
            print_all_artists(gigs);
        }
        else if(input.find("ARTIST") == 0 || input.find("artist") == 0)
        {
            vector<string> text = split(input, ' ');
            if(text.size() < 2)
            {
                cout << "Error: Invalid input." << endl;
            }
            else
            {
                print_artist(gigs, text.at(1));
            }
        }
        else if(input == "STAGES" || input == "stages")
        {
            print_all_stages(gigs);
        }

        else if(input.find("STAGE") == 0 || input.find("stage") == 0)
        {
            vector<string> text = split(input, ' ');
            if(text.size() < 2)
            {
                cout << "Error: Invalid input." << endl;
            }
            else
            {
                print_stage(gigs, text.at(1));
            }
        }
        else
        {
            cout << "Error: Invalid input." << endl;
        }

        


    }


    
}


    

