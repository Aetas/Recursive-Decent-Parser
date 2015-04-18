//TEST DRIVER
//no liscence yet.

#include<iostream>
#include<exception>
#include<sstream>	//I don't usually like using ss, but it is the simplest way to parse from text.
#include"Parser.h"

void exampleTests();

int main() {
	
	exampleTests();

	return 0;
}

void exampleTests() {
	try {
		std::stringstream ss(" (- 3 + 5 ) * - 4 ");
		Expression expr(ss);
		std::cout << expr.getValue() << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		std::stringstream ss(" - 3 +  5 * - 4 ");
		Expression expr(ss);
		std::cout << expr.getValue() << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		std::stringstream ss(" 3 +  5 * 4  ");
		Expression expr(ss);
		std::cout << expr.getValue() << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		std::stringstream ss(" (-3 + 5 * -4 ");
		Expression expr(ss);
		std::cout << expr.getValue() << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		std::stringstream ss(" (- a +  5  * - 4 ");
		Expression expr(ss);
		std::cout << expr.getValue() << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}