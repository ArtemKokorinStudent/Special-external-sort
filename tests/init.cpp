#include "catch.hpp"
#include <iostream>
#include "Database_Creator.hpp"
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
bool isALessThanB(char A, char B, bool is_capital) {
	std::string alphabet;
	if (is_capital) {
		alphabet = " АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
	}
	else {
		alphabet = " абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	}
	size_t A_i;
	size_t B_i;
	for (size_t i = 0; i < alphabet.size(); i++) {
		if (alphabet[i] == A) {
			A_i = i;
		}
		if (alphabet[i] == B) {
			B_i = i;
		}
	}
	return A_i < B_i;
}
bool isANotMoreThanB(person A, person B) {
	for (size_t i = 0; i < A.surname.length(); i++) {
		char A_char = A.surname[i];
		char B_char = (i < B.surname.length()) ? B.surname[i] : ' ';
		if (isALessThanB(A.surname[i], B.surname[i], i == 0)) {
			return true;
		}
		else {
			if (A.surname[i] != B.surname[i]) {
				return false;
			}
		}
	}
	return true;
}

SCENARIO("Sort", "[s]") {
	size_t n_persons = 10000000;
	size_t RAM_amount = 40 * 1000 * 1000;
	std::string names_file_name = "F:\\1\\names.txt";
	std::string surnames_file_name = "F:\\1\\surnames.txt";
	std::string database_file_name = "F:\\1\\database.txt";
	std::string output_file_name = "F:\\1\\sorted_database.txt";
	{
		//Database_Creator database_creator(database_file_name, names_file_name, surnames_file_name, n_persons);
		Database_Sorter database_sorter(database_file_name, output_file_name, RAM_amount);
		size_t start = clock();
		database_sorter.sortDatabase();
		size_t result = clock() - start;
		std::cout << result << std::endl;
		system("pause");
	}
	for (size_t i = 0; i < 0; i++) {
		size_t person1_i = rand() % n_persons;
		size_t person2_i = person1_i + rand() % (n_persons - person1_i);
		person person1 = readPerson(output_file_name, person1_i);
		person person2 = readPerson(output_file_name, person2_i);
		REQUIRE(isANotMoreThanB(person1, person2));
	}
}
