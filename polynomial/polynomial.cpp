#include "polynomial.h"
#include <iostream>

void ThrowInvalidInput() {
    throw std::invalid_argument("Invalid input");
}

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
    bool isCoeffNegetive = false;
    while (!termRead) {
        is.get(c);
        switch (c) {
            case ' ':
                continue;
                break;
            case 'x':
                if (t.exp != 0) {
                    ThrowInvalidInput();
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
                if (c == '-') {
                    if (isCoeffNegetive) {
                        ThrowInvalidInput();
                    }
                    isCoeffNegetive = true;
                } else if (!(c >= '0' && c <= '9') || t.exp != 0) {
                    ThrowInvalidInput();
                } else {
                    t.coeff = t.coeff * 10 + c - '0';
                }
                break;
        }
    }
    if (isCoeffNegetive) {
        t.coeff *= -1;
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
            } else if (t.coeff == -1) {
                return os << "-x";
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

Polynomial::Polynomial() : termsAmount(0), order(Order::ASC) {
    Term* poly = new Term[1];
}
Polynomial::Polynomial(int coeff) {
    Term* poly = new Term[1];
    poly[0] = Term(coeff);
    termsAmount = 1;
    order = Order::ASC;
}
Polynomial::Polynomial(const Term& t) {
    Term* poly = new Term[1];
    poly[0] = t;
    termsAmount = 1;
    order = Order::ASC;
}

Polynomial::~Polynomial() {
    delete[] poly;
}

Polynomial& Polynomial::operator=(const Polynomial& p) {
    if (this != &p) {
        delete[] poly;
        poly = new Term[p.termsAmount];
        for (int i = 0; i < p.termsAmount; i++) {
            poly[i] = p.poly[i];
        }
        termsAmount = p.termsAmount;
        order = p.order;
    }
    return *this;
}
