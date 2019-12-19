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
	double & getCoefficient() {return coefficient;}
	int getDegree() const;
	void setDegree(const int);
	void setCoefficient(const double);
	void print() const;
	static int getNumberOfMonomials();
	bool degCheck(const Monomial &)const;
	Monomial add(const Monomial &);
	const Monomial & operator=(const Monomial &);
	Monomial operator+(const Monomial &)const;
	Monomial operator-(const Monomial &)const;
	Monomial operator*(const Monomial &)const;
	const Monomial & operator+=(const Monomial &);
	const Monomial & operator-=(const Monomial &);
	const Monomial & operator*=(const Monomial &);
	Monomial operator-() const ;
	bool operator==(const Monomial &monomial)const;
	bool operator!=(const Monomial &monomial) const;
	friend ostream & operator<<(ostream &out, const Monomial &c);
	friend istream & operator>>(istream &in,  Monomial &monom);
	double operator()(double r) const;
	
private:
	double coefficient;
	int degree;
	static int numberOfMonomials;
};

#endif /* MONOMIAL_H_ */