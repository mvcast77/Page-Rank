#include <cstdlib>
#include <vector>
#include <iostream>

/*
 * This Script will generate a graph in key value(s) format.
 * Note that the calculation of the connected nodes will lead 
 *		to somewhat consistent gaps between the individual
 *		"second" nodes.
 * This may change in the future by replacing the addition of
 *		last to every "second" value with a random offset
 */

int main(int argc, char ** argv){
	if (argc < 2){
		std::cout << "Expected format is ./exec <N>";
		return EXIT_FAILURE;
	}
	unsigned N;
	sscanf(argv[1], "%d", &N);

	srand(time(0));

	for (unsigned first = 0; first < N; ++first){
	
		unsigned last = 0;
		unsigned second;
		bool first_second = true;
		bool any_seconds = false;
		double choice = (rand() % 100) / 100.00;
		if (choice < .7){
			std::cout << first << ":";
			any_seconds = true;
		}

		while (choice < .7){
			second = (rand() % N) + last;

			//Repeat edges are not allowed
			if (second == last) ++second;
			//Guaranteed to run at least once, as last = 0 initially
			if (second >= N) break;
			//To ensure proper placement of commas
			if (first_second){
				std::cout << second;
				first_second = false;
			} else std::cout << "," << second;
			last = second;
			choice = (rand() % 100) / 100.00;
		}
		if (any_seconds) std::cout << "\n";
	}
	return 0;
}
