#include <iostream>
#include <chrono>
#include <ctime>

struct Timer {
	std::clock_t time;
	std::clock_t result;
	void start() {
		time = std::clock();
	}
	void measure() {
		result = 1000.0 * (std::clock() - time) / CLOCKS_PER_SEC;
	}
} timer;
