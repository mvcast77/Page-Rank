#include <cstdlib>
#include <fstream>
#include <iostream>

void read(const char * file_name){

	std::ifstream file {file_name};

	int first_num;
	int second_num;
	char buf;

	while (file >> first_num){
		file >> buf >> second_num;
		std::cout << "(" << first_num << ", " << second_num << ")" << "\n";
		while(file.peek() == ','){
			file >> buf >> second_num;
			std::cout << "(" << first_num << ", " << second_num << ")" << "\n";
		}
	}

	return 0;
}

