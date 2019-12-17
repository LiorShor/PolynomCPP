#include "Polynomial.h"
#include <iostream>
using namespace std;

Polynomial::Polynomial()
{
	head = NULL;
}

Polynomial::~Polynomial() 
{ // Delete list
	Node * nodeToDelete= NULL;
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



 Polynomial Polynomial::operator=(const Polynomial &polynom)
{
	delete this;
	this->head = polynom.head;
	return *this;
}
 Polynomial Polynomial::operator+(const Polynomial &polynom)const
{
	 Polynomial p = polynom;
	 p = polynom;
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		p+=(*tail->data);
		tail = tail->next;
	}
	return p;
}
 Polynomial Polynomial::operator+(const Monomial& monom)const 
{
	Polynomial p = *this;
	p.add(monom);
	return p;
}

 Polynomial Polynomial::operator-(const Monomial &monom) const
{ // THIS SHOULD WORK : CALLING operator- IN MONOM !!
	Polynomial p = *this;
	Monomial monom2 = monom;
	Node * tail = p.head;
	while (tail != NULL)
	{
		*(tail->data) - monom2; 
		tail = tail->next;
	}
	return p;
}
 Polynomial  Polynomial::operator-(const Polynomial &polynom)const 
{
	Polynomial p = *this;
	Node * tail =polynom.head;
	while (tail != NULL)
	{
		p - *(tail->data);
		tail = tail->next;
	}
	return p;
}
 Polynomial & Polynomial::operator+=(const Monomial&monom) {
	add(monom);
	return *this;
}
 Polynomial  Polynomial::operator+=(const Polynomial&polynom) {
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		add(*(tail->data));
		tail = tail->next;
	}
	return *this;
}
 Polynomial & Polynomial::operator-=(const Monomial&monom)
{
	Monomial monom2 = monom;
	monom2.setCoefficient(monom2.getDegree()*-1);
	add(monom2);
	return *this;
}
 Polynomial & Polynomial::operator-=(const Polynomial&polynom)
{
	Node * tail = polynom.head;
	while (tail != NULL)
	{
		*this - *(tail->data);
		tail = tail->next;
	}
	return *this;
}
Polynomial Polynomial::operator-()
{
	Node * tail = this->head;
	while (tail != NULL)
	{
		-*(tail->data);
		tail = tail->next;
	}
	return *this;
}
bool Polynomial::operator==(const Polynomial &polynom) const //NEED TO CHECK
{
	if (*this != polynom)
		return false;
	return true;
}
bool Polynomial::operator!=(const Polynomial &polynom) const // NEED TO CHECK
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
		tail2 = tail->next;
	}
	return true;
}
bool Polynomial::operator!=(const Monomial &monom) const // NEED TO CHECK
{
	Polynomial p;
	p += monom;
	if (*this == p)
		return true;
	return false;
}
double Polynomial::operator() (const double r)
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

double  Polynomial::operator[](const int &degree)
{
	Node * tail = this->head;
	while (tail)
	{
		if (tail->data->getDegree() == degree)
		{
			return tail->data->getCoefficient();
		}
		tail = tail->next;
	}
	return 0;
}