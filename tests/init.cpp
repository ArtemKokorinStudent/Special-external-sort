#include "catch.hpp"
#include <iostream>
#include "Database_Creator.hpp"
#include "Database_Sorter.hpp"

SCENARIO("Sort", "[s]") {
	Database_Creator database_creator(3000);
	Database_Sorter database_sorter("F:\\1\\database.txt", "F:\\1\\sorted_database.txt", 4000);
	database_sorter.sortDatabase();
}
