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
Monomial Monomial::operator=(const Monomial &monomial)
{
	this->degree = monomial.getDegree();
	this->coefficient = monomial.coefficient;
	return *this;
}
Monomial Monomial::operator+(const Monomial &monomial1)const
{
	Monomial monomial2;
	monomial2.coefficient = 0;	
	if (degCheck(monomial1)) {
		monomial2 = *this;
		monomial2 += monomial1;
		return monomial2;
	}
	return *this;
}
Monomial Monomial::operator-(const Monomial &monomial1)const
{
	Monomial monomial2;
	if (degCheck(monomial1)) {
		monomial2 = *this;
		monomial2 -= monomial1;
		return monomial2;
	}
	return *this;
}
Monomial Monomial::operator*(const Monomial &monomial1)const
{
	Monomial monomial2 =*this;
	monomial2 *= monomial1;
	return monomial2;
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
const Monomial & Monomial::operator*=(const Monomial &monomial)
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
	double div = 0.1;
	char c;
	bool pow_flag = false, x_flag = false, num_flag = false, minus_flag = false;
	monom.coefficient = monom.degree = 0;
	while ((c = in.get()) != '\n')
	{
		if (c == '.')
		{
			c = in.get();
			while (c >= '0'&&c <= '9')
			{
				monom.setCoefficient((monom.getCoefficient()) + ((c - '0')*div));
				div *= 0.1;
				c = in.get();
			}
			if (c == '\n')
				break;
		}
		else if (c == '^')
		{
			pow_flag = true;
		}
		else if (c == 'x')
		{
			x_flag = true;
		}
		else if (c >= '0'&&c <= '9')
		{
			if (!pow_flag)
			{
				monom.setCoefficient((monom.getCoefficient() * 10) + (c - '0'));
				num_flag = true;
			}
			else
			{
				monom.setDegree((monom.getDegree() * 10) + (c - '0'));
			}
		}
		if (c == ',' || c == '+')
			break;
		if (c == '-' && !x_flag && !pow_flag && !num_flag)
			minus_flag = true;

	}
	if (!pow_flag&&x_flag)
		monom.degree = 1;
	if (!num_flag)
		monom.setCoefficient(1);
	if (minus_flag == true)
		monom.setCoefficient(monom.getCoefficient()*-1);
	return in;
}
//istream & operator>>(istream &in, Monomial &monom)
//{
//	string input;
//	char str[100];
//	getline(cin, input); // read until , is found
//	strcpy(str, input.c_str());
//	bool isnegative = false ,xFlag = false ,degFlag = false;
//	if((strstr(str, "-")) != NULL)
//		isnegative = true;
//	if ((strstr(str, "x")) != NULL)
//		xFlag = true;
//	if ((strstr(str, "^")) != NULL)
//		degFlag = true;
//	
//
//	char * token = strtok(str, " -x^,");
//	if (xFlag == true && degFlag == true)//-24x^346
//	{
//		convertStringtoCoefficient(token, monom);
//		char * token = strtok(NULL, " -x^,");
//		convertStringtoDegree(token, monom);
//	}
//	else if (degFlag == false)  //2434x or x or -x
//	{
//		if(xFlag == true)
//			monom.degree = 1;
//		convertStringtoCoefficient(token, monom);
//	}
//	//23 546 etc.
//	if (isnegative)
//		monom.coefficient *= -1;;
//	return in;
//}
//
//
//
//
//void convertStringtoCoefficient(char *&token, Monomial &monom)
//{
//	monom.coefficient = 0;
//	if (token != NULL) {
//		monom.coefficient = token[0] - '0';
//		for (int i = 1; i < (int)strlen(token); i++)
//		{
//			monom.coefficient *= 10;
//			monom.coefficient += token[i] - '0';
//		}
//	}
//}
//void convertStringtoDegree(char *&token, Monomial &monom)
//{
//	monom.degree = 0;
//	if (token != NULL) {
//		monom.degree = token[0] - '0';
//		for (int i = 1; i < (int)strlen(token); i++)
//		{
//			monom.degree *= 10;
//			monom.degree += token[i] - '0';
//		}
//	}
//}


double Monomial::operator()(double r)const {
	double power = r;
	for (int i = 0; i < this->degree; i++)
	{
		power *= r;
	}
	return power*this->coefficient;
}

