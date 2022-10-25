#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void print(map<string, vector<string>> lista, string id, string dots)
{
    for(string nimi : lista.at(id))
    {
        cout << dots << nimi << endl;
        if(!lista.at(nimi).empty())
        {
            dots += "..";
            print(lista, nimi, dots);
            dots = dots.substr(0, dots.length() - 2);
        }
        else if(lista.at(id).size() <= 1)
        {
            dots = "..";
        }
    }
}

void count(map<string, vector<string>> lista, string id, int& sum)
{
    for(string nimi : lista.at(id))
    {
        sum++;
        if(!lista.at(nimi).empty())
        {
            count(lista, nimi, sum);
        }
    }
}

void lista_depth(map<string, vector<string>> lista, string id, int& depth, int count = 0)
{
    for(string nimi : lista.at(id))
    {
        count++;
        if(!lista.at(nimi).empty())
        {
            lista_depth(lista, nimi, depth, count);
            count--;

        }
        else
        {
            if(count > depth)
            {
                depth = count;
                count = 0;
            }
            else
            {
                count = 0;
            }
        }
    }
}

int main()
{
    // TODO: Implement the datastructure here
    map<string, vector<string>> lista;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            if(lista.find(id1) != lista.end())
            {
                lista.at(id1).push_back(id2);
                lista.insert({id2, {}});

            }
            else
            {
                vector<string> vec = {id2};
                lista.insert({id1, vec});
                lista.insert({id2, {}});
            }

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            cout << id << endl;
            print(lista, id, "..");

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int sum = 0;
            count(lista, id, sum);
            cout << sum << endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int depth = 0;
            lista_depth(lista, id, depth);
            cout << 1 + depth << endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
