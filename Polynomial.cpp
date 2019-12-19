#include "Polynomial.h"
#include <iostream>
using namespace std;

Polynomial::Polynomial()
{
	head = NULL;
}
Polynomial::Polynomial(const Polynomial &polynom) 
{
	if (polynom.head == NULL)
		this->head = NULL;
	else
	{
		Node * tailPoly = polynom.head;
		Node * tailthis;
		Node * newnode = new Node;
		newnode->next = NULL;
		newnode->data = new Monomial(*tailPoly->data);
		this->head = newnode;
		tailthis = this->head;
		tailPoly = tailPoly->next;
		while (tailPoly)
		{
			Node * newnode = new Node;
			newnode->next = NULL;
			newnode->data = new Monomial(*tailPoly->data);
			tailthis->next = newnode;
			tailPoly = tailPoly->next;
			tailthis = tailthis->next;
		}
	}
}
Polynomial::~Polynomial() {
	Node *p = head;
	while (p) {
		Node *q = p;
		p = p->next;
		delete q->data;
		delete q;
	}
}

Polynomial::Node* Polynomial::findGreaterOrEqual(int degree, Polynomial::Node*& prev) const {
	Node *ret = prev = NULL;
	Node *p = head;
	while (p && p->data->getDegree() >= degree) {
		prev = ret;
		ret = p;
		p = p->next;
	}
	return ret;
}

void Polynomial::add(const Monomial &monom) {
	Node *prev;
	Node *p = findGreaterOrEqual(monom.getDegree(), prev);
	if (p && p->data->getDegree() == monom.getDegree()) {
		p->data->add(monom);
		if (p->data->getCoefficient() == 0) { // The monomial vanished, remove it from list
			delete p->data;
			if (prev) {
				prev->next = p->next;
			}
			else {
				head = p->next;
			}
			delete p;
		}
	}
	else {
		Node *newNode = new Node;
		newNode->data = new Monomial(monom);
		if (p) {
			newNode->next = p->next;
			p->next = newNode;
		}
		else {
			newNode->next = head;
			head = newNode;
		}
	}
}
void Polynomial::print() const
{// Print whole list
	Node * tail= NULL;
	if (head != NULL)
	{
		tail = head;
		while (tail != NULL)
		{
			tail->data->print();
			if (tail->next != NULL && tail->next->data->getCoefficient() >= 0)
				cout << "+";
			tail = tail->next;
		}
	}
	else
		cout << 0 ;
} 
void Polynomial::remove(Node *prev)
{// Remove node
	Node * temp = NULL;
	if (head->data->getCoefficient() == 0) 
	{// Removing first node in list
		temp = head;
		head = head->next;
	}
	else
	{
		temp = prev->next;
		prev->next = prev->next->next;
	}
	delete(temp->data);
	delete(temp);
}

const Polynomial & Polynomial::operator+=(const Monomial&monom) {
	add(monom);
	return *this;
}
const Polynomial & Polynomial::operator+=(const Polynomial&polynom) {
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		*this += *(tail->data);
		tail = tail->next;
	}
	return *this;
}
const Polynomial & Polynomial::operator-=(const Monomial&monom)
{
	Monomial monom2 = monom;
	monom2 = -monom2;
	add(monom2);
	return *this;
}
 const Polynomial & Polynomial::operator-=(const Polynomial&polynom)
{
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		*this -= *(tail->data);
		tail = tail->next;
	}
	return *this;
}
Polynomial Polynomial::operator-()const
{
	Polynomial p(*this);
	Node * tail = p.head;
	while (tail != NULL)
	{
		*tail->data = -*tail->data;
		tail = tail->next;
	}
	return p;
}
bool Polynomial::operator==(const Polynomial &polynom) const 
{
	if (*this != polynom)
		return false;
	return true;
}
bool Polynomial::operator!=(const Polynomial &polynom) const
{
	Node * tail = this->head;
	Node * tail2 = polynom.head;
	if (this->head == NULL && polynom.head==NULL)
		return false;
	while (tail != NULL && tail2 !=NULL)
	{
		if (*tail->data == *tail2->data)
			return false;
		tail = tail->next;
		tail2 = tail2->next;
	}
	return true;
}
bool Polynomial::operator==(const Monomial &monom) const
{
	if (this->head != NULL)
	{
		if (*this->head->data == monom)
		{
			if (this->head->next == NULL)
				return true;
		}
	}
	
	return false;
}
bool Polynomial::operator!=(const Monomial &monom) const 
{
	if (*this == monom)
		return false;
	return true;
}
double Polynomial::operator() (const double r) const
{
	double sum = 0;
	Node * tail = this->head;
	while (tail)
	{ 
		sum += (*tail->data)(r);
		tail = tail->next;
	}
	return sum;
}
ostream & operator<<(ostream &out, const Polynomial &polynom)
{
	polynom.print();
	return out;
}

istream & operator>>(istream &in, Polynomial & polynom) 
{
	Monomial monom;
	while (polynom.head != NULL) //Empty the polynom in case it's an used one
	{
		polynom.head->data->setCoefficient(0);
		polynom.remove(polynom.head);
	}
	while (true)
	{
		in >> monom;
		polynom += monom;

		if (in.peek() == '\n')
			break;
	}
	in.get();
	return in;
}
double & Polynomial::operator[](const int &degree)
{
	Node * tail = this->head;
	static double temp = 0;
	if (head->data->getDegree() < degree)
		return temp;
	while (tail)
	{
		if (tail->data->getDegree() == degree)
		{
			return tail->data->getCoefficient();
		}
		tail = tail->next;
	}
	return temp;
}
const Polynomial & Polynomial::operator=(const Polynomial &polynom) 
{
	Polynomial p = polynom;
	while (this->head!=NULL)
	{
		this->head->data->setCoefficient(0);
		this->remove(this->head);
	}
	*this += p;
	return *this;
}

 Polynomial  Polynomial::operator+(const Polynomial &polynom)const
{
	Polynomial  p(*this);
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		p += (*tail->data);
		tail = tail->next;
	}
	return p;
}
 Polynomial Polynomial::operator+(const Monomial& monom)const
{
	Polynomial p(*this);
	p.add(monom);
	return p;
}

 Polynomial Polynomial::operator-(const Monomial &monom) const
{
	Polynomial  p (*this);
	Monomial monom2 = monom;
	monom2 = -monom2;
	p.add(monom2);
	return p;
}
Polynomial Polynomial::operator-(const Polynomial &polynom)const 
{
	Polynomial p(*this);
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		p = *this - *(tail->data);
		tail = tail->next;
	}
	return p;
}

