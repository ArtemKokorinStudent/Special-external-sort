#include "catch.hpp"
#include <iostream>
#include "externalSort.hpp"
size_t fileSize(std::string const & file_name) {
        std::ifstream is(file_name, std::ifstream::binary);
	is.seekg(0, is.end);
	size_t file_size = is.tellg();
	is.close();
	return file_size;
}
SCENARIO("Sort", "[s]") {
	const std::string output_file_name = "F:\\1\\sorted_database.txt";
	size_t start = clock();
	externalSort("8.txt", "F:\\1\\sorted_database.txt", 1);
	std::cout << "Sort time 8(microseconds): " << clock() - start << std::endl;
	std::cout << "File was: " << fileSize("8.txt") << std::endl;
	std::cout << "Output size: " << fileSize(output_file_name) << std::endl;
	start = clock();
	externalSort("16.txt", "F:\\1\\sorted_database.txt", 1);
	std::cout << "Sort time 15(microseconds): " << clock() - start << std::endl;
	std::cout << "File was: " << fileSize("16.txt") << std::endl;
	std::cout << "Output size: " << fileSize(output_file_name)<< std::endl;
	start = clock();
	externalSort("32.txt", "F:\\1\\sorted_database.txt", 1);
	std::cout << "Sort time 32(microseconds): " << clock() - start << std::endl;
	std::cout << "File was: " << fileSize("32.txt") << std::endl;
	std::cout << "Output size: " << fileSize(output_file_name)<< std::endl;

	const int n_persons = 422000;
	for (size_t i = 0; i < 1; i++) {
		size_t person1_i = rand() % n_persons;
		size_t person2_i = person1_i + rand() % (n_persons - person1_i);
		person person1 = readPersonFromFile(output_file_name, person1_i);
		person person2 = readPersonFromFile(output_file_name, person2_i);
		REQUIRE(person1.name <= person2.name);
	}
}
