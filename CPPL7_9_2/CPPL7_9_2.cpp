#include <iostream>
#include "big_integer.h"

int main() {

	auto number1 = big_integer("114575");
	auto number2 = big_integer("78524");
	auto result1 = number1 + number2;
	auto result2 = number1 * number2;
	std::cout << result1 << std::endl; // 193099
	std::cout << result2 << std::endl; // 8996887300
	number1 = number2;
	std::cout << number1 << " " << number2 << std::endl; // 78524 78524
}