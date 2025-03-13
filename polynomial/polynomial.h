#include <istream>
#ifndef polynomial_h
#define polynomial_h

enum class Order { ASC, DESC };

class Term {
 private:
    int coeff;
    int exp;

 public:
    Term(int coeff = 0, int exp = 0) : coeff(coeff), exp(exp) {}

    Term& operator+(const Term& t2);
    friend std::istream& operator>>(std::istream& is, Term& t);
    friend std::ostream& operator<<(std::ostream& os, Term& t);

    friend class Polynomial;
};

class Polynomial {
 private:
    int termsAmount;
    Term* poly;
    Order order;
 public:
    Polynomial();
    Polynomial(int coeff);
    Polynomial(const Term& t);
    ~Polynomial();

    Polynomial& operator=(const Polynomial& p);
    Polynomial& operator+=(const Polynomial& p);
    Polynomial& operator*=(const Polynomial& p);

    friend Polynomial& operator+(const Polynomial& p1, const Polynomial& p2);
    friend Polynomial& operator*(const Polynomial& p1, const Polynomial& p2);

    friend std::istream& operator>>(std::istream& is, Polynomial& p);
    friend std::ostream& operator<<(std::ostream& os, Polynomial& p);
};

#endif
