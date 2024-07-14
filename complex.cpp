
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "complex.hpp"


Complex::Complex(double r, double i) : real(r), imag(i) {}

double Complex::get_real() const {
    return real;
}

double Complex::get_imag() const {
    return imag;
}

Complex Complex::operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
}

Complex Complex::operator*(const Complex& other) const {
    return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
}

Complex Complex::operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    return Complex((real * other.real + imag * other.imag) / denominator, (imag * other.real - real * other.imag) / denominator);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return real != other.real || imag != other.imag;
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.get_real() << " + " << c.get_imag() << "i";
    return os;
}

// friend std::istream& operator>>(std::istream& is, Complex& c) {
//     is >> c.real >> c.imag;
//     return is;
// }