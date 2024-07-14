#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>


class Complex {

    private:
    double real;
    double imag;

    public:
    Complex(double r, double i);

    double get_real() const;

    double get_imag() const;

    Complex operator+(const Complex& other) const;

    Complex operator-(const Complex& other) const;

    Complex operator*(const Complex& other) const;

    Complex operator/(const Complex& other) const;

    bool operator==(const Complex& other) const;

    bool operator!=(const Complex& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);

    // friend std::istream& operator>>(std::istream& is, Complex& c);
};
#endif