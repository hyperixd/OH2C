#include <iostream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

int message_test(string message)
{
    for(unsigned long long i = 0; i < message.length(); i++)
    {
        char enc_char = message.at(i);
        if(isupper(message.at(i)) == true || enc_char > 122 || enc_char < 97)
        {
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            return false;
        }
    }
    return true;
}

int char_test(string enc_text)
{
    int charact_test = 0;
    if(enc_text.length() != 26)
    {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return false;
    }

    for(unsigned long long i = 0; i < enc_text.length(); i++)
    {
        char enc_char = enc_text.at(i);
        if(isupper(enc_text.at(i)) == true || enc_char > 122 || enc_char < 97)
        {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return false;
        }
        charact_test += enc_char;

    }
    if(charact_test != 2847)
    {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return false;
    }
    return true;
}

int main()
{
    
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    string encrypt = "";
    cout << "Enter the encryption key: ";
    getline(cin, encrypt);

    if(char_test(encrypt) == false)
    {
        return EXIT_FAILURE;
    }

    string message = "";
    cout << "Enter the text to be encrypted: ";
    getline(cin, message);

    if(message_test(message) == false)
    {
        return EXIT_FAILURE;
    }

    map<char, char> enc_dict;
    for(unsigned long long i = 0; i < encrypt.length(); i++)
    {
        char alpha_char = alpha.at(i);
        char enc_char = encrypt.at(i);
        enc_dict[alpha_char] = enc_char;
    }

    for(unsigned long long j = 0; j < message.length(); j++)
    {
        char final = message.at(j);
        message.at(j) = enc_dict[final];
    }

    cout << "Encrypted text: " << message << endl;
    return EXIT_SUCCESS;
}
