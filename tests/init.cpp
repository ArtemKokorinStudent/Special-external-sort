#include "catch.hpp"

#include "shared_pointer.hpp"

SCENARIO("Default constructor, get", "[c]") {
	shared_pointer<int> shared_pointer;
	REQUIRE(shared_pointer.get() == nullptr);
}

SCENARIO("T * constructor, getNReferences ", "[a]") {
	shared_pointer<std::string> shared_pointer(new std::string("Hello!"));
	REQUIRE(shared_pointer.getNReferences() == 1);
}
