#include "bigint.hpp"

bigint::bigint() : str("0") {}
bigint::bigint(unsigned int num) : str(std::to_string(num)) {}
bigint::~bigint() {}
bigint::bigint(const bigint& other) : str(other.str) {}
bigint& bigint::operator=(const bigint& other) {
    if (this != &other) {
        str = other.str;
    }
    return *this;
}

std::string bigint::getStr() const {
    return str;
}

std::ostream& operator<<(std::ostream& out, const bigint& obj) {
    out << obj.getStr();
    return out;
}

std::string sumStr(std::string str1, std::string str2) {
    int len1 = str1.length() -1;
    int len2 = str2.length() -1;
    int leftover = 0;
    std::string result;
    while (len1 >= 0 || len2 >= 0 || leftover) {
        int n1 = len1>= 0 ? str1[len1--] - '0' : 0;
        int n2 = len2>= 0 ? str2[len2--] - '0' : 0;
        int sum = n1 + n2 + leftover;
        result.push_back('0' + (sum % 10));
        leftover = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

bigint bigint::operator+(const bigint& other) const {
    bigint tmp;
    tmp.str = sumStr(str, other.str);
    return tmp;
}

// Another faster way to do the operator+
// bigint bigint::operator+(const bigint& other) const {
//     bigint tmp;
//     tmp.str = std::to_string(std::stoul(str) + std::stoul(other.str));
//     return tmp;
// }

bigint& bigint::operator+=(const bigint& other) {
    *this = *this + other;
    return *this;
}

bigint& bigint::operator++() {
    bigint tmp(1);
    *this += tmp;
    return *this;
}

bigint bigint::operator++(int) {
    bigint tmp(*this);
    ++*this;
    return tmp;
}

bigint bigint::operator<<(const unsigned int num) const {
    bigint tmp(*this);
    tmp.str.insert(tmp.str.end(), num, '0');
    return tmp;
}

bigint bigint::operator>>(const unsigned int num) const {
    size_t len = str.length();
    bigint tmp(*this);
    if (len > num)
        tmp.str.erase(len - num, num);
    else
        tmp.str = "0";
    return tmp;
}

bigint& bigint::operator<<=(const unsigned int num) {
    *this = *this << num;
    return *this;
}

bigint& bigint::operator>>=(const bigint& other) {
    *this = *this >> std::stoul(other.str);
    return *this;
}

bool bigint::operator<(const bigint& other) const {
    if (str.length() != other.str.length())
        return str.length() < other.str.length();
    return str < other.str;
}
bool bigint::operator>(const bigint& other) const {
    if (str.length() != other.str.length())
        return str.length() > other.str.length();
    return str > other.str;
}

bool bigint::operator==(const bigint& other) const {
    return str == other.str;
}
bool bigint::operator<=(const bigint& other) const {
    return (*this == other || *this < other);
}
bool bigint::operator>=(const bigint& other) const {
    return (*this == other || *this > other);
}
bool bigint::operator!=(const bigint& other) const {
    return str != other.str;
}
