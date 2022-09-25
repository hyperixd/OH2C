#ifndef BOOK_HH
#define BOOK_HH
#include "date.hh"
#include <string>


class Book
{
public:
    Book(const std::string &auth, const std::string &nimi,
     bool loaned = false);


    void print() const;
    void loan(Date today);
    void renew();
    void give_back();


private:
    std::string auth_;
    std::string nimi_;
    bool loaned_;
    std::string loan_day_;
    std::string loan_back_;
};

#endif // BOOK_HH
