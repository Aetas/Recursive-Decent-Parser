
#include<iostream>	//note that istream could be used to ditch the ostream half of this lib
#include<deque>
#include"Parser.h"

//static functions

static void ignoreSpace(std::istream& in);
static char getChar(std::istream& in);

/*
// MAVERICKS
*/

//This is the most usefull function ever written. Not really, but you get my point.
static void ignoreSpace(std::istream& in) {
	while (isspace(in.peek())) {
		in.get();
	}
}

static char getChar(std::istream& in) {
	ignoreSpace(in);		//takes care of preceding space
	char ret = in.get();
	ignoreSpace(in);		//takes care of following space, grabbing only the char
	return ret;				//return the prize
}


/*
// PRODUCTION
*/
Production::~Production() {}

//Parse error -- return to this
const char* ParseError::what() const throw() {
	return "a parsing error occured";
}	//expand upon this later with specific errors


/*
// NUMBER
*/
Number::Number(std::istream& in) {
	ignoreSpace(in);	//again, remove spaces
	in >> value;
	if (!in) {
		throw ParseError();
		return;
	}
	ignoreSpace(in);	//again, remove trailing space
}

//override inherited pure virtual
double Number::getValue() {
	return value;
}


/*
// FACTOR
*/
Factor::Factor(std::istream& in) {
	ignoreSpace(in);
	if (in.peek() == '(') {
		in.get();
		expression = new Expression(in);
		ignoreSpace(in);
		if (in.peek() != ')') {
			throw ParseError();
		}
		else {
			in.get();
		}
	}
	else {
		expression = new Number(in);
	}
}

Factor::~Factor() {
	delete expression;
}

double Factor::getValue() {
	return expression->getValue();
}

/*
// UNARY
*/
Unary::Unary(std::istream& in) {
	sign = 1;
	ignoreSpace(in);
	while (in.peek() == '-' || in.peek() == '+') {
		if (getChar(in) == '-') {
			sign = -sign;
		}
	}
	value = new Factor(in);	//grab the factor following unary
}

Unary::~Unary() {
	delete value;
}

double Unary::getValue() {
	return sign * value->getValue();	//either 1 * value or -1 * value. Basically makes it negative or not
}

/*
// TERM
*/
Term::Term(std::istream& in) {
	values.push_back(new Unary(in));	//make the first value
	ignoreSpace(in);
	while (in.peek() == '*' || in.peek() == '/') {
		operations.push_back(getChar(in));	//put the operations in queue
		values.push_back(new Unary(in));	//then push the left operand in queue
	}
}

Term::~Term() {
	for (std::deque<Unary*>::iterator it = values.begin(); it != values.end(); it++)
		delete *it;
}

double Term::getValue() {	//change to iterators
	double ret = values[0]->getValue();
	for (unsigned int i = 1; i < values.size(); i++) {
		if (operations[i - 1] == '*') {
			ret *= values[i]->getValue();
		}
		else {
			ret /= values[i]->getValue();
		}
	}
	return ret;
}

/*
// EXPRESSION
*/
Expression::Expression(std::istream& in) {
	ignoreSpace(in);
	values.push_back(new Term(in));
	while (in.peek() == '+' || in.peek() == '-') {
		operations.push_back(getChar(in));
		values.push_back(new Term(in));
	}
}

Expression::~Expression() {	//this may cause problems based on the nature of iterators, deleting, and how a deque shrinks when it is deleted. Well, in theory.
	for (std::deque<Term*>::iterator it = values.begin(); it != values.end(); it++)
		delete *it;
}

double Expression::getValue() {
	double ret = values[0]->getValue();
	for (unsigned int i = 1; i < values.size(); i++) {
		if (operations[i - 1] == '+')
			ret += values[i]->getValue();
		else
			ret -= values[i]->getValue();
	}
	return ret;
}