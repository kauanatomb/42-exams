#ifndef bigint_hpp
#define bigint_hpp

#include <string>
#include <iostream>
// #include <algorithm>

class bigint {
    private:
        std::string str;
    public:
        bigint();
        bigint(unsigned int num);
        ~bigint();
        bigint(const bigint& other);
        bigint& operator=(const bigint& other);

        std::string getStr() const;

        bigint operator+(const bigint& other) const;
        bigint& operator+=(const bigint& other);

        bigint& operator++();
        bigint operator++(int);

        bigint operator<<(const unsigned int num) const;
        bigint operator>>(const unsigned int num) const;
        bigint& operator<<=(const unsigned int num);
        bigint& operator>>=(const bigint& other);

        bool operator>(const bigint& other);
        bool operator>=(const bigint& other);
        bool operator<=(const bigint& other);
        bool operator<(const bigint& other);
        bool operator==(const bigint& other);
        bool operator!=(const bigint& other);
};

std::ostream& operator<<(std::ostream& out, const bigint& obj);

#endif