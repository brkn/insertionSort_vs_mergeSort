#include "csvRow.h"

void csvRow::setMembers() {
	std::size_t index = this->rowLine.find_first_of(",");
	if (index == std::string::npos) return;
	this->timestamp = this->rowLine.substr(0, index);

	index = this->rowLine.find_first_of(",", index +1);
	if (index == std::string::npos) return;
	std::size_t index2 = this->rowLine.find_first_of(",", index + 1);
	if (index2 == std::string::npos) return;
	this->price = this->rowLine.substr(index+1, index2-index-1);
}

bool csvRow::operator>(csvRow& row2) {
	if (this->key) {
		return std::stof(this->price) > std::stof(row2.price); //string to float
	}
	else {
		return this->timestamp > row2.timestamp;
	}
}

int csvRow::key = -1;
void csvRow::setKey(char feature) {
	switch (feature) {
		case 't':
			csvRow::key = 0;
			return;
		case 'p':
			csvRow::key = 1;
			return;
		default:
			throw "Error. Unexpected feature for criterion: ";
	}
}