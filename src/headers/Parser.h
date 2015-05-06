/*
// NOTE:
// This work is almost entirely based off of Ishkabible's tutorial/work on deamincode.net (http://www.dreamincode.net/forums/topic/234775-creating-a-recursive-descent-parser-oop-style/)
// At the moment, it is entirely based off of his work with some of my styling points and use of iterators instead of unsigned int in loops.
// As the project progresses, it will be completely revamped to be my work, but this is the state of it right now.
*/

#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<deque>
#include<exception>

//predefine classes, since inheritence and polymorphism is heavily used
class Production;
class Expression;
class Term;
class Unary;
class Number;
class Factor;
class ParseError;

//big daddy (n0tail)
class Production {
public:
	virtual ~Production();
	virtual double getValue() = 0;	//pure virtual. Make sure to override or polymorphism will bitch hard.

private:
};

//parsing errors
class ParseError : public std::exception {
	const char* what() const throw();
};

//NUMBER
class Number : public Production {
public:
	//notably, the contsructor takes a istream argument.
	Number(std::istream& in);
	//override
	double getValue();
private:
	double value;

};

//FACTOR
class Factor : public Production {
public:
	Factor(std::istream& in);	//again, the constructor is through stream argument
	~Factor();

	//poly
	double getValue();
private:
	Production* expression;

};

//UNARY
class Unary : public Production {
public:
	Unary(std::istream& in);
	~Unary();
	//poly
	double getValue();

private:
	int sign;
	Factor* value;

};

//TERM
class Term : public Production {
public:
	Term(std::istream& in);
	~Term();
	//poly
	double getValue();
private:
	std::deque<Unary*> values;
	std::deque<char> operations;

};

//EXPRESSION
class Expression : public Production {
public:
	Expression(std::istream& in);
	~Expression();
	//poly
	double getValue();
private:
	std::deque<Term*> values;
	std::deque<char> operations;
};

#endif //PARSER_H

