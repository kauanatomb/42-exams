#include "vect2.hpp"
#include <iostream>

vect2::vect2() : x(0), y(0) {}
vect2::vect2(const int num1, const int num2) : x(num1), y(num2) {}
vect2::vect2(const vect2& other) : x(other.x), y(other.y) {}
vect2& vect2::operator=(const vect2& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}
vect2::~vect2() {}

int vect2::operator[](int index) const {
    if (index == 0)
        return x;
    else if (index == 1)
        return y;
    else
        return 0;
}

int& vect2::operator[](int index) {
    if (index == 0)
        return x;
    return y;
}

std::ostream& operator<<(std::ostream& out, const vect2& obj) {
    std::cout << "{" << obj[0] << ", " << obj[1] << "}";
    return out;
}

vect2& vect2::operator+=(const vect2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

vect2& vect2::operator*=(int num) {
    x *= num;
    y *= num;
    return *this;
}

vect2& vect2::operator*=(const vect2& other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

vect2& vect2::operator++() {
    x += 1;
    y += 1;
    return *this;
}

vect2 vect2::operator++(int) {
    vect2 vec(*this);
    x = vec.x + 1;
    y = vec.y + 1;
    return vec;
}

vect2& vect2::operator-=(const vect2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

vect2& vect2::operator--() {
    x -= 1;
    y -= 1;
    return *this;
}

vect2 vect2::operator--(int) {
    vect2 vec(*this);
    x = vec.x - 1;
    y = vec.y - 1;
    return vec;
}

vect2 vect2::operator*(int num) const {
    vect2 vec;
    vec.x = x * num;
    vec.y = y * num;
    return vec;
}

vect2 operator*(int num, vect2& obj) {
    vect2 vec;
    vec = obj * num;
    return vec;
}

vect2 vect2::operator+(const vect2& other) const {
    vect2 vec;
    vec.x = x + other.x;
    vec.y = y + other.y;
    return vec;
}

vect2 vect2::operator-(const vect2& other) const {
    vect2 vec;
    vec.x = x - other.x;
    vec.y = y - other.y;
    return vec;
}

vect2 vect2::operator-() const {
    vect2 vec(*this);
    vec.x = -vec[0];
    vec.y = -vec[1];
    return vec;
}

bool vect2::operator==(const vect2& other) const {
    return (x == other.x && y == other.y);
}

bool vect2::operator!=(const vect2& other) const {
    return (x != other.x && y != other.y);
}