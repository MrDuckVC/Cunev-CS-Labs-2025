#include "fraction.h"
#include <iostream>
#include <numeric>
#include <cstring>
#include <cmath>

namespace {
void ThrowDenominatorIsZero() {
    throw std::invalid_argument("Denominator can't be zero.");
}
}

namespace fraction {
int Fraction::N_DEC = 4;

void Fraction::Simplify() {
    int gcd = std::gcd(numerator_, denominator_);
    numerator_ /= gcd;
    denominator_ /= gcd;
}

Fraction::Fraction() {
    numerator_ = 0;
    denominator_ = 1;
}
Fraction::Fraction(char* str) {
    numerator_ = 0;
    denominator_ = 1;

    int slashIndex = -1;
    for (int i = 0; i < std::strlen(str); i++) {
        if (str[i] == '/') {
            slashIndex = i;
            break;
        }
    }

    int spaceIndex = -1;
    for (int i = 0; i < std::strlen(str); i++) {
        if (str[i] == ' ') {
            spaceIndex = i;
            break;
        }
    }

    if (slashIndex == -1 && spaceIndex == -1) {
        numerator_ = std::stoi(str);
        denominator_ = 1;
    } else if (spaceIndex == -1) {
        // для дробей без целой части
        numerator_ = std::stoi(str);
        denominator_ = std::stoi(str + slashIndex + 1);
    } else {
        // для дробей с целой частью
        int wholePart = std::stoi(str);
        numerator_ = std::stoi(str + spaceIndex + 1);
        denominator_ = std::stoi(str + slashIndex + 1);
        if (wholePart < 0) {
            numerator_ *= -1;
        }
        numerator_ += wholePart * denominator_;
    }

    if (denominator_ == 0) {
        ThrowDenominatorIsZero();
    }

    Simplify();
}
Fraction::Fraction(int numerator, int denominator) {
    numerator_ = numerator;
    denominator_ = denominator;

    if (denominator_ == 0) {
        ThrowDenominatorIsZero();
    }
    Simplify();
}
Fraction::Fraction(double value) {
    denominator_ = static_cast<int>(std::pow(10, N_DEC));
    numerator_ = static_cast<int>(value * denominator_);
    Simplify();
}

void Fraction::SetNDEC(int n) {
    if (n < 0) {
        throw std::invalid_argument("N_DEC can't be negative.");
    }
    N_DEC = n;
}

Fraction Fraction::operator+(const Fraction& other) {
    int newDenominator = denominator_ * other.denominator_;
    int newNumerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
    return Fraction(newNumerator, newDenominator);
}
Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

Fraction operator+(double value, const Fraction& fraction) {
    return Fraction(value) + fraction;
}
Fraction operator+=(double value, const Fraction& fraction) {
    return Fraction(value) += fraction;
}

std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
    if (fraction.numerator_ % fraction.denominator_ == 0) {
        return os << fraction.numerator_ / fraction.denominator_;
    }
    if (std::abs(fraction.numerator_) > std::abs(fraction.denominator_)) {
        return os << fraction.numerator_ / fraction.denominator_ << " " << std::abs(fraction.numerator_ % fraction.denominator_) << "/" << fraction.denominator_;
    } else {
        return os << fraction.numerator_ << "/" << fraction.denominator_;
    }
    return os;
}
std::istream& operator>>(std::istream& is, Fraction& fraction) {
    char str[256];
    is.getline(str, 256);
    fraction = str;
    return is;
}
}  // namespace fraction
