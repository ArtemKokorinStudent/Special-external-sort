#include <string>
struct person 
{
	std::string surname;
	std::string name;
	std::string year;
};
struct PersonHash 
{
	std::size_t operator()(person const & s) const
	{
		std::size_t h1 = std::hash<std::string>{}(s.surname);
		std::size_t h2 = std::hash<std::string>{}(s.name);
		std::size_t h3 = std::hash<std::string>{}(s.year);
		return h1 ^ ((h2 ^ (h3 << 1)) << 1); // or use boost::hash_combine
	}
};
bool operator==(const person & left, const person & right) {
	return left.name == right.name && left.surname == right.surname && left.year == right.year;
}
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
person readPersonFromFile(std::string const & file_name, size_t const index) {
	person result;
	std::ifstream file(file_name);
	for (size_t i = 0; i < index + 1; i++) {
		file >> result;
	}
	file.close();
	return result;
}
