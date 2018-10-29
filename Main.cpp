#include <cstdio>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "csvRow.h"

std::vector<csvRow> readCsvFile(int& size, const char* filename) {
	std::vector<csvRow> rows(size+1); //Size+1 because first line is header

	std::ifstream input;
	input.open(filename);
	if (!input.good()) throw "Error. File couldn't opened.";

	for (int i = 0; i < size + 1; i++) { //Size+1 lines are read because first line is header
		if (input.eof()) { //if filesize is smaller than givensize
			size = i - 1;
			break;
		}
		getline(input, rows[i].rowLine);
		rows[i].setMembers();
	}
	input.close();
	return rows;
}

int outputSortedDataToFile(std::vector<csvRow>& rows, int size, const char* filename) {
	std::ofstream output;
	output.open(filename);
	if (!output.good()) throw "Error: Couldn't create file.";
	for (int i = 0; i < size; i++)
		output << rows[i].rowLine << std::endl;
	output.close();
	return 1;
}

void insertionSort(std::vector<csvRow> &rows, int n) {
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
}
void mergeLeftRight(std::vector<csvRow>& rows, int left, int mid, int right) {
	int i, j, k;

	int leftSize = mid - left + 1;
	int rightSize = right - mid;

	std::vector<csvRow> leftVector, rightVector;

	leftVector.insert(leftVector.begin(), rows.begin()+left, rows.begin() + left + leftSize);
	rightVector.insert(rightVector.begin(), rows.begin()+mid + 1, rows.begin() + mid + rightSize + 1);


	i = 0; // Index of left vector
	j = 0; // Index of right vector
	k = left; // Index of merged vector
	while (i < leftSize && j < rightSize){
		if (leftVector[i] <= rightVector[j]){
			rows[k] = leftVector[i];
			i++;
		}
		else{
			rows[k] = rightVector[j];
			j++;
		}
		k++;
	}
	while (i < leftSize){
		rows[k] = leftVector[i];
		i++;
		k++;
	}
	while (j < rightSize){
		rows[k] = rightVector[j];
		j++;
		k++;
	}
}
void mergeSort(std::vector<csvRow>& rows, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(rows, left, mid); //sort left
		mergeSort(rows, mid + 1, right); //sort right
		mergeLeftRight(rows, left, mid, right);
	}
}

int main(int argc, char** argv) {
	//get commandline arguments
	char *algo = argv[2], *feature = argv[4];
	int size = atoi(argv[6]) +1;

	try { //set the feature as a static member.
		csvRow::setKey(*feature);
	}
	catch (char* e) {
		printf("%s %c", e, *feature);
		return -3;
	}

	//read rows from file
	std::vector<csvRow> rows;
	try { //read 'size' lines from input file
		 rows = readCsvFile(size, "log_inf.csv"); 
	}
	catch(char* e){
		printf("%s", e);
		return -4;
	}
	clock_t t = clock();
	switch (*algo) {
		t = clock();
		case 'i': //insertion sort
			insertionSort(rows, size);
			break;
		case 'm': //merge sort
			mergeSort(rows, 1, size -1); //Sent left = 1 because 0th is header, size-1 is most right element.
			break;
		default:
			printf("Error. Unexpected algorithm type: %c\n", *algo);
			return -1;
	}
	t = clock() - t;
	printf("Sorted %d rows, \n %c criterion \n, %c algorithm \n %f seconds\n", size - 1, *feature, *algo, ((float)t) / CLOCKS_PER_SEC);
	//output to file
	try { // output as given filename.
		outputSortedDataToFile(rows, size, "sorted.csv"); //outputs the sorted data to given filename
	}
	catch (char* e) {
		printf("%s", e);
		return -4;
	}

	return 0;
}