#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <vector>
#include "person.hpp"
#include <ctime>

using Files = std::unordered_map<std::string, std::ofstream>;
using String = std::string const &;
void append(String file_name, std::ofstream & to) {
	std::ifstream file(file_name);
	char ch;
	while (file.get(ch)) {
		to.put(ch);
	}
	file.close();
}
Files stuffToFiles(String database_file_name, String vault_name) {
	Files files;
	std::ifstream database(database_file_name);
	while (!database.eof()) {
		person current_person;
		database >> current_person;
		auto search = files.find(current_person.name);
		if (search == files.end()) {
			files.insert(std::make_pair(current_person.name,
				std::ofstream(vault_name + current_person.name + ".txt")));
			files[current_person.name] << current_person;
		}
		else {
			(*search).second << std::endl << current_person;
		}
	}
	for (auto it = files.begin(); it != files.end(); ++it) {
		(*it).second.close();
	}
	database.close();
	return files;
}
void collect(Files & files, String output_file_name, String vault_name) {
	std::ofstream output_file(output_file_name);
	std::vector<std::string> sorted_names;
	sorted_names.reserve(files.size());
	for (auto it = files.begin(); it != files.end(); ++it) {
		sorted_names.push_back((*it).first);
	}
	std::sort(sorted_names.begin(), sorted_names.end());
	size_t start = clock();
	for (auto file_name : sorted_names) {
		append(vault_name + file_name + ".txt", output_file);
	}
	size_t result = clock() - start; //4s (debug, on)
	output_file.close();
}
void externalSort(String database_file_name, String output_file_name, size_t RAM, String vault_name) {
	Files set = stuffToFiles(database_file_name, vault_name);
	collect(set, output_file_name, vault_name);
}
