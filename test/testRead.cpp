#include <fstream>
#include <iostream>

int main() {
	char c;
	std::string temp("../log/testCC.txt");
	std::ifstream file(temp.c_str());

	while (file) {
		file >> c;
		if (c != '0') {
			std::cout << "char = " << c << std::endl;
		}
	}


	return 0;
}
