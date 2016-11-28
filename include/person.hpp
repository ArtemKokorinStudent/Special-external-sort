#include <string>
#include <cstring>
#include <utility>
#include <algorithm>

const size_t n_literals = 27;
size_t letterI(const char letter, const bool is_capital) {
	int first_letter_code = static_cast<int>(is_capital ? 'A' : 'a');
	size_t result = static_cast<int>(letter) - first_letter_code + 1;
	return result;
}
struct person {
	char * str;
	unsigned char name_i;
	unsigned char name_length;
        person() : str(nullptr) {
               ;
        }
        person(person const & _person) {
               str = _person.str;
               name_i = _person.name_i;
               name_length = _person.name_length;
        }
        person(person && _person) : str(_person.str), name_i(_person.name_i), name_length(_person.name_length) {
               _person.str = nullptr;
        }
        person & operator=(person && _person) {
	       if (this != &_person) {
		        (person(std::move(_person))).swap(*this);
	       }
	       return *this;
        }
	size_t i(size_t sort_i) const {
		if (sort_i < name_length) {
			return letterI(str[name_i + sort_i], sort_i == 0);
		}
		else {
			return 0;
		}
	}
	char * getName() {
		char * temp = new char[name_length + 1];
		strncpy(temp, &(str[name_i]), name_length);
		temp[name_length] = '\0';
		return temp;
	} //Boost
        void putStr(std::string const & _str) {
                str = new char[_str.length() + 1];
		strncpy(str, _str.c_str(), _str.length());
		str[_str.length()] = '\0';
        }
	~person() {
		delete[] str;
	}
};
std::ostream & operator<<(std::ostream & output, person const & _person)
{
	output << _person.str << " ";
	return output;
}
std::istream & operator>>(std::istream & input, person & _person)
{
	input >> _person.str;
	return input;
}
