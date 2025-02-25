#ifndef FRACTION_H
#define FRACTION_H

#include <ostream>

namespace fraction {
class Fraction {
 private:
    static int N_DEC;
    int numerator_;
    int denominator_;
    void Simplify();

 public:
    Fraction();
    Fraction(const char*);
    Fraction(int, int);
    Fraction(double);

    void SetNDEC(int);

    Fraction operator+(const Fraction&);
    Fraction& operator+=(const Fraction&);

    friend Fraction operator+(double, const Fraction&);
    friend Fraction operator+=(double, const Fraction&);

    friend std::ostream& operator<<(std::ostream&, const Fraction&);
    friend std::istream& operator>>(std::istream&, Fraction&);
};
}  // namespace fraction

#endif  // FRACTION_H
