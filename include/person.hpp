#include <string>
struct person {
	std::string surname;
	std::string name;
	std::string year;
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
person readPersonFromFile(std::string file_name, size_t index) {
	person result;
	std::ifstream file(file_name);
	for (size_t i = 0; i < index + 1; i++) {
		file >> result;
	}
	file.close();
	return result;
}
