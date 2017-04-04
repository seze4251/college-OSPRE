#include <iostream>
#include "hello.h"

void hello::print() {

	std::cout << "Hello World" << std::endl;
}

int main(int, char**) {
	hello* hi = new hello();
	hi->print();

	return 0;
}

