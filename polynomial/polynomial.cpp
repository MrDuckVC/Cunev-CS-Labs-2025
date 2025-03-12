#include "polynomial.h"
#include <iostream>

Term& Term::operator+(const Term& t2) {
    if (exp == t2.exp) {
        coeff += t2.coeff;
    }
    return *this;
}

std::istream& operator>>(std::istream& is, Term& t) {
    t.coeff = 0;
    t.exp = 0;
    char c;
    bool termRead = false;
    while (!termRead) {
        is.get(c);
        switch (c) {
            case ' ':
                continue;
                break;
            case 'x':
                if (t.exp != 0) {
                    throw std::invalid_argument("Invalid input");
                }
                if (t.coeff == 0) {
                    t.coeff = 1;
                }
                t.exp = 1;
                break;
            case '^':
                is >> t.exp;
                break;
            case '+':
                termRead = true;
                break;
            case '\n':
                termRead = true;
                break;
            default:
                if ((c < '0' && c > '9') || t.exp != 0) {
                    throw std::invalid_argument("Invalid input");
                } else {
                    t.coeff = t.coeff * 10 + c - '0';
                }
                break;
        }
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, Term& t) {
    if (t.coeff == 0) {
        return os;
    }
    switch (t.exp) {
        case 0:
            return os << t.coeff;
            break;
        case 1:
            if (t.coeff == 1) {
                return os << "x";
            }
            return os << t.coeff << "x";
            break;
        default:
            break;
    }
    if (t.coeff == 1) {
        return os << "x^" << t.exp;
    }
    return os << t.coeff << "x^" << t.exp;
}
