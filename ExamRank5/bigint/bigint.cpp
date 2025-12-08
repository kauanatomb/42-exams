#include "bigint.hpp"

bigint::bigint() : str("0") {}
bigint::bigint(unsigned int num) : str(std::to_string(num)) {}
bigint::bigint(const bigint& other) : str(other.str) {}
bigint& bigint::operator=(const bigint& other) {
    if (this != &other) {
        str = other.str;
    }
    return *this;
}
bigint::~bigint() {}

std::string bigint::getStr() const {
    return str;
}

std::ostream& operator<<(std::ostream& out, const bigint& obj) {
    out << obj.getStr();
    return out;
}

std::string sumString(std::string str1, std::string str2) {
    int str1Len = str1.length() - 1;
    int str2Len = str2.length() - 1;
    std::string result;
    int leftover = 0;

    while (str1Len >= 0 || str2Len >= 0 || leftover) {
        int sumStr1 = str1Len >= 0 ? str1[str1Len--] - '0' : 0;
        int sumStr2 = str2Len >= 0 ? str2[str2Len--] - '0' : 0;
        int sum = sumStr1 + sumStr2 + leftover;
        result.push_back('0' + (sum % 10));
        leftover = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

bigint bigint::operator+(const bigint& other) const {
    bigint nBigInt;
    nBigInt.str = sumString(str, other.str);
    return nBigInt;
}

bigint& bigint::operator+=(const bigint& other) {
    str = sumString(str, other.str);
    return *this;
}

bigint& bigint::operator++() {
    str = sumString(str, "1");
    return *this;
}

bigint bigint::operator++(int) {
    bigint nBigInt(*this);
    this->str = sumString(nBigInt.str, "1");
    return nBigInt;
}

bigint bigint::operator<<(unsigned int num) const {
    bigint tmp(*this);
    tmp.str.insert(tmp.str.end(), num, '0');
    return tmp;
}

bigint bigint::operator>>(unsigned int num) const {
    bigint tmp(*this);
    size_t size = tmp.str.length();
    size >= num ? tmp.str.erase(size - num, num) : tmp.str = "0";
    return tmp;
}

bigint& bigint::operator<<=(unsigned int num) {
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
    return (str == other.str );
}

bool bigint::operator!=(const bigint& other) const {
    return (str != other.str );
}

bool bigint::operator>=(const bigint& other) const {
    return ((*this > other) || *this == other);
}

bool bigint::operator<=(const bigint& other) const {
    return ((*this < other) || *this == other);
}