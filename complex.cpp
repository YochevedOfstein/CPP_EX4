// yocheved@davidowitz.net

#include <iostream>
#include <string>
#include <vector>
#include <sstream>  
#include <iomanip> 
#include <cmath>
#include "complex.hpp"


Complex::Complex(double r, double i) : real(r), imag(i) {}

double Complex::get_real() const {
    return real;
}

double Complex::get_imag() const {
    return imag;
}

std::string Complex::to_string() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << get_real() << " + " << get_imag() << "i";
    return ss.str();
}

bool Complex::operator>(const Complex& other) const {
    return sqrt(real*real + imag*imag) > sqrt(other.real*other.real + other.imag*other.imag);
}

bool Complex::operator<(const Complex& other) const {
    return sqrt(real*real + imag*imag) < sqrt(other.real*other.real + other.imag*other.imag);
}

bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.get_real() << " + " << c.get_imag() << "i";
    return os;
}
