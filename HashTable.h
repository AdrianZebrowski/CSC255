/*
 * HashTable.h
 *
 *  Created on: Sep 29, 2022
 *      Author: adria
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <vector>
#include <iostream>

enum PROBING_TYPE{LINEAR, QUADRATIC, DOUBLE};

class HashTable
{
public:
	// Constructor
	HashTable(int tableSize, PROBING_TYPE probing);

	int* get(int key);
	void put(int key, int value);
	void printTable();
	void printTable(std::ofstream& outFile);
	void clear();

	int getTableSize() {return tableSize;}
	int getNumRecord() {return numRecords;}
	int getNumCollisions() {return numCollisions;}
	double getLoadFactor() {return loadFactor;}

private:
	struct Record
	{
		int key;
		int value;

		Record(int key, int value) : key(key), value(value) {}
	};

	int tableSize;
	int numRecords;
	int numCollisions;
	double loadFactor;
	std::vector<Record*> table;
	PROBING_TYPE probing;

	int hashIndex(int key) const;
	int find(int key);

};

HashTable::HashTable(int tableSize, PROBING_TYPE probing)
{
	std::vector<Record*>temp(tableSize, nullptr);
	table = temp;
	numRecords = 0;
	numCollisions = 0;
	loadFactor = 0.0;
	this->tableSize = tableSize;
	this->probing = probing;
}

int hash(int key)
{
	return key;
}

int hash2(int key)
{
	return 7 - (key % 7);
}

int HashTable::hashIndex(int key) const
{
	return hash(key) % tableSize;
}

// Linear probing only for now
int HashTable::find(int key)
{
	int startIndex = hashIndex(key);
	int index = startIndex;
	int currentCollisions = 0;

	while(true)
	{
		if (table[index] == nullptr || table[index]->key == key)
			return index;

		numCollisions++;
		currentCollisions++;

		if (probing == LINEAR)
			index = (startIndex + currentCollisions) % tableSize;
		else if (probing == QUADRATIC)
			index = (startIndex + currentCollisions * currentCollisions) % tableSize;
		else
			index = (startIndex + currentCollisions * hash2(key)) % tableSize;

		if (index == startIndex)
			return -1;
	}
}

int* HashTable::get(int key)
{
	int index = find(key);

	if (index == -1)
		return nullptr;

	Record* rec = table[index];

	if (rec == nullptr)
		return nullptr;
	else
		return & rec->value;
}

void HashTable::put(int key, int value)
{
	int index = find(key);

	if (index == -1)
		throw std::runtime_error("The hash table is full.");

	Record* rec = table[index];

	if (rec == nullptr)
	{
		table[index] = new Record(key, value);
		numRecords++;
		loadFactor = (double) numRecords / tableSize;
	}
	else
		rec->value = value;
}

void HashTable::printTable()
{
	std::cout << "Table size: " << tableSize << std::endl;
	std::cout << "Number of records: " << numRecords << std::endl;

	for (int i = 0; i < tableSize; i++)
	{
		if (table[i] != nullptr)
			std::cout << "Index = " << i << ", Key = " << table[i]->key << ", Value = " << table[i]->value << std::endl;
	}

	std::cout << "Probing mode: ";

		if(probing == LINEAR)
			std::cout << "Linear";
		else if (probing == QUADRATIC)
			std::cout << "Quadratic";
		else
			std::cout << "Double hashing";

	std::cout << std::endl;

	std::cout << "Number of collisions: " << numCollisions << std::endl;
}

void HashTable::printTable(std::ofstream& outFile)
{
	outFile << "Table size: " << tableSize << std::endl;
	outFile << "Number of records: " << numRecords << std::endl;

	for (int i = 0; i < tableSize; i++)
	{
		if (table[i] != nullptr)
			outFile << "Index = " << i << ", Key = " << table[i]->key << ", Value = " << table[i]->value << std::endl;
	}

	outFile << "Probing mode: ";

		if(probing == LINEAR)
			outFile << "Linear";
		else if (probing == QUADRATIC)
			outFile << "Quadratic";
		else
			outFile << "Double hashing";

	outFile << std::endl;

	outFile << "Number of collisions: " << numCollisions << std::endl;
}

void HashTable::clear()
{
	std::vector<Record*>temp(tableSize, nullptr);
	table = temp;
	numRecords = 0;
	numCollisions = 0;
	loadFactor = 0.0;
}

#endif /* HASHTABLE_H_ */
