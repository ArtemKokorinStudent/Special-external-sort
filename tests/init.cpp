#include "catch.hpp"
#include <iostream>
//#include "Database_Creator.hpp"
#include "Database_Sorter.hpp"

person readPerson(std::string file_name, size_t index) {
	person result;
	std::ifstream file(file_name);
	for (size_t i = 0; i < index + 1; i++) {
		file >> result;
	}
	file.close();
	return result;
}
/*bool isANotMoreThanB(person A, person B) {
	for (size_t i = 0; i < A.name.length(); i++) {
		char A_char = A.name[i];
		char B_char = (i < B.name.length()) ? B.name[i] : ' ';
		if (letterI(A.name[i], i == 0) < letterI(B.name[i], i == 0)) {
			return true;
		}
		else {
			if (A.name[i] != B.name[i]) {
				return false;
			}
		}
	}
	return true;
}*/

SCENARIO("Sort", "[s]") {
	size_t n_persons = 200;
	//system("start www.cyberforum.ru/cpp-beginners/thread82643.html#post458604");
	size_t RAM_amount = 1;
	std::string names_file_name = "F:\\1\\names.txt";
	std::string surnames_file_name = "F:\\1\\surnames.txt";
	std::string database_file_name = "F:\\1\\database.txt";
	std::string output_file_name = "F:\\1\\sorted_database.txt";

	//Database_Creator database_creator(database_file_name, names_file_name, surnames_file_name, n_persons);
	Database_Sorter database_sorter(database_file_name, output_file_name, RAM_amount);
	size_t start = clock();
	database_sorter.sortDatabase();
	size_t result = clock() - start;
	database_sorter.closeDatabase();
	std::cout << result << std::endl;

	for (size_t i = 0; i < 0; i++) {
		size_t person1_i = rand() % n_persons;
		size_t person2_i = person1_i + rand() % (n_persons - person1_i);
		person person1 = readPerson(output_file_name, person1_i);
		person person2 = readPerson(output_file_name, person2_i);
		//REQUIRE(isANotMoreThanB(person1, person2));
	}
}
