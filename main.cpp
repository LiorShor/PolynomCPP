#include <iostream>
#include <iomanip>
#include "Monomial.h"
#include "Polynomial.h"

using namespace std;

void testMonomial() {
	Monomial m1, m2;

	do {
		cout << "Enter two monomials m1 and m2: " << endl;
		cin >> m1 >> m2;
		cout << "m1= " << m1 << ",m2= " << m2 << endl;
		cout << "m1+m2= " << m1 + m2 << endl;
		cout << "m1-m2= " << m1 - m2 << endl;
		cout << "m1*m2= " << m1 * m2 << endl;
		m1 *= 2;
		cout << "m1 *= 2, m1= " << m1 << endl;
		m2 += m1;
		cout << "m2 += m1, m1= " << m1 << ",m2=" << m2 << endl;
	} while (m1 != 0 || m2 != 0);
}

void testPolynomial() {
	Polynomial p,p2;
	Monomial m(3, 9);
	cout << "p=" << p << endl;
	cout << "Adding one to p" << endl;
	p += Monomial(3,9);
	p = -p;
	cout << "p=" << p << endl;
	p2 += Monomial(3, 9);
	p -= p2;
	if(p != m)
		cout << "yay";
	else
		cout << "not";
	cout << "p=" << p << endl;
	p2 += Monomial(3,9);
	if (p != p2)
		cout << "yay";
	else
		cout << "not";
	cout << "p=" << -p << endl;
	//p = p2;
	cout << "MINUS=" << p  << endl;
	cout << "Adding x^2 to p" << endl;
	p -= Monomial(1, 2);
	cout << "p=" << p << endl;
	//p2 = p;



	cout << "Adding -x^2 to p" << endl;
	p += Monomial(-1, 2);
	cout << "p=" << p << endl;
	cout << "p2=" << p2 << endl;
	cout << "Number of Monomials=" << Monomial::getNumberOfMonomials() << endl;
	do {
		cout << "Enter a polynomial: " << endl;
		cin >> p;
		cout << p << endl;
		cout << "p(0)=" << p(0) << ", p(1)=" << p(1) << ", p(2)=" << p(2) << endl;
		cout << "p[0]=" << p[0] << ", p[1]=" << p[1] << ", p[2]=" << p[2] << ", p[4]=" << p[4] << endl;
		//p[1] = 8;
		cout << "p-p=" << p- p << endl;
	} while (p != Monomial(0));
}

int main() {
	cout << boolalpha;
//	testMonomial();
	cout << "Number of Monomials=" << Monomial::getNumberOfMonomials() << endl;
	testPolynomial();
	cout << "Number of Monomials=" << Monomial::getNumberOfMonomials() << endl;
	return 0;
}
