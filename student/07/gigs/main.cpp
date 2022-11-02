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
 *  The data is stored to multimap with Artists name as key and
 * other values to vector.
 *  Data is handled with iterators and the alphabetical /
 * chronoligical order is created with creating multimap with wanted data as 
 * key and data as iterator to original multimap.
 * (Maybe not best implementation :D).
 * 
 * */

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

// Farthest year for which gigs can be allocated
const std::string FARTHEST_POSSIBLE_YEAR = "2030";

//Constants for handling vectors:
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

// Checks if artist has many gigs in same day or if stage is 
// booked for many artits at the same time:
bool is_invalid_artist(multimap<string, vector<string>> gigs)
{
    //Formatting variables and iterators:
    vector<string> day;
    //Two iterators, which we are using to compare map keys.
    multimap<string,vector<string>>::iterator gigs_iter = gigs.begin();
    multimap<string,vector<string>>::iterator test_iter = gigs.begin();
    //Adding first date to vector, where we can check if there are same dates.
    day.push_back(gigs_iter->second.at(DATE));
    gigs_iter++;
    while(gigs_iter != gigs.end())
    {
        // Checks that the key is same:
        if(gigs_iter->first == test_iter->first)
        {
            //If the date is not already in day vector. If not,
            // add it to the day vector:
            if(find(day.begin(), day.end(), gigs_iter->second.at(DATE))
             == day.end())
            {
                day.push_back(gigs_iter->second.at(DATE));
            }
            // If date is in the vector, that means the artist has
            // double booked and return failure.
            else
            {
                cout << "Error: Already exists." << endl;
                return EXIT_FAILURE;
            }

        }
        // If the keys are not same, we can clear day vector.
        else
        {
            day.clear();
            
        }
            test_iter = gigs_iter;
            gigs_iter++;
    }
    return EXIT_SUCCESS;
}
// Checks that stage is not double booked for one day:
bool is_invalid_stage(multimap<string, vector<string>> gigs)
{
    // Formatting variables and iterators:
    multimap<string,vector<string>>::iterator gigs_iter = gigs.begin();
    multimap<string, multimap<string,vector<string>>::iterator> versus;
    vector<string> day;
    // Making new multimap so we can easily check the booked days by stages:
    versus.insert({gigs_iter->second.at(STAGE), gigs_iter});
    gigs_iter++;
    // Adding the stages and iterator for the new multimap:
    while(gigs_iter != gigs.end())
    {
        versus.insert({gigs_iter->second.at(STAGE), gigs_iter});
        gigs_iter++;
    }
    multimap<string, multimap<string,vector<string>>::iterator>::iterator
    versus_iter = versus.begin();
    multimap<string, multimap<string,vector<string>>::iterator>::iterator
    versus_test = versus.begin();
    // Adding the date to day vector so we can check for the booking:
    day.push_back(versus_iter->second->second.at(DATE));
    versus_iter++;
    while(versus_iter != versus.end())
    {
        // If stages name is same:
        if(versus_iter->first == versus_test->first)
        {
            //If the next dates are same, return failure:
            if(versus_iter->second->second.at(DATE) == versus_test->second->second.at(DATE))
            {
                cout << "Error: Already exists." << endl;
                return EXIT_FAILURE;
            }
            //If the date is not in the day vector, add it there:
            else if(find(day.begin(), day.end(), 
            versus_iter->second->second.at(DATE)) == day.end())
            {
                day.push_back(versus_test->second->second.at(DATE));
                
            }
            // If it is, return failure.
            else
            {
                cout << "Error: Already exists." << endl;
                return EXIT_FAILURE;
            }

        }
        // If stage name is not the same, clear vector:
        else
        {
            day.clear();
            
        }
        versus_test = versus_iter;
        versus_iter++;
    }

    return EXIT_SUCCESS;

}

