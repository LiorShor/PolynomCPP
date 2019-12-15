#ifndef MONOMIAL_H_
#define MONOMIAL_H_
#include <iostream>

using namespace std;
class Monomial {
public:
	Monomial(double coefficient = 1, int degree = 0);
	Monomial(const Monomial &other);
	~Monomial();
	double getCoefficient()  const;
	int getDegree() const;
	void setCoefficient(const double);
	void setDegree(const int);
	void print() const;
	static int getNumberOfMonomials();
	bool degCheck(const Monomial &)const;
	Monomial operator=(const Monomial &);
	Monomial add(const Monomial &);
	Monomial operator+(const Monomial &)const;
	Monomial operator-(const Monomial &)const;
	Monomial operator*(const Monomial &)const;
	Monomial operator+=(const Monomial &);
	Monomial operator-=(const Monomial &);
	const Monomial& operator*=(const Monomial &);
	Monomial operator-();
	bool operator==(const Monomial &monomial)const;
	bool operator!=(const Monomial &monomial) const;
	friend ostream & operator<<(ostream &out, const Monomial &c);
	friend istream & operator>>(istream &in,  Monomial &monom);
	double operator()(double r) const;
	friend void convertStringtoCoefficient(char *&, Monomial &monom);
	friend void convertStringtoDegree(char *&, Monomial &monom);
	
private:
	double coefficient;
	int degree;
	static int numberOfMonomials;
};

#endif /* MONOMIAL_H_ */