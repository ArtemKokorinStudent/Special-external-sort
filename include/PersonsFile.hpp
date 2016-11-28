#include <fstream>
#include <string>

class Persons_File {
public:
	Persons_File() : is_empty(true), file_size(0) {
		;
	}
	std::string file_name;
	size_t file_size;
	bool is_empty;
	char * key;
	bool is_same;
	std::fstream stream;
	void openNew(std::string _file_name) {
		file_name = _file_name;
		stream.open(file_name, std::ios::out);
	}
};