// Reads the text file including our data and gives it back to multimap
// in main func.
// Also handles errors here:
bool read_file(multimap<string, vector<string>>& gigs )
{
    string file_name = "";
    vector<string> splitted;
    string artist = "";
    cout << "Give a name for input file: ";
    getline(cin, file_name);
    ifstream file_temp(file_name);
    // If file is not found:
    if ( not file_temp )
    {
        cout << "Error: File could not be read." << endl;
        return EXIT_FAILURE;
    } 
    else
    {
        string rivi;
        while ( getline(file_temp, rivi) )
        {
            splitted = split(rivi);
            // If some of the data columns fields are empty, stop the program:
            for(auto str : splitted)
            {
                if(str.size() == 0)
                {
                    cout << "Error: Invalid format in file." << endl;
                    return EXIT_FAILURE;
                }
            }
            // If there is less than four fields in data column,
            // stop the program:
            if(splitted.size() != 4)
            {
                cout << "Error: Invalid format in file." << endl;
                return EXIT_FAILURE;
            }
            // If given date is not valid, stop the program:
            else if(!is_valid_date(splitted.at(1)))
            {
                cout << "Error: Invalid date." << endl;
                return EXIT_FAILURE;
            }
            // Add the artists name as key and other info as value:
            artist = splitted.at(0);
            splitted.erase(splitted.begin());
            gigs.insert({artist, splitted});
        }
        file_temp.close();
    }
    // If artist has double booked a gig or stage is double booked,
    // stop the program:
    if(is_invalid_artist(gigs) || is_invalid_stage(gigs))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
    
}

// Prints every artist that is stored in the multimap:
void print_all_artists(multimap<string,vector<string>> gigs)
{
    // Formatting iterators:
    multimap<string,vector<string>>::iterator artist_begin = gigs.begin();
    multimap<string,vector<string>>::iterator artist_test = gigs.begin();
    cout << "All artists in alphabetical order:" << endl;
    cout << artist_begin->first << endl;
    while ( artist_begin != gigs.end() ) 
    {
        // If the last key is same artist as current key, skip.
        if(artist_begin->first == artist_test->first)
        {
            ++artist_begin;
        }
        // If not same artist, print the key.
        else
        {
            cout << artist_begin->first;
            cout << endl;
            ++artist_begin;
            artist_test = artist_begin;
        }
    }
}

// Print artists upcoming gigs in chronological order:
void print_artist(multimap<string,vector<string>> gigs, string artist)
{
    // Count how many gigs are coming.
    // If the artist is not on the multimap, print error.
    int num = gigs.count(artist);
    if(num == 0)
    {
        cout << "Error: Not found." << endl;
    }
    // If the artist is found but has no gigs upcoming, just prints the info.
    else if(gigs.find(artist)->second.size() == 0)
    {
        cout << "Artist "<< artist <<
        " has the following gigs in the order they are listed:" 
        << endl;
    }
    else
    {
        multimap<string,vector<string>>::iterator artist_begin
         = gigs.find(artist);

        cout << "Artist "<< artist <<
        " has the following gigs in the order they are listed:" << endl;
        map<string, multimap<string,vector<string>>::iterator> versus;
        // Makes new map with date being key and original multimaps iterator as
        // value for easier print.
        // num is the amount of gigs the artist has:
        for(int i = 0; i < num; i++)
        {
            versus.insert({artist_begin->second.at(DATE), artist_begin});

            artist_begin++;

        }
        map<string, multimap<string,vector<string>>::iterator>::iterator versus_itr
        = versus.begin();
        // Prints out the gigs:
        while(versus_itr != versus.end())
        {
            cout << " - " << versus_itr->first << " : " <<
            versus_itr->second->second.at(CITY) << ", " 
            << versus_itr->second->second.at(STAGE) << endl;
            versus_itr++;
        }

    }
    

}

