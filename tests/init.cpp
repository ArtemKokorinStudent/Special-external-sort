#include "catch.hpp"
#include <iostream>
//#include "Database_Creator.hpp"
#include "Database_Sorter.hpp"

person readPerson(std::string const & file_name, size_t const index) {
	person result;
	std::ifstream file(file_name);
	for (size_t i = 0; i < index + 1; i++) {
		file >> result;
	}
	file.close();
	return result;
}
bool isANotMoreThanB(person const & A, person const & B) {
        char * A_name = A.getName();
        char * B_name = B.getName();
	for (size_t i = 0; i < A.name_length; i++) {
		char A_char = A_name[i];
		char B_char = (i < B.name_length) ? B_name[i] : ' ';
		if (letterI(A_name[i], i == 0) < letterI(B_name[i], i == 0)) {
			return true;
		}
		else {
			if (A_name[i] != B_name[i]) {
				return false;
			}
		}
	}
        delete []A_name;
        delete []B_name;
	return true;
}

SCENARIO("Sort", "[s]") {
	size_t n_persons = 200;
	//system("start www.cyberforum.ru/cpp-beginners/thread82643.html#post458604");
	size_t RAM_amount = 1;
	std::string names_file_name = "F:\\1\\names.txt";
	std::string surnames_file_name = "F:\\1\\surnames.txt";
	std::string database_file_name = "8.txt";
	std::string output_file_name = "F:\\1\\sorted_database.txt";

	//Database_Creator database_creator(database_file_name, names_file_name, surnames_file_name, n_persons);
	Database_Sorter database_sorter1("8.txt", "1", 1);
        Database_Sorter database_sorter2("16.txt", "2", 4);
        Database_Sorter database_sorter3("16.txt", "3", 17);
	size_t start = clock();
	database_sorter1.sortDatabase();
	database_sorter2.sortDatabase();
	database_sorter3.sortDatabase();
	size_t result = clock() - start;
	database_sorter1.closeDatabase();
	database_sorter2.closeDatabase();
	database_sorter3.closeDatabase();
	std::cout << "Result " << result << std::endl;

	for (size_t i = 0; i < 100; i++) {
		size_t person1_i = rand() % n_persons;
		size_t person2_i = person1_i + rand() % (n_persons - person1_i);
		person person1 = readPerson("1", person1_i);
		person person2 = readPerson("1", person2_i);
		REQUIRE(isANotMoreThanB(person1, person2));
	}
}
