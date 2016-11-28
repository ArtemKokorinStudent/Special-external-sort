#include <string>
#include <cstring>
#include <utility>
#include <algorithm>
#include <unordered_map>
std::unordered_map<std::string, size_t> map;
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
        person(person const & _person) : str(_person.str), name_i(_person.name_i), name_length(_person.name_length) {
               ;
        }
        person(person && _person) : str(_person.str), name_i(_person.name_i), name_length(_person.name_length) {
               _person.str = nullptr;
        }
        person & operator=(person && _person) {
	       if (this != &_person) {
                        std::swap(str, _person.str);
                        std::swap(name_i, _person.name_i);
                        std::swap(name_length, _person.name_length);
	       }
	       return *this; //?
        }
	size_t i(size_t sort_i) const {
		/*if (map.find(str) == end()){
			map.insert(str, map.size());	
		} else{
			map.find(str).	
		}*/
		if (sort_i < name_length) {
			return letterI(str[name_i + sort_i], sort_i == 0);
		}
		else {
			return 0;
		}
	}
	char * getName() const {
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
	std::string str1, str2, str3;
        input >> str1;
	_person.name_i = str1.length() + 1;
	input >> str2;
	_person.name_length = str2.length();
	input >> str3;
        _person.putStr(str1 + " " + str2 + " " + str3);
	
	return input;
}
