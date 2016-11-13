#include "catch.hpp"

#include "shared_pointer.hpp"

SCENARIO("Default constructor, get", "[c]") {
	shared_pointer<int> shared_pointer;
	REQUIRE(shared_pointer.get() == nullptr);
}

SCENARIO("by object address constructor, getNReferences, asterisk, arrow", "[a]") {
	std::string * string = new std::string("Hello!");
	shared_pointer<std::string> shared_pointer(string);
	REQUIRE(shared_pointer.getNReferences() == 1);
	REQUIRE(*shared_pointer == "Hello!");
	REQUIRE(shared_pointer->size() == 6);
}

SCENARIO("copy", "[d]") {
	int * number = new int(8);
	shared_pointer<int> shared_pointer1(number);
	shared_pointer<int> shared_pointer2(shared_pointer1);
	shared_pointer<int> shared_pointer3;
	shared_pointer3 = shared_pointer2;
	REQUIRE(shared_pointer1.getNReferences() == 3);
	REQUIRE(shared_pointer2.getNReferences() == 3);
	REQUIRE(shared_pointer3.getNReferences() == 3);
	REQUIRE(*shared_pointer1 == 8);
	REQUIRE(*shared_pointer2 == 8);
	REQUIRE(*shared_pointer3 == 8);
}
SCENARIO("move", "[e]") {
	{
		int * number = new int(-4);
		shared_pointer<int> shared_pointer1(number);
		shared_pointer<int> shared_pointer2(std::move(shared_pointer1));
		REQUIRE(shared_pointer2.getNReferences() == 1);
		REQUIRE(*shared_pointer2 == -4);
	}
	{
		int * number = new int(-8);
		shared_pointer<int> shared_pointer1(number);
		shared_pointer<int> shared_pointer2;
		shared_pointer2 = std::move(shared_pointer1);
		REQUIRE(shared_pointer2.getNReferences() == 1);
		REQUIRE(*shared_pointer2 == -8);
	}
}
SCENARIO("swap", "[f]") {
	int * number1 = new int(-1);
	int * number2 = new int(-2);
	shared_pointer<int> shared_pointer1(number1);
	shared_pointer<int> shared_pointer2(number2);
	shared_pointer1.swap(shared_pointer2);

	REQUIRE(shared_pointer1.getNReferences() == 1);
	REQUIRE(shared_pointer2.getNReferences() == 1);
	
	REQUIRE(*shared_pointer1 == -2);
	REQUIRE(*shared_pointer2 == -1);
}
SCENARIO("reset", "[d]") {
	int * number = new int(-1);
	shared_pointer<int> shared_pointer1(number);
	shared_pointer<int> shared_pointer2(shared_pointer1);
	shared_pointer1.reset();

	REQUIRE(shared_pointer1.get() == nullptr);
	REQUIRE(shared_pointer2.getNReferences() == 1);
}
