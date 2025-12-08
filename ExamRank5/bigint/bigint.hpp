#ifndef bigint_HPP
#define bigint_HPP

#include <string>
#include <iostream>

class bigint {
    private:
        std::string str;
    public:
        bigint();
        bigint(unsigned int num);
        bigint(const bigint& other);
        bigint& operator=(const bigint& other);
        ~bigint();

        std::string getStr() const;

        bigint operator+(const bigint& other) const;
        bigint& operator+=(const bigint& other);

        bigint& operator++();
        bigint operator++(int);

        bigint operator<<(unsigned int num) const;
        bigint operator>>(unsigned int num) const;
        bigint& operator<<=(unsigned int num);
        bigint& operator>>=(const bigint& other);

        bool operator<(const bigint& other) const;
        bool operator>(const bigint& other) const;
        bool operator==(const bigint& other) const;
        bool operator!=(const bigint& other) const;
        bool operator>=(const bigint& other) const;
        bool operator<=(const bigint& other) const;
};

std::ostream& operator<<(std::ostream& out, const bigint& obj);

#endif
