#include "catch.hpp"
#include <iostream>
#include "externalSort.hpp"

SCENARIO("Sort", "[s]") {
	const std::string output_file_name = "F:\\1\\sorted_database.txt";
	size_t start = clock();
	externalSort("8.txt", "F:\\1\\sorted_database.txt", 1);
	externalSort("16.txt", "F:\\1\\sorted_database.txt", 1);
	externalSort("32.txt", "F:\\1\\sorted_database.txt", 1);
	std::cout << "Sort time: " << clock() - start << std::endl;

	const int n_persons = 300;
	for (size_t i = 0; i < 100; i++) {
		size_t person1_i = rand() % n_persons;
		size_t person2_i = person1_i + rand() % (n_persons - person1_i);
		person person1 = readPersonFromFile(output_file_name, person1_i);
		person person2 = readPersonFromFile(output_file_name, person2_i);
		REQUIRE(person1.name <= person2.name);
	}
}
