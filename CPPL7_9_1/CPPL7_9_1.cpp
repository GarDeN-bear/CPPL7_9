#include<iostream>
#include <vector>

template<class T>
void move_vectors(T&, T&);

int main() {
	std::vector <std::string> one = { "test_string1", "test_string2" };
	std::vector <std::string> two;
	move_vectors(one, two);
}

template<class T>
void move_vectors(T& obj1, T& obj2) {
	obj2 = std::move(obj1);
	for (const auto& el : obj2) {
		std::cout << el << " ";
	}
	std::cout << std::endl;
}