#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Database_Creator {
public:
	std::ofstream file;
	Database_Creator(size_t n_people) : file("F:\\1\\database.txt") {
		clearOutputFile();
		fillNames();
		fillSurnames();
		srand(time(0));
		for (size_t i = 0; i < n_people; i++) {
			file << surnames[rand() % surnames.size()] << " "
				<< names[rand() % names.size()] << " "
				<< 1934 + rand() % 80;
			if (i != n_people - 1) {
				file << std::endl;
			}
			else {
				//file << "!";
			}
		}
		file.close();
	}
private:
	void clearOutputFile() {
		std::ofstream file("F:\\1\\database.txt");
		file.close();
	}
	void fillNames() {
		std::ifstream names_file("F:\\1\\names.txt");
		std::string string;
		while (!names_file.eof()) {
			names_file >> string;
			names.push_back(string);
		}
		names_file.close();
	}
	void fillSurnames() {
		std::ifstream surnames_file("F:\\1\\surnames.txt");
		std::string string;
		while (!surnames_file.eof()) {
			surnames_file >> string;
			surnames.push_back(string);
		}
		surnames_file.close();
	}
	std::vector<std::string> names;
	std::vector<std::string> surnames;
};
