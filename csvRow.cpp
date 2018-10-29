
#include "csvRow.h"
#include <string>

void csvRow::setMembers() {
	std::size_t index = this->rowLine.find_first_of(",");
	if (index == std::string::npos) return;
	this->timestamp = this->rowLine.substr(0, index);

	index = this->rowLine.find_first_of(",", index +1);
	if (index == std::string::npos) return;
	std::size_t index2 = this->rowLine.find_first_of(",", index + 1);
	if (index2 == std::string::npos) return;
	std::string temp = this->rowLine.substr(index+1, index2-index-1);
	if(temp != "last_price") this->price = std::stof(temp);
}

bool csvRow::operator>(csvRow& row2) {
	if (this->key) {
		return this->price > row2.price; //string to float
	}
	else {
		return this->timestamp > row2.timestamp;
	}
}

bool csvRow::operator<=(csvRow& row2) {
	if (this->key) {
		return this->price <= row2.price; //string to float
	}
	else {
		return this->timestamp <= row2.timestamp;
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