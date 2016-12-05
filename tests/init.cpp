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
size_t fileStr(std::string const & file_name) {
	std::ifstream is(file_name, std::ifstream::binary);
	size_t res = 0;
	while (!is.eof()) {
		person p;
		is >> p;
		res++;
	}
	is.close();
	return res;
}
void testingSort(std::string const & file_name, std::string const & output_file_name, size_t RAM) {
	std::cout << std::endl;
	timer.start();
	externalSort(file_name, output_file_name, RAM);
	timer.measure();
	std::cout << "Sort time of " << file_name << "(ms): " << timer.result << std::endl;
	std::cout << "File was: " << fileSize(file_name) << " bytes." << std::endl;
	std::cout << "Output size: " << fileSize(output_file_name) << " bytes." << std::endl;
	std::cout << std::endl;
}
SCENARIO("Sort", "[s]") {
	const std::string output_file_name = "F:\\1\\sorted_database";
	testingSort("8.txt", output_file_name, 1);
	testingSort("16.txt", output_file_name, 4);
	testingSort("32.txt", output_file_name, 17);

	const int n_persons = 422000;
	for (size_t i = 0; i < 1; i++) {
		size_t person1_i = rand() % n_persons;
		size_t person2_i = person1_i + rand() % (n_persons - person1_i);
		person person1 = readPersonFromFile(output_file_name, person1_i);
		person person2 = readPersonFromFile(output_file_name, person2_i);
		REQUIRE(person1.name <= person2.name);
	}
}
