#include <sstream>
#include <vector>
#include <limits>
#include "person.hpp"
#include "PersonsFile.hpp"

using Buckets = std::vector<std::vector<person>>;
using Persons = std::vector<person>;
using Output_Files = std::vector<std::ofstream>;

class Database_Sorter {
	bool is_database_empty;
	std::string database_file_name;
	std::string vault_name;
public:
	Database_Sorter(std::string database_file_name, std::string output_file_name, size_t _RAM_amount, 
		std::string _vault_name = "F:\\1\\temp_files\\")
		: database_file_name(database_file_name),
		output_file(output_file_name),
		RAM_amount(_RAM_amount * 1024 * 1024),
		is_database_empty(true),
		vault_name(_vault_name)
	{
		;
	}
	void sortDatabase() {
                std::fstream database_file(database_file_name);
		database_file.seekg(0, std::ios::end);
		size_t database_size = static_cast<size_t>(database_file.tellg());
                database_file.close();
		sortFile(database_file_name, database_size, 0);
	}
	void closeDatabase() {
		output_file.close();
	}
private:
	void outputFile(std::string const & file_name) {
		if (is_database_empty) {
			is_database_empty = false;
		}
		else {
			output_file << std::endl;
		}
		std::ifstream file(file_name);
		char ch;
		while (file.get(ch)) {
			output_file.put(ch);
		}
		file.close();
	}
	void sortFile(std::string const & file_name, size_t const file_size, size_t const sort_i) {
		if (file_size < RAM_amount) {
			RAMsort(file_name, sort_i);
		}
		else {
			std::vector<Persons_File> persons_files = stuffPersonsToFiles(file_name, sort_i);
			for (size_t i = 0; i < persons_files.size(); i++) {
				if (!persons_files[i].is_empty) {
					if (persons_files[i].is_same) {
						outputFile(persons_files[i].file_name);
					}
					else {
						sortFile(persons_files[i].file_name, persons_files[i].file_size, sort_i + 1);
					}
				}
			}
		}
	}
	
	void RAMsort(std::string const & file_name, size_t const sort_i) {
		persons.clear();
		readFileIntoRAM(file_name);
		sortPersons(persons, sort_i);
	}
	void readFileIntoRAM(std::string const & file_name) {
		std::ifstream is(file_name, std::ifstream::binary);
		if (is) {
			// get length of file:
			is.seekg(0, is.end);
			size_t length = is.tellg();
			is.seekg(0, is.beg);

			char * buffer = new char[length];
			// read data as a block:
			is.read(buffer, length);
			is.close();
			size_t previous_i = 0;
			size_t i = 0;
			bool state = false;
			person current_person;
			while (i < length) {
				if (buffer[i] == ' ') {
					if (!state) {
						current_person.name_i = i - previous_i + 1;
						state = true;
					}
					else {
						current_person.name_length = i - previous_i - current_person.name_i;
						state = false;
					}
				}
				else if (buffer[i] == '\r') {
					current_person.str = new char[i - previous_i + 1];
					strncpy(current_person.str, &(buffer[previous_i]), i - previous_i);
					current_person.str[i - previous_i] = '\0';
					persons.push_back(current_person);
					
					previous_i = i + 2;
					i++;
				}
				i++;
			}
			persons.shrink_to_fit();
			delete[] buffer;
		}
	}
	void sortPersons(Persons & entered_persons, size_t const sort_i) {
		size_t full_bucket_i;
		Buckets buckets = stuffPersonsToBuckets(entered_persons, sort_i, full_bucket_i);
		if (full_bucket_i != std::numeric_limits<size_t>::max()) {
			outputBucket(buckets[full_bucket_i], output_file);
		}
		else {
			for (auto bucket : buckets) {
				if (!bucket.empty()) {
					sortPersons(bucket, sort_i + 1);
				}
			}
		}
	}
	Buckets stuffPersonsToBuckets(Persons & persons, size_t const sort_i, size_t & full_bucket_i) {
		bool is_same = true;
		
		full_bucket_i = persons[0].i(sort_i);
		size_t persons_size = persons.size();
		Buckets buckets(n_literals);
		for (auto person : persons) {
			size_t currentI = person.i(sort_i);
			//full_bucket_i = currentI;
			
			buckets[currentI].push_back(person());
			std::swap(buckets[currentI], person);
			if (is_same) {
				if (full_bucket_i != currentI) {
					is_same = false;
				}
			}
		}
		persons.clear();
		persons.shrink_to_fit();
		if (!is_same) {
			full_bucket_i = std::numeric_limits<size_t>::max();
		}
		
		return buckets;
	}
	void outputBucket(Persons const & bucket, std::ofstream & sorted_persons_file) {
		for (auto person : bucket) {
			outputPerson(person);
		}
	}
	void outputPerson(person const & _person) {
		if (is_database_empty) {
			is_database_empty = false;
		}
		else {
			output_file << std::endl;
		}
		output_file << _person.str;
	}

	std::vector<Persons_File> stuffPersonsToFiles(
		std::string base_file_name, size_t sort_i) {
		std::ifstream base_file(base_file_name);
		bool is_same = true;
		std::vector<Persons_File> files(n_literals);

		person current_person;
		size_t currentTargetFileI;
		std::string str1, str2, str3;
		while (!base_file.eof()) {
			base_file >> current_person;
			currentTargetFileI = current_person.i(sort_i);
			if (files[currentTargetFileI].is_empty) {
				files[currentTargetFileI].openNew(calcDerivedFileName(base_file_name, currentTargetFileI));
				files[currentTargetFileI].is_empty = false;
				files[currentTargetFileI].key = current_person.getName();
				files[currentTargetFileI].is_same = true;
			}
			else {
				if (files[currentTargetFileI].is_same) {
					char * temp = current_person.getName();
					if (strcmp(files[currentTargetFileI].key, temp) != 0) { //B
						files[currentTargetFileI].is_same = false;
					}
                                        delete []temp;
				}
				files[currentTargetFileI].stream << std::endl;
			}
			files[currentTargetFileI].stream << current_person;
		}
		for (size_t i = 0; i < files.size(); i++) {
			if (!files[i].is_empty) {
				files[i].file_size = static_cast<size_t>(files[i].stream.tellg());
                                delete []files[i].key;
			}
			files[i].stream.close();
		}
		base_file.close();
		return files;
	}
	std::string calcDerivedFileName(const std::string & base_file_name, size_t const file_i) {
		std::string derived_file_name;
		if (base_file_name == database_file_name) {
			derived_file_name = vault_name + static_cast<char>(file_i + 64) + ".txt";
		}
		else {
			derived_file_name = base_file_name + static_cast<char>(file_i + 64) + ".txt";
		}
		return derived_file_name;
	}

	std::vector<person> persons;
	//std::ifstream database_file;
	std::ofstream output_file;
	const size_t RAM_amount;
};
//memory: max 27 files, 
