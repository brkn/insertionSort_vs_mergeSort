#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "csvRow.h"

std::vector<csvRow> readCsvFile(int& size, const char* filename) {
	std::vector<csvRow> rows(size);
	//csvRow temp;

	std::ifstream input;
	input.open(filename);
	if (!input.good()) throw "Error. File couldn't opened.";

	for (int i = 0; i < size; i++) { //we read size+1 lines because first line is header
		if (input.eof()) { //filesize is smaller than givensize
			size = i + 1; //? check if true, or is it size = i?
			break;
		}
		getline(input, rows[i].rowLine);
		std::cout << rows[i].rowLine << std::endl << std::endl; //for debug
		rows[i].setMembers();
	}
	return rows;
}

int outputSortedData(std::vector<csvRow> rows, int size, const char* filename) {
	return 0;
}

int insertionSort(std::vector<csvRow> rows, int n) {
	for (int i = 2; i < n; i++) {	//we skip first row, because its header
		csvRow key = rows[i];
		int j = i - 1;				//we skip first row, because its header

		while (j >= 1 && rows[j] > key)
		{
			rows[j + 1] = rows[j];
			j--;
		}
		rows[j + 1] = key;
	}
	return 0;
}

int mergeSort(std::vector<csvRow> rows, int n) {

	return 0;
}

int main(int argc, char** argv) {
	//get commandline arguments
	char *algo = argv[2], *feature = argv[4];
	int size = atoi(argv[6]) +1;

	//static key doesnt work for now
	
	try { //set the feature as a static member.
		csvRow::setKey(*feature);
	}
	catch (char* e) {
		printf("%s %c", e, *feature);
		return -3;
	}
	
	//printf("%d %c %c\n", size, *algo, *feature); // for debug

	std::vector<csvRow> rows;
	try { //read 'size' lines from input file
		 rows = readCsvFile(size, "log_inf.csv"); 
	}
	catch(char* e){
		printf("%s", e);
		return -4;
	}
		
	switch (*algo) {
		case 'i': //insertion sort
			insertionSort(rows, size, *feature);
			break;
		case 'm': //merge sort
			mergeSort(rows, size, *feature);
			break;
		default:
			printf("Error. Unexpected algorithm type: %c\n", *algo);
			return -1;
	}

	outputSortedData(rows, size, "sorted.csv"); //outputs the sorted data to given filename

	return 0;
}