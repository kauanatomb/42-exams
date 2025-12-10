#ifndef vect2_hpp
#define vect2_hpp

#include <iostream>

class vect2 {
    private:
        int x;
        int y;
    public:
        vect2();
        vect2(const int num1, const int num2);
        vect2(const vect2& other);
        vect2& operator=(const vect2& other);
        ~vect2();

        int operator[](int index) const;
        int& operator[](int index);

        vect2& operator++();
        vect2 operator++(int);
        vect2& operator--();
        vect2 operator--(int);

        vect2& operator-=(const vect2& other);
        vect2& operator+=(const vect2& other);
        vect2& operator*=(const vect2& other);
        vect2& operator*=(int num);

        vect2 operator*(int num) const;
        vect2 operator+(const vect2& other) const;
        vect2 operator-(const vect2& other) const;
        vect2 operator-() const;

        bool operator==(const vect2& other) const;
        bool operator!=(const vect2& other) const;
};

vect2 operator*(int num, vect2& obj);
std::ostream& operator<<(std::ostream& out, const vect2& obj);

#endif