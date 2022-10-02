#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
nimi_(owner), credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const
{
    std::cout << nimi_ << " : " << iban_ << " : " << money_ << " euros" << std::endl;
}

void Account::set_credit_limit(int limit)
{
    if(credit_ == false)
    {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;

    }
    else
    {
        cred_limit_ = limit;
    }

}

void Account::save_money(int amount)
{
    money_ = amount;
}

void Account::take_money(int amount)
{
    if(money_ + cred_limit_ - amount < 0)
    {
        if(credit_)
        {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;

        }
        else
        {
            std::cout << "Cannot take money: balance underflow" << std::endl;

        }

    }
    else
    {
        money_ -= amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << money_ << " euros" << std::endl;

    }
}

void Account::transfer_to(Account& name, int amount)
{
    if(money_ + cred_limit_ - amount < 0)
    {
        if(credit_)
        {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }
        else
        {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }
        
    }
    else
    {
        money_ -= amount;
        name.money_ += amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << money_ << " euros" << std::endl;

    }
    
}
