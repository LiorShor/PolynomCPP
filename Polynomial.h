#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Monomial.h"
#include <iostream>

using namespace std;
class Polynomial
{
private:
	typedef struct list {
		Monomial * data;
		struct list * next;
	}Node;
	Node * head;
public:
	Polynomial();
	Polynomial(const Polynomial &);
	~Polynomial();
	void add(const Monomial &);
	void print() const;
	void insertbefore(Node *, Node *);
	void remove(Node *);
	const Polynomial & operator=(const Polynomial &);
	const Polynomial & operator+(const Polynomial &)const;
	const Polynomial & operator+(const Monomial&)const;
	const Polynomial & operator-(const Polynomial &)const;
	const Polynomial & operator-(const Monomial&)const;
	Polynomial operator-=(const Monomial&);
	Polynomial operator-=(const Polynomial&);
	Polynomial operator+=(const Monomial&);
	Polynomial operator+=(const Polynomial&);
	Polynomial operator-() const;
	double operator() (const double) const;
	bool operator!=(const Polynomial &) const;
	bool operator!=(const Monomial &) const;
	bool operator==(const Polynomial &) const;
	bool operator==(const Monomial &) const;
	double & operator[](const int &);
	friend ostream & operator<<(ostream &out, const Polynomial &c);
	friend istream & operator>>(istream &in, Polynomial &monom);
};

#endif // ! POLYNOMIAL_H
