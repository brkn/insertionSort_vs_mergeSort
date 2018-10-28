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

int insertionSort(std::vector<csvRow> rows, int size, char feature) {
	return 0;
}

int mergeSort(std::vector<csvRow> rows, int size, char feature) {
	return 0;
}

int main(int argc, char** argv) {
	/*for (int i = 0; i < argc; i++) {
		printf("%d %s\n", argc, argv[i]); // for debug
	}*/

	//get commandline arguments
	char *algo = argv[2], *feature = argv[4];
	int size = atoi(argv[6]) +1;

	//printf("%d %c %c\n", size, *algo, *feature); // for debug

	std::vector<csvRow> rows;
	try { //read 'size' lines from input file
		 rows = readCsvFile(size, "log_inf.csv"); 
	}
	catch(char* e){
		printf("%s", e);
	}

	switch (*algo) {
		case 'i': //insertion sort
			if (insertionSort(rows, size, *feature) == -2) {
				printf("Error. Unexpected feature type: %c", *feature);
				return -2;
			}
			break;
		case 'm': //merge sort
			if (mergeSort(rows, size, *feature) == -2) {
				printf("Error. Unexpected feature type: %c", *feature);
				return -2;
			}
			break;
		default:
			printf("Error. Unexpected algorithm type: %c\n", *algo);
			return -1;
	}

	outputSortedData(rows, size, "sorted.csv"); //outputs the sorted data to given filename

	return 0;
}