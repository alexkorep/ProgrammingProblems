// Problem1Mb.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <assert.h>
#include <iostream>
#include <random>
#include <algorithm>

static const int cs_memorySize = 1024*1024*8*100; // 100 megabytes
//typedef std::bitset<cs_memorySize*8> Memory;
typedef std::vector<char> Memory;

// e.g. if base is 4 bits:
// 0xxxx - 0 to 15 values
// 10xxxx - 16 to 31 values
// 110xxxx - 32 to 47 values
// 1110xxxx - 48 to 63 values, and so on
class HuffmanAlgo 
{
public:
	// Adds |value| to the |pos| position of |memory|
	// |base| - how many bits are stored in huffman tree leaf
	// returns |pos| - new position behind endoded value.
	static void encode(Memory& memory, int& pos, const int value, const int base)
	{
		const int numberOfOnes = value / (1 << base);
		for (int i = 0; i < numberOfOnes; ++i)
		{
			memory[pos] = 1;
			++pos;
		}
		memory[pos] = 0;
		++pos;

		int lowerValue = value % (1 << base);
		for (int i = 0; i < base; ++i)
		{
			memory[pos] = lowerValue & 0x1; // We keep bits in reversed order (Big Endian), maybe change in the futue
			++pos;
			lowerValue = lowerValue >> 1;
		}
	}

	// Extracts value from the |pos| position of |memory|
	// |base| - how many bits are stored in huffman tree leaf
	static int decode(const Memory& memory, int& pos, const int base)
	{
		int numberOfOnes = 0;
		while (memory[pos])
		{
			++numberOfOnes;
			++pos;
		}
		++pos; // skip 0;

		int val = (0x1 << base)*numberOfOnes;

		for (int i = 0; i < base; ++i)
		{
			val += memory[pos] << i; // Remember - Big Endian
			++pos;
		}

		return val;
	}
};

void testEncode(const int base, const int* values, const int size)
{
	Memory memory;
	memory.resize(cs_memorySize);

	int pos = 0;
	for (int i = 0; i < size; ++i)
	{
		HuffmanAlgo::encode(memory, pos, values[i], base);
	}
	std::cout << "Base: " << base;
	std::cout << ", memory (bits): " << pos;
	std::cout << ", memory (Bytes): " << pos/8 << std::endl;
}

int main()
{
	std::random_device rd;
	std::default_random_engine generator(rd);
	std::uniform_int_distribution<int> distribution(0, 99999999);

	const int len = 1000000;
	//const int len = 10;

	//int testValues[len] = {0};
	int* testValues = new int[len];

	for (int i = 0; i < 10; ++i)
	{
		for (int i = 0; i < len; ++i)
		{
			const int value = distribution(generator); // 0..99,999,999
			testValues[i] = static_cast<int>(value);
		}

		std::sort(testValues, testValues + len);

		// Build array of differences
		int prevValue = 0;
		for (int i = 0; i < len; ++i)
		{
			const int prev = testValues[i];
			testValues[i] = testValues[i] - prevValue;
			prevValue = prev;
		}

		/*
		for (int base = 5; base < 8; ++base)
		{
			testEncode(base, testValues, len);
		}
		*/
		// base = 6
		testEncode(6, testValues, len);
	}

	delete[] testValues;

	// 1015174
	// 1015159
	// 1015126
	// 1015169
	// 1015119
	// 1015094
	// 1015057
	// 1015210

	/*
	Memory memory;
	memory.resize(cs_memorySize);

	int pos = 0;
	const int base = 4;
	for (int i = 0; i < _countof(testValues); ++i)
	{
		HuffmanAlgo::encode(memory, pos, testValues[i], base);
	}
	std::cout << pos << std::endl;

	pos = 0;
	for (int i = 0; i < _countof(testValues); ++i)
	{
		const int value = HuffmanAlgo::decode(memory, pos, base);
		assert(testValues[i] == value);
	}
	*/

	char c;
	std::cin >> c;

	return 0;
}

