#include <iostream>
#include <string>
#include <unordered_set>

#include "ordered_set.hpp"

//https://ideone.com/F0V42m
//g++ -std=c++11 -o ordered_set ordered_set.cpp

int main()
{
	std::set<std::string> a1 {"a", "b"};
	std::set<std::string> b1 {"b", "a"};
	std::cout << std::boolalpha << (a1 == b1) << std::endl;

	std::cout << "Set a1 contains:";
	for (auto it=a1.begin(); it!=a1.end(); ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << '\n';

	std::cout << "Set b1 contains:";
	for (auto it=b1.begin(); it!=b1.end(); ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << '\n';



	std::unordered_set<std::string> a2 {"a", "b"};
	std::unordered_set<std::string> b2 {"b", "a"};
	std::cout << std::boolalpha << (a2 == b2) << std::endl;


	std::cout << "Unordered Set a2 contains:";
	for (auto it=a2.begin(); it!=a2.end(); ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << '\n';

	std::cout << "Unordered Set b2 contains:";
	for (auto it=b2.begin(); it!=b2.end(); ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << '\n';




	util::ordered_set<std::string> a3 {"a", "b"};
	util::ordered_set<std::string> b3 {"b", "a"};
	std::cout << std::boolalpha << (a3 == b3) << std::endl;


	std::cout << "Ordered Set a3 contains:";
	for (auto it=a3.begin(); it!=a3.end(); ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << '\n';

	std::cout << "Ordered Set b3 contains:";
	for (auto it=b3.begin(); it!=b3.end(); ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << '\n';
}


