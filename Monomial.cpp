#define _CRT_SECURE_NO_WARNINGS
#include "Monomial.h"
#include <iostream>
#include <assert.h>

using namespace std;

int Monomial::numberOfMonomials = 0;

Monomial::Monomial(double coefficient, int degree) : degree(degree) {
	assert(degree >= 0);
	this->coefficient = coefficient;
	numberOfMonomials++;
}

Monomial::Monomial(const Monomial& other) : degree(other.degree) {
	this->coefficient = other.coefficient;
	numberOfMonomials++;
}

Monomial::~Monomial() {
	numberOfMonomials--;
}

double Monomial::getCoefficient() const 
{
	return coefficient;
}

int Monomial::getDegree() const {
	return degree;
}

void Monomial::print() const {
	if (coefficient != 1 || degree == 0) cout << coefficient;
	if (coefficient != 1 && degree > 0) cout << "*";
	if (degree > 0) cout << "x";
	if (degree > 1) cout << "^" << degree;
}
void Monomial::setCoefficient(const double coefficient)
{
	this->coefficient = coefficient;
}
void Monomial::setDegree(const int degree)
{
	this->degree = degree;
}
int Monomial::getNumberOfMonomials() {
	return numberOfMonomials;
}
Monomial Monomial::add(const Monomial &monomial)
{
	if (degCheck(monomial))
		coefficient += monomial.coefficient;
	return *this;

}
bool Monomial::degCheck(const Monomial &monomial)const
{
	if (this->degree == monomial.degree)
		return true;
	return false;
}
const Monomial & Monomial::operator=(const Monomial &monomial)
{
	this->degree = monomial.getDegree();
	this->coefficient = monomial.coefficient;
	return *this;
}
const Monomial & Monomial::operator+(const Monomial &monomial)const
{
	if (degCheck(monomial))
		return Monomial(this->coefficient + monomial.coefficient, this->degree);
	return *this;
}
const Monomial &  Monomial::operator-(const Monomial &monomial1)const
{
	Monomial * monomial2 = new Monomial();
	if (degCheck(monomial1)) {
		*monomial2 = *this;
		*monomial2 -= monomial1;
		return *monomial2;
	}
	return *this;
}
const Monomial &  Monomial::operator*(const Monomial &monomial1)const
{
	Monomial * monomial2 =new Monomial(*this);
	*monomial2 *= monomial1;
	return *monomial2;
}
Monomial Monomial::operator+=(const Monomial &monomial)
{
	if (degCheck(monomial))
		this->coefficient += monomial.coefficient;
	return *this;
}
Monomial Monomial::operator-=(const Monomial &monomial)
{
	if (degCheck(monomial))
		this->coefficient -= monomial.coefficient;
	return *this;
}
 Monomial Monomial::operator*=(const Monomial &monomial)
{
	this->degree += monomial.degree;
	this->coefficient *= monomial.coefficient;
	return *this;
}
Monomial Monomial::operator-() {
	this->coefficient *= -1;
	return *this;
}

bool Monomial::operator==(const Monomial &monomial) const
{
	if (degCheck(monomial) && this->coefficient == monomial.coefficient)
		return true;
	return false;
}
bool Monomial::operator!=(const Monomial &monomial) const
{
	if (*this == monomial)
		return false;
	return true;
}
ostream & operator<<(ostream & out, const Monomial &monom)
{
	monom.print();
	return out;
}
istream &operator>>(istream &in, Monomial &monom)
{
	bool isPow = false, isX = false, isNum = false, isFirstMinus;
	static bool isSecMinus = false;
	double div = 0.1;
	char ch;

	isFirstMinus = isSecMinus;
	isSecMinus = false;
	monom.coefficient = monom.degree = 0;
	while ((ch = in.get()) != '\n')
	{
		if (ch == '^')
			isPow = true;
		else if (ch == 'x')
			isX = true;
		else if (ch >= '0'&& ch <= '9'){
			if (!isPow)
			{
				monom.setCoefficient((monom.getCoefficient() * 10) + (ch - '0'));
				isNum = true;
			}
			else
				monom.setDegree((monom.getDegree() * 10) + (ch - '0'));
		}
		else if (ch == '.'){
			ch = in.get();
			while (ch >= '0'&& ch <= '9'){
				monom.setCoefficient((monom.getCoefficient()) + ((ch - '0')*div));
				div *= 0.1;
				ch = in.get();
			}
			if (ch == '\n')
				break;
		}
		if (ch == ',' || ch == '+')
			break;	
		if ((ch == '-') && (!isNum && !isX && !isPow))
			isFirstMinus = true;
		else if (ch == '-')
		{
			isSecMinus = true;
			break;
		}
	}
	if (!isNum)
		monom.coefficient= 1;
	if (!isPow&&isX)
		monom.degree = 1;
	if (isFirstMinus == true) {
		monom.setCoefficient(-monom.getCoefficient());
		isFirstMinus = false;
	}
	return in;
}

double Monomial::operator()(double r)const {
	double power = 1;
	for (int i = 0; i < this->degree; i++)
	{
		power *= r;
	}
	return power*this->coefficient;
}

