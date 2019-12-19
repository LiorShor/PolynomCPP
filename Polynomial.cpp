#include "Polynomial.h"
#include <iostream>
using namespace std;

Polynomial::Polynomial()
{
	head = NULL;
}
Polynomial::Polynomial(const Polynomial &polynom)  ///WORKS!!!@$@!#$
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
Polynomial::~Polynomial() 
{ // Delete list
	Node * nodeToDelete = NULL;
	if (head != NULL)
	{
		while (head != NULL)
		{
			nodeToDelete = head;
			head = head->next;
			delete(nodeToDelete);
		}
	}
	delete(head);
}

void Polynomial::add(const Monomial & mon)
{ // Enqueue to list
	Node * tail, * prev = NULL;
	Node * newnode = new Node;
	newnode->next = NULL;
	newnode->data = new Monomial(mon);
	if (head == NULL)
		head = newnode;
	else
	{
		prev = tail = head;
		while (tail != NULL)
		{
			if (tail->data->getDegree() < mon.getDegree())
			{
				insertbefore(newnode, prev);
				return;
			}
			else
			if (tail->data->getDegree() == mon.getDegree())
			{
				tail->data->add(mon);
				if (tail->data->getCoefficient() == 0)
						remove(prev);
					delete newnode->data;
					delete newnode;

				return;
			}
			prev = tail;
			tail = tail->next;
		}
		delete tail;
		prev->next = newnode;
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
void Polynomial::insertbefore(Node * newnode,Node *prev)
{
	if(head->data->getDegree() < newnode->data->getDegree())  
	{// Insert to head
		newnode->next = head;
		head = newnode;
	}
	else{
		newnode->next = prev->next;
		prev->next = newnode;
	}
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

Polynomial Polynomial::operator+=(const Monomial&monom) {
	add(monom);
	return *this;
}
Polynomial Polynomial::operator+=(const Polynomial&polynom) {
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		*this += *(tail->data);
		tail = tail->next;
	}
	return *this;
}
 Polynomial Polynomial::operator-=(const Monomial&monom) ///WORKS
{
	Monomial monom2 = monom;
	monom2 = -monom2;
	add(monom2);
	return *this;
}
 Polynomial Polynomial::operator-=(const Polynomial&polynom) 
{
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		*this -= *(tail->data);
		tail = tail->next;
	}
	return *this;
}
Polynomial Polynomial::operator-()
{
	Node * tail = this->head;
	while (tail != NULL)
	{
		*tail->data = -*tail->data;
		tail = tail->next;
	}
	return *this;
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
	if (*this->head->data == monom)
	{
		if (this->head->next == NULL)
			return true;
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

const Polynomial & Polynomial::operator+(const Polynomial &polynom)const
{
	Polynomial * p = new Polynomial(*this);
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		*p += (*tail->data);
		tail = tail->next;
	}
	return *p;
}
const Polynomial & Polynomial::operator+(const Monomial& monom)const
{
	Polynomial * p = new Polynomial(*this);
	p->add(monom);
	return *p;
}

const Polynomial & Polynomial::operator-(const Monomial &monom) const
{
	Polynomial * p = new Polynomial(*this);
	Monomial monom2 = monom;
	monom2 = -monom2;
	p->add(monom2);
	return *p;
}
const Polynomial & Polynomial::operator-(const Polynomial &polynom)const 
{
	Polynomial * p = new Polynomial (*this);
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		*p = *this - *(tail->data);
		tail = tail->next;
	}
	return *p;
}

