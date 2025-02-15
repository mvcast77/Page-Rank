#include <cstdlib>
#include <fstream>
#include <iostream>

void read(const char * file_name){

	std::ifstream file {file_name};

	int first_num;
	int second_num;
	char buf;

	while (file >> first_num){
		int count = 0;
		file >> buf >> second_num;
		++count;
		std::cout << "(" << first_num << ", " << second_num << ")" << "\n";
		while(file.peek() == ','){
			file >> buf >> second_num;
			std::cout << "(" << first_num << ", " << second_num << ")" << "\n";
			++count;
		}
		std::cout << "total count is: " << count << std::endl;
	}
}

int main(int argc, char ** argv){
	read(argv[1]);
	return 0;
}
