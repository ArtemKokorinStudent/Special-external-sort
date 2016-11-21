#include <string>
#include <fstream>
#include <sstream>
#include <vector>
char russian_letters[6];
size_t russianLetterI(const char letter, const bool is_capital) {
	int first_letter_code = static_cast<int>(is_capital ? russian_letters[0] : russian_letters[1]);
	if (letter > (is_capital ? russian_letters[2] : russian_letters[3])) {
		size_t result = static_cast<int>(letter) - first_letter_code + 2;
		return result;
	}
	else {
		if (letter == (is_capital ? russian_letters[4] : russian_letters[5])) {
			return 7;
		}
		size_t result = static_cast<int>(letter) - first_letter_code + 2;
		return result;
	}
}
size_t letterI(const char letter, const bool is_capital) {
        int first_letter_code = static_cast<int>(is_capital ? 'A' : 'a');
	size_t result = static_cast<int>(letter) - first_letter_code + 1;
}
struct person {
	std::string surname;
	std::string name;
	size_t year;
	size_t i(size_t sort_i) const {
		if (sort_i < surname.length()) {
			return letterI(surname[sort_i], sort_i == 0);
		}
		else {
			return 0;
		}
	}
};
std::ostream & operator<<(std::ostream & output, person const & _person)
{
	output << _person.surname << " ";
	output << _person.name << " ";
	output << _person.year;
	return output;
}
std::istream & operator>>(std::istream & input, person & _person)
{
	input >> _person.surname;
	input >> _person.name;
	input >> _person.year;
	return input;
}
using Buckets = std::vector<std::vector<person>>;
using Persons = std::vector<person>;
class Persons_File {
public:
	Persons_File() : is_empty(true), file_size(0) {
		;
	}
	std::string file_name;
	bool is_empty;
	size_t file_size;
	std::fstream stream;
	void openNew(std::string _file_name) {
		file_name = _file_name;
		stream.open(file_name, std::ios::out);
	}
	void addToSize(person _person) {
		file_size += _person.surname.size();
		file_size += _person.name.size();
		file_size += sizeof(_person.year);
		file_size += 1 + 1 + 2;
	}
};
using Output_Files = std::vector<std::ofstream>;

class Database_Sorter {
	bool is_database_empty;
	std::string database_file_name;
	std::string vault_file_name;
public:
	Database_Sorter(std::string database_file_name, std::string output_file_name, size_t _RAM_amount)
		: database_file_name(database_file_name),
		database_file(database_file_name),
		output_file(output_file_name),
		RAM_amount(_RAM_amount * 1024 * 1024),
		is_database_empty(true)
	{
		vault_file_name = "F:\\1\\temp_files\\";
	}
	void sortDatabase() {
		sortFile(database_file, database_file_name, RAM_amount + 1, 0);
	}
	
	~Database_Sorter() {
		database_file.close();
		output_file.close();
	}
private:
	void sortFile(std::ifstream & file, std::string file_name, size_t file_size, size_t sort_i) {
		if (file_size < RAM_amount) {
			RAMsort(file, sort_i);
		}
		else {
			std::vector<Persons_File> persons_files = stuffPersonsToFiles(file, file_name, sort_i);
			for (size_t i = 0; i < persons_files.size(); i++) {
				if (persons_files[i].file_size != 0) {
					std::ifstream temp_file(persons_files[i].file_name);
					sortFile(temp_file, persons_files[i].file_name, persons_files[i].file_size, sort_i + 1);
					temp_file.close();
				}
			}
		}
	}

	void RAMsort(std::ifstream & file, size_t sort_i) {
		persons_outputted = 0;
		persons.clear();
		readFileIntoRAM(file);
		sortPersons(persons, sort_i);
	}
	void readFileIntoRAM(std::ifstream & file) {
		while (!file.eof()) {
			person current_person;
			file >> current_person;
			persons.push_back(current_person);
		}
	}
	void sortPersons(Persons const & entered_persons, size_t sort_i) {
		Buckets buckets = stuffPersonsToBuckets(entered_persons, sort_i);
		if (isOnlyOneBucketFull(buckets, entered_persons, sort_i)) {
			outputBucket(entered_persons, output_file);
		}
		else {
			sortBuckets(buckets, sort_i + 1);
		}
	}
	Buckets stuffPersonsToBuckets(Persons const & persons, size_t sort_i) {
		Buckets buckets(34);
		for (auto person : persons) {
			size_t currentI = person.i(sort_i);
			buckets[currentI].push_back(person);
		}
		return buckets;
	}
	bool isOnlyOneBucketFull(Buckets const & buckets, Persons const & persons, size_t sort_i) {
		size_t first_bucket_i = persons[0].i(sort_i);
		return buckets[first_bucket_i].size() == persons.size();
	}
	void outputBucket(Persons const & bucket, std::ofstream & sorted_persons_file) {
		for (auto person : bucket) {
			outputPerson(person);
		}
	}
	void outputPerson(person _person) {
		if (is_database_empty) {
			is_database_empty = false;
		}
		else {
			output_file << std::endl;
		}
		output_file << _person;
		persons_outputted++;
	}
	void sortBuckets(Buckets const & buckets, size_t sort_i) {
		for (auto bucket : buckets) {
			if (!bucket.empty()) {
				sortPersons(bucket, sort_i);
			}
		}
	}

	std::vector<Persons_File> stuffPersonsToFiles(std::ifstream & base_file, std::string base_file_name, size_t sort_i) {
		std::vector<Persons_File> files = createDerivedFiles(base_file_name);
		while (!base_file.eof()) {
			person current_person;
			base_file >> current_person;
			size_t currentI = current_person.i(sort_i);
			if (files[currentI].is_empty) {
				files[currentI].is_empty = false;
			}
			else {
				files[currentI].stream << std::endl;
			}
			files[currentI].stream << current_person;
			files[currentI].addToSize(current_person);
		}
		for (size_t i = 0; i < files.size(); i++) {
			files[i].stream.close();
		}
		return files;
	}
	std::vector<Persons_File> createDerivedFiles(std::string base_file_name) {
		std::vector<Persons_File> files(34);
		for (size_t i = 0; i < files.size(); i++) {
			std::stringstream string_stream;
			std::string str;
			if (base_file_name == database_file_name) {
				string_stream << vault_file_name << i << ".txt";
			}
			else {
				string_stream << base_file_name << "_" << i << ".txt";
			}
			string_stream >> str;
			files[i].openNew(str);
		}
		return files;
	}
	std::vector<person> persons;
	size_t persons_outputted;
	std::ifstream database_file;
	std::ofstream output_file;
	size_t RAM_amount;
};