// Prints all stages in citys alphabetical order:
void print_all_stages(multimap<string,vector<string>> gigs)
{
    // Formatting variables and iterators:
    multimap<string,vector<string>>::iterator stage_test = gigs.begin();
    // Making versus multimap for easier printing:
    multimap<string, multimap<string,vector<string>>::iterator> versus;
    multimap<string, multimap<string,vector<string>>::iterator>::iterator
    versus_itr = versus.begin();
    while(stage_test != gigs.end())
    {
        // If there is no current city as key, add it.
        if(stage_test->second.size() == 0)
        {
            stage_test++;
        }
        else if(versus.find(stage_test->second.at(CITY)) == versus.end() )
        {
            // City name as key, original multimap iterator as value:
            versus.insert({stage_test->second.at(CITY), stage_test});
            stage_test++;
        }
        else
        {
            // If the city is already found in the multimap but the stage
            // is not, add it to the versus multimap:
            int num = versus.count(stage_test->second.at(CITY));
            for(int i = 0; i < num; i++)
            {
                versus_itr = versus.find(stage_test->second.at(CITY));
                if(versus_itr->second->second.at(STAGE) 
                != stage_test->second.at(STAGE))
                {
                    versus.insert({stage_test->second.at(CITY), stage_test});
                    stage_test++;
                }
                // If same stage is found in both, skip:
                else
                {
                    stage_test++;
                }
                
            }
            
        }

    }
    cout << "All gig places in alphabetical order:" << endl;
    versus_itr = versus.begin();
    // Print all the values:
    while(versus_itr != versus.end())
    {
        cout << versus_itr->first << ", " 
        << versus_itr->second->second.at(STAGE)
        << endl;
        versus_itr++;
    }
}

// Print stages every upcoming artist in alphabetical order:
void print_stage(multimap<string,vector<string>> gigs, string input)
{
    // Formatting variables and iterators:
    multimap<string,vector<string>>::iterator stage_test = gigs.begin();
    multimap<string, multimap<string,vector<string>>::iterator> versus;
    while(stage_test != gigs.end())
    {
        // Make new multimap for easier printing.
        // Stage name as key:
        if(stage_test->second.size() == 0)
        {
            stage_test++;
        }
        else
        {
            versus.insert({stage_test->second.at(STAGE), stage_test});
            stage_test++;
        }
        
    }
    // If our stage is not in the multimap, print error:
    multimap<string, multimap<string,vector<string>>::iterator>::iterator 
    versus_itr = versus.find(input);
    if(versus_itr == versus.end())
    {
        cout << "Error: Not found." << endl;
    }
    // If stage is in multimap, print artists out:
    else
    {
        int num = versus.count(input);
        cout << "Stage "<< versus_itr->first 
        <<" has gigs of the following artists:" << endl;
        for(int i = 0;i < num; i++)
        {
            cout << " - " <<versus_itr->second->first << endl;
            versus_itr++;
        }
    }
}

// Adds new artist without gigs:
void add_artist(multimap<string,vector<string>>& gigs, string artist)
{
    // If artist is already on map, print error:
    if(gigs.find(artist) != gigs.end())
    {
        cout << "Error: Already exists." << endl;
    }
    else
    {
        gigs.insert({artist, {}});
        cout << "Artist added." << endl;
    }
}

