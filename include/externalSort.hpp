#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <vector>
#include "person.hpp"
#include "timer.hpp"

using Occurences = std::unordered_map<person, size_t, PersonHash>;
Occurences countOccurences(std::string const & database_file_name) {
	Occurences distribution;
	std::ifstream database(database_file_name, std::ios::binary);
	while (!database.eof()) {
		person current_person;
		database >> current_person;
		auto search = distribution.find(current_person);
		if (search == distribution.end()) {
			distribution.insert({ current_person, 1 });
		}
		else {
			search->second++;
		}
	}
	database.close();
	return distribution;
}
void outputSortedDistribution(Occurences & occurences, std::string const & output_file_name)
{
	std::ofstream output_file(output_file_name, std::ios::binary);

	std::vector<person> sorted_persons;
	sorted_persons.reserve(occurences.size());
	for (auto it = occurences.begin(); it != occurences.end(); ++it) {
		sorted_persons.push_back(it->first);
	}
	std::sort(sorted_persons.begin(), sorted_persons.end(), [](person a, person b) {
		return a.name < b.name;
	});

	for (auto current_person : sorted_persons) {
		std::string str = current_person.surname + " "
			+ current_person.name + " " + current_person.year + "\r\n";
		for (size_t i = 0; i < occurences[current_person]; i++) {
			output_file.write(str.c_str(), str.size());
		}
	}
	output_file.close();
}
void externalSort(std::string const & database_file_name,
	std::string const & output_file_name, size_t const RAM) {
	Occurences occurences = countOccurences(database_file_name);
	outputSortedDistribution(occurences, output_file_name);
}
