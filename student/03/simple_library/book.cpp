#include "book.hh"
#include <iostream>


Book::Book(const std::string &auth, const std::string &nimi, bool loaned) :
auth_(auth),
nimi_(nimi),
loaned_(loaned)
{


}

void Book::print() const
{
    std::cout << auth_ << " : " << nimi_ << std::endl;
    if(loaned_)
    {
        std::cout << "- loaned: " << "x" << std::endl
        << "- to be returned: " << "xX__X_X_X__X" << std::endl;
    }
    else
    {
        std::cout << "- available" << std::endl;
    }
}

void Book::loan(Date today)
{
    if(loaned_)
    {
        std::cout << "Already loaned: cannot be loaned" 
        << std::endl;

    }
    else
    {
        loaned_ = true;
        Date loan_day_(today);
        Date loan_back_(loan_day_);
        loan_back_.advance(28);
        int i = 0;
    }
}

void Book::renew()
{
    int i = 0;
}

void Book::give_back()
{
    int i = 0;
}
