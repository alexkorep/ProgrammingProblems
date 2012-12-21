// NarcissicNumbers.cpp : Defines the entry point for the console application.
//
/*
http://programmingpraxis.com/2012/12/14/115132219018763992565095597973971522401/

115132219018763992565095597973971522401
December 14, 2012
Today we have an exercise, a solution, and a question I don’t know the answer to. 
The exercise is to write a program that lists the narcissistic numbers in which the sum of the nth powers 
of the digits of an n-digit number is equal to the number. For instance, 153 is a narcissistic number of 
length 3 because 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153. The largest decimal narcissistic number is the 
39-digit number that is the title of today’s exercise.

Your task is to write a program to find narcissistic numbers. When you are finished, you are welcome to 
read or run a suggested solution, or to post your solution or discuss the exercise in the comments below.

Pages: 1 2
*/

#include <iostream>
#include <vector>

typedef unsigned int uint;

typedef std::vector<uint> PartialSolution;

uint pow(uint base, uint p) {
	uint result = 1;
	for (uint i = 0; i < p; ++i) {
		result *= base;
	}
	return result;
}

void findNumber(uint len, const PartialSolution& partialSolution) {
	// check previous sum
	uint sum = 0;

	uint minNumPartial = 0;
	for (uint k = 0; k < partialSolution.size(); ++k) {
		sum += pow(partialSolution[k], len);
		minNumPartial = minNumPartial*10 + partialSolution[k];
	}

	if (len == partialSolution.size()) {
		if (sum && sum == minNumPartial) {
			// Result found!
			std::cout << minNumPartial << std::endl;
		}
		return;
	}

	uint maxNum = minNumPartial;
	uint minNum = minNumPartial;
	for (uint j = partialSolution.size(); j < len; ++j) {
		minNum = minNum*10 + 0;
		maxNum = maxNum*10 + 9;
	}

	// check predicted min/max values for this number
	for (uint i = 0; i <= 9; ++i) {
		uint minPredicted = minNumPartial*10 + i;
		uint maxPredicted = minPredicted;
		for (uint j = partialSolution.size() + 1; j < len; ++j) {
			minPredicted = minPredicted*10 + 0;
			maxPredicted  = maxPredicted*10 + 9;
		}

		if (minPredicted < minNum || maxPredicted > maxNum) {
			// bad candidate
			continue;
		}

		if (0 == i && partialSolution.empty()) {
			// don't consider numbers with leading 0
			continue;
		}

		PartialSolution sol1 = partialSolution;
		sol1.push_back(i);
		findNumber(len, sol1);
	}
}

void findNarcissicNumbers(uint len) {

	PartialSolution partialSolution;
	findNumber(len, partialSolution);
}

int main()
{
	for (uint i = 3; i <= 9; ++i) {
		findNarcissicNumbers(i);
	}

	std::cout << "done!";
	char ch;
	std::cin >> ch;

	return 0;
}