// Function to add gigs for already existing artists:
void add_gig(multimap<string,vector<string>>& gigs, string artist
, string date, string city, string stage)
{
    // If artist is not on the list:
    if(gigs.find(artist) == gigs.end())
    {
        cout << "Error: Not found." << endl;
    }
    // If artist has no gigs before:
    else if(gigs.find(artist)->second.size() == 0)
    {
        multimap<string,vector<string>> gigs_test = gigs;
        multimap<string,vector<string>>::iterator test_iter = gigs_test.find(artist);
        test_iter->second = {date, city, stage};
        // If given date is invalid:
        if(!is_valid_date(date))
        {
            cout << "Error: Invalid date." << endl;
        }
        // If there is no errors from stage:
        else if(!is_invalid_stage(gigs_test))
        {
            gigs = gigs_test;
            cout << "Gig added." << endl;
        }
    }
    // If artist has gigs already:
    else
    {
        multimap<string,vector<string>> gigs_test = gigs;
        gigs_test.insert({artist, {date, city, stage}});
        // If given date is invalid:
        if(!is_valid_date(date))
        {
            cout << "Error: Invalid date." << endl;
        }
        // If there is no errors from artist and stage:
        else if(!is_invalid_artist(gigs_test) && !is_invalid_stage(gigs_test))
        {
            gigs = gigs_test;
            cout << "Gig added." << endl;
        }
    }
}
// Cancels every
void cancel(multimap<string,vector<string>>& gigs, string artist, string date)
{
    // If artist is not on the list:
    if(gigs.find(artist) == gigs.end())
    {
        cout << "Error: Not found." << endl;
    }
    else if(!is_valid_date(date))
    {
        cout << "Error: Invalid date." << endl;
    }
    else
    {
        // num = amount of gigs, idx = used to check if
        // there is only one gig left and idx_2 = how many gigs
        // have been canceled.
        int num = gigs.count(artist);
        int idx = num;
        int idx_2 = 0;
        multimap<string,vector<string>>::iterator gigs_iter = gigs.find(artist);
        multimap<string,vector<string>>::iterator gigs_iter_test = gigs_iter;

        for(int i = 0; i < num; i++)
        {
            // If there is still multiple artist keys:

            gigs_iter_test++;
            if(gigs_iter->second.at(DATE) > date && idx > 1)
            {
                gigs.erase(gigs_iter);
                idx--;
                // Giving the old iterator next value:
                gigs_iter = gigs_iter_test;
            }
            // If there is only one key left:
            else if(gigs_iter->second.at(DATE) > date)
            {
                gigs_iter->second = {};
            }
            else
            {
                // Going to next iterator:
                gigs_iter++;
                gigs_iter_test = gigs_iter;
                idx_2++;
            }
        }
        // if idx_2 is same as number of gigs, it means nothing
        // have been canceled:
        if(idx_2 == num)
        {
            cout << "Error: No gigs after the given date." << endl;
        }
        else
        {
            cout << "Artist's gigs after the given date cancelled." << endl;
        }
    }
}

// Main function where program checks inputs etc:
int main()
{
    multimap<string,vector<string>> gigs = {};
    // If read_file gives failure, stop the program:
    if(read_file(gigs))
    {
        return EXIT_FAILURE;
    }

    while(true)
    {
        // Reads users input:
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
            // Uses split function to get artist name:
            vector<string> text = split(input, ' ');
            // If user gives only one parameter, print error:
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
            // Uses split function to get stages name:
            vector<string> text = split(input, ' ');
            // If user gives only one parameter, print error:
            if(text.size() < 2)
            {
                cout << "Error: Invalid input." << endl;
            }
            else
            {
                print_stage(gigs, text.at(1));
            }
        }
        else if(input.find("ADD_ARTIST") == 0 || input.find("add_artist") == 0)
        {
            // Uses split function to get artists name:
            vector<string> text = split(input, ' ');
            // If user gives only one parameter, print error:
            if(text.size() < 2)
            {
                cout << "Error: Invalid input." << endl;
            }
            else
            {
                add_artist(gigs, text.at(1));
            }
        }
        else if(input.find("ADD_GIG") == 0 || input.find("add_gig") == 0)
        {
            // Uses split function to get artists name:
            vector<string> text = split(input, ' ');
            // If user gives less than four parameters, print error:
            if(text.size() < 5)
            {
                cout << "Error: Invalid input." << endl;
            }
            else
            {
                add_gig(gigs, text.at(1), text.at(2), text.at(3), text.at(4));
            }            
        }
        else if(input.find("CANCEL") == 0 || input.find("cancel") == 0)
        {
            // Uses split function to get artists name:
            vector<string> text = split(input, ' ');
            // If user gives less than two parameters, print error:
            if(text.size() < 3)
            {
                cout << "Error: Invalid input." << endl;
            }
            else
            {
                cancel(gigs, text.at(1), text.at(2));
            }
        }
        else
        {
            cout << "Error: Invalid input." << endl;
        }
    }
}
