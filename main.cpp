/*
 * main.cpp
 *
 *  Created on: Sep 29, 2022
 *      Author: adria
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "HashTable.h"

void collisionsOutput(std::vector<int>, std::ofstream&);

HashTable linearProbingHashTable(11, LINEAR);
HashTable quadraticProbingHashTable(11, QUADRATIC);
HashTable doubleHashingProbingHashTable(11, DOUBLE);

int main()
{
	std::vector<int> keys;

	std::ifstream inFile;
	inFile.open("in_a_6_Lab3.txt");

	int num;

	while (inFile)
	{
		inFile >> num;
		keys.push_back(num);
	}

	keys.pop_back();
	inFile.close();

	std::cout << "Read the following values from input file:" << std::endl;
	for (int x : keys)
		std::cout << x << " ";
	std::cout << std::endl;

	std::ofstream outFileCollisions;
	std::ofstream outFileTables;

	outFileCollisions.open("output_a_6_collisions_Lab3.txt");
	outFileTables.open("output_a_6_tables_Lab3.txt");

	outFileCollisions << "***** Random Order Start *****" << std::endl;
	collisionsOutput(keys, outFileCollisions);
	outFileCollisions << "***** Random Order End *****" << std::endl;
	outFileCollisions << std::endl;

	outFileTables << "***** Linear Probing Random Order Start *****" << std::endl;
	linearProbingHashTable.printTable(outFileTables);
	outFileTables << "***** Linear Probing Random Order End *****" << std::endl;
	outFileTables << std::endl;

	outFileTables << "***** Quadratic Probing Random Order Start *****" << std::endl;
	quadraticProbingHashTable.printTable(outFileTables);
	outFileTables << "***** Quadratic Probing Random Order End *****" << std::endl;
	outFileTables << std::endl;

	outFileTables << "***** Double Hashing Probing Random Order Start *****" << std::endl;
	doubleHashingProbingHashTable.printTable(outFileTables);
	outFileTables << "***** Double Hashing Probing Random Order End *****" << std::endl;
	outFileTables << std::endl;

	std::sort(begin(keys), end(keys));
	linearProbingHashTable.clear();
	quadraticProbingHashTable.clear();
	doubleHashingProbingHashTable.clear();

	outFileCollisions << "***** Ascending Order Start *****" << std::endl;
	collisionsOutput(keys, outFileCollisions);
	outFileCollisions << "***** Ascending Order End *****" << std::endl;
	outFileCollisions << std::endl;

	outFileTables << "***** Linear Probing Ascending Order Start *****" << std::endl;
	linearProbingHashTable.printTable(outFileTables);
	outFileTables << "***** Linear Probing Ascending Order End *****" << std::endl;
	outFileTables << std::endl;

	outFileTables << "***** Quadratic Probing Ascending Order Start *****" << std::endl;
	quadraticProbingHashTable.printTable(outFileTables);
	outFileTables << "***** Quadratic Probing Ascending Order End *****" << std::endl;
	outFileTables << std::endl;

	outFileTables << "***** Double Hashing Probing Ascending Order Start *****" << std::endl;
	doubleHashingProbingHashTable.printTable(outFileTables);
	outFileTables << "***** Double Hashing Probing Ascending Order End *****" << std::endl;
	outFileTables << std::endl;

	std::sort(begin(keys), end(keys), std::greater<int>());
	linearProbingHashTable.clear();
	quadraticProbingHashTable.clear();
	doubleHashingProbingHashTable.clear();

	outFileCollisions << "***** Descending Order Start *****" << std::endl;
	collisionsOutput(keys, outFileCollisions);
	outFileCollisions << "***** Descending Order End *****" << std::endl;
	outFileCollisions << std::endl;

	outFileTables << "***** Linear Probing Descending Order Start *****" << std::endl;
	linearProbingHashTable.printTable(outFileTables);
	outFileTables << "***** Linear Probing Descending Order End *****" << std::endl;
	outFileTables << std::endl;

	outFileTables << "***** Quadratic Probing Descending Order Start *****" << std::endl;
	quadraticProbingHashTable.printTable(outFileTables);
	outFileTables << "***** Quadratic Probing Descending Order End *****" << std::endl;
	outFileTables << std::endl;

	outFileTables << "***** Double Hashing Probing Descending Order Start *****" << std::endl;
	doubleHashingProbingHashTable.printTable(outFileTables);
	outFileTables << "***** Double Hashing Probing Descending Order End *****" << std::endl;
	outFileTables << std::endl;

	outFileCollisions.close();

	return 0;
}

void collisionsOutput(std::vector<int> keys, std::ofstream& outFile)
{
	outFile << "Hash function: hash(key) = key" << std::endl;
	outFile << "Secondary hash function: hash2(key) = R - (key % R), where R = 7" << std::endl;
	outFile << std::endl;

	outFile << "----- Format of output -----" << std::endl;
	outFile << "Key : Value -> retrievedValue, Collisions: numCollisions" << std::endl;
	outFile << std::endl;

	int* retrievedVal;
	int prevNumCollisionsLinear;
	int prevNumCollisionsQuadratic;
	int prevNumCollisionsDoubleHashing;

	for (int key : keys)
	{
		prevNumCollisionsLinear = linearProbingHashTable.getNumCollisions();
		prevNumCollisionsQuadratic = quadraticProbingHashTable.getNumCollisions();
		prevNumCollisionsDoubleHashing = doubleHashingProbingHashTable.getNumCollisions();

		linearProbingHashTable.put(key, 2 * key);
		quadraticProbingHashTable.put(key, 2 * key);
		doubleHashingProbingHashTable.put(key, 2 * key);

		retrievedVal = linearProbingHashTable.get(key);
		outFile << key << " : " << 2 * key << " -> " << *retrievedVal << ", Collisions: " << linearProbingHashTable.getNumCollisions() - prevNumCollisionsLinear << std::endl;

		retrievedVal = quadraticProbingHashTable.get(key);
		outFile << key << " : " << 2 * key << " -> " << *retrievedVal << ", Collisions: " << quadraticProbingHashTable.getNumCollisions() - prevNumCollisionsQuadratic << std::endl;

		retrievedVal = doubleHashingProbingHashTable.get(key);
		outFile << key << " : " << 2 * key << " -> " << *retrievedVal << ", Collisions: " << doubleHashingProbingHashTable.getNumCollisions() - prevNumCollisionsDoubleHashing << std::endl;
		outFile << std::endl;
	}

	outFile << "----- Total number of collisions -----" << std::endl;
	outFile << "Linear probing: " << linearProbingHashTable.getNumCollisions() << std::endl;
	outFile << "Quadratic probing: " << quadraticProbingHashTable.getNumCollisions() << std::endl;
	outFile << "Double hashing probing: " << doubleHashingProbingHashTable.getNumCollisions() << std::endl;
}

